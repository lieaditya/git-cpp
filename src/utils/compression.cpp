#include <vector>
#include <zlib.h>
#include <iostream>
#include <array>
#include "utils/compression.hpp"

#define BUFFER_SIZE 4096

namespace utils {

std::vector<unsigned char> compress(const std::string& data) {
    z_stream deflateStream{};
	/* use default allocation and deallocation function */
    deflateStream.zalloc = Z_NULL;
    deflateStream.zfree = Z_NULL;
    deflateStream.opaque = Z_NULL; // set this for shared context between zalloc and zfree only if custom zalloc and zfree are used 

    if (deflateInit(&deflateStream, Z_DEFAULT_COMPRESSION) != Z_OK) {
		if (deflateStream.msg != nullptr) {
			std::cerr << "Deflate init error: " << deflateStream.msg << '\n';
		} else {
			std::cerr << "Deflate init error: Unknown error\n";
		}
		exit(EXIT_FAILURE);
	}

    deflateStream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(data.data()));
    deflateStream.avail_in = data.size();
	std::array<Bytef, BUFFER_SIZE> buffer;
	std::vector<unsigned char> compressedData;

	int deflateRet;
    do {
        deflateStream.next_out = buffer.data();
        deflateStream.avail_out = BUFFER_SIZE;

		/* 
		 * Returns Z_STREAM_END if avail_in == 0 && flush is set to Z_FINISH, or Z_OK if avail_out == 0 && avail_in > 0
		 * Z_NO_FLUSH is set to buffer some data internally for better compression - more data to find patterns
		*/
        deflateRet = deflate(&deflateStream, deflateStream.avail_in ? Z_NO_FLUSH : Z_FINISH); 
		if (deflateRet != Z_OK && deflateRet != Z_STREAM_END) {
			deflateEnd(&deflateStream);
			std::cerr << "Deflate failed\n";
			exit(EXIT_FAILURE);
		}

        size_t bytesCompressed = BUFFER_SIZE - deflateStream.avail_out;
        compressedData.insert(compressedData.end(), buffer.begin(), buffer.begin() + bytesCompressed);
    } while (deflateRet != Z_STREAM_END);

	if (deflateEnd(&deflateStream) != Z_OK) {
		std::cerr << "Failed to free deflate stream\n";
		exit(EXIT_FAILURE);
	}
    return compressedData;
}

std::string decompress(const std::vector<unsigned char>& compressedData) {
    z_stream inflateStream = {};
    inflateStream.zalloc = Z_NULL;
    inflateStream.zfree = Z_NULL;
    inflateStream.opaque = Z_NULL;

    if (inflateInit(&inflateStream) != Z_OK) {
		if (inflateStream.msg != nullptr) {
			std::cerr << "Inflate init error: " << inflateStream.msg << '\n';
		} else {
			std::cerr << "Inflate init error: Unknown error\n";
		}
		exit(EXIT_FAILURE);
	}

    inflateStream.next_in = const_cast<Bytef*>(compressedData.data());
    inflateStream.avail_in = compressedData.size();
	std::array<Bytef, BUFFER_SIZE> buffer;
    std::string decompressedData;

    int inflateRet;
    do {
        inflateStream.next_out = buffer.data();
        inflateStream.avail_out = buffer.size();

		/* inflate() returns Z_STREAM_END if avail_in == 0 or Z_OK if avail_out == 0 && avail_in > 0 */
        inflateRet = inflate(&inflateStream, Z_NO_FLUSH);
        if (inflateRet != Z_OK && inflateRet != Z_STREAM_END) {
            inflateEnd(&inflateStream);
			if (inflateStream.msg != nullptr) {
				std::cerr << "Inflate failed: " << inflateStream.msg << '\n';
			} else {
				std::cerr << "Inflate failed: Unknown error (code " << inflateRet << ")\n";
			}
			exit(EXIT_FAILURE);
        }

		size_t bytesDecompressed = BUFFER_SIZE - inflateStream.avail_out;
		decompressedData.append(reinterpret_cast<char*>(buffer.data()), bytesDecompressed);
    } while (inflateRet != Z_STREAM_END);

	if (inflateEnd(&inflateStream) != Z_OK) {
		std::cerr << "Failed to free inflate stream\n";
		exit(EXIT_FAILURE);
	}
    return decompressedData;
}

} // namespcae utils
