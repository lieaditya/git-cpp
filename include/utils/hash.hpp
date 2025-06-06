#ifndef HASH_HPP
#define HASH_HPP

#include <string>

namespace utils {

/**
 * @brief Computes the SHA1 hash of the given data
 *
 * @param data A data string to be hashed
 * @return std::string The SHA1 hash string in hexadecimal format
*/
std::string computeSHA1(std::string data);

} // namespace utils

#endif // HASH_HPP
