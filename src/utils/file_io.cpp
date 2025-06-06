#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include "utils/file_io.hpp"

namespace utils {

std::vector<unsigned char> readFile(const std::string& path) {
	std::ifstream file(path, std::ios::binary);
	return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

std::ifstream openBinaryInputFile(const std::string& path) {
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed opening file " << path << '\n';
		std::cerr << strerror(errno) << '\n';
		exit(EXIT_FAILURE);
	}

	return file;
}

std::ofstream openBinaryOutputFile(const std::string& path) {
	std::ofstream file(path, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed opening file " << path << '\n';
		std::cerr << strerror(errno) << '\n';
		exit(EXIT_FAILURE);
	}

	return file;
}

} // namespace utils
