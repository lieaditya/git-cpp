#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include "utils/hash.hpp"

namespace utils {

std::string computeSHA1(std::string data) {
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
	
	std::ostringstream hashStream;
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
		hashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
	}
	std::string sha1 = hashStream.str();
	return sha1;
}

} // namespace utils
