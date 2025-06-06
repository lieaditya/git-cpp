#include <iostream>
#include <vector>
#include <unistd.h>
#include "commands/cat_file.hpp"
#include "utils/compression.hpp"
#include "utils/file_io.hpp"

bool prettyPrint = false;
std::string hash;

namespace {

void parseArgs(const int& argc, char* const argv[]) {
    if (argc == 2) {
        std::cerr << "No option specified\n";
		std::cerr << "Usage: " << argv[0] << " " << argv[1] << " -p <object>\n";
        exit(EXIT_FAILURE);
    }

    int opt;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                prettyPrint = true;
                hash = optarg;
                break;
            default:
				std::cerr << "Usage: " << argv[0] << " " << argv[1] << " -p <object>\n";
                exit(EXIT_FAILURE);
        }
    }
}

} // empty namespace

void catFileCommand(const int& argc, char* const argv[]) {
	parseArgs(argc, argv);
    if (prettyPrint) {
        std::string path = ".git/objects/" + hash.substr(0, 2) + '/' + hash.substr(2);
        std::vector<unsigned char> compressedData = utils::readFile(path);
        std::string decompressedData = utils::decompress(compressedData);
		size_t nullBytePos = decompressedData.find('\0');
		if (nullBytePos != std::string::npos && nullBytePos + 1 < decompressedData.size()) {
			std::cout << decompressedData.substr(nullBytePos + 1);
		} else {
			std::cerr << "Error: invalid Git object format.\n";
			exit(EXIT_FAILURE);
		}
    }
}
