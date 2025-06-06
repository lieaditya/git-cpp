#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP

#include <vector>
#include <string>

namespace utils {

/**
 * @brief Compresses input data using zlib compression.
 *
 * @param data The input string data to compress
 * @return std::vector<unsigned char> The compressed data bytes
*/
std::vector<unsigned char> compress(const std::string& data);

/**
 * @brief Decompresses data previously compressed with zlib.
 *
 * @param compressedData The compressed data bytes
 * @return std::string The decompressed original data
 *
 * @throw std::runtime_error If decompression fails or data is invalid
*/
std::string decompress(const std::vector<unsigned char>& compressedData);

} // namespace utils

#endif // COMPRESSION_HPP
