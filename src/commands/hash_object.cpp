#include <iostream>
#include <getopt.h>
#include "commands/hash_object.hpp"
#include "utils/git_object.hpp"

bool writeFlag = false;
std::string path;

namespace {

void parseArgs(const int& argc, char* const argv[]) {
    if (argc == 2) {
		std::cerr << "Missing argument.\n";
        std::cerr << "Usage: " << argv[0] << " [-w] <file>\n";
        exit(EXIT_FAILURE);
    }
    int opt;
    while ((opt = getopt(argc, argv, "w:")) != -1) {
        switch (opt) {
            case 'w':
                writeFlag = true;
				path = optarg;
				break;
            default: 
                std::cerr << "Usage: " << argv[0] << " [-w] <file>\n";
                exit(EXIT_FAILURE);
        }
    }
}

} // empty namespace

void hashObjectCommand(const int& argc, char* const argv[]) {
	parseArgs(argc, argv);
	std::string sha1;
	if (writeFlag) {
		sha1 = utils::writeBlob(path, true);
	} else {
		sha1 = utils::writeBlob(path);
	}
    std::cout << sha1 << std::endl;
}
