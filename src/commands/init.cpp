#include <exception>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include "commands/init.hpp"
#include "utils/file_io.hpp"

void initCommand() {
    try {
        std::filesystem::create_directory(".git");
        std::filesystem::create_directory(".git/objects");
        std::filesystem::create_directory(".git/refs");

		std::ofstream headFile = utils::openBinaryOutputFile(".git/HEAD");
        headFile << "ref: refs/heads/main\n";
        headFile.close();
        std::cout << "Initialized git directory\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}
