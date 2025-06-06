#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <vector>
#include <string>
#include <fstream>


namespace utils {

/**
 * @brief Reads the entire content of a file into a vector of bytes.
 *
 * @param path The file path to read from
 * @return std::vector<unsigned char> The content of the file in vector of bytes
*/
std::vector<unsigned char> readFile(const std::string& path);

/**
 * @brief Opens a file in binary mode for reading.
 *
 * @param path The file path string
 * @return std::ifstream A binary input file stream for the opened file
*/
std::ifstream openBinaryInputFile(const std::string& path);

/**
 * @brief Opens a file in binary mode for writing.
 *
 * @param path The file path string
 * @return std::ofstream A binary input file stream for the opened file
*/
std::ofstream openBinaryOutputFile(const std::string& path);

} // namespace utils

#endif // FILE_IO_HPP
