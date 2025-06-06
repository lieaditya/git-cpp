#include <fstream>
#include <sstream>
#include <filesystem>
#include "utils/git_object.hpp"
#include "utils/compression.hpp"
#include "utils/hash.hpp"
#include "utils/file_io.hpp"

namespace utils {

void writeGitObject(const std::string& hash, const std::string& content) {
	std::string dir = ".git/objects/" + hash.substr(0, 2);
	std::string filePath = dir + "/" + hash.substr(2);

	std::filesystem::create_directories(dir);

	std::vector<unsigned char> compressed = utils::compress(content);

	std::ofstream objFile = utils::openBinaryOutputFile(filePath);
	objFile.write(reinterpret_cast<const char*>(compressed.data()), compressed.size());
	objFile.close();
}

std::string writeBlob(const std::string& path, bool writeAsGitObject) {
	std::ifstream file = utils::openBinaryInputFile(path);
    std::ostringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();
    std::string header = "blob " + std::to_string(content.size()) + '\0';
    std::string fullContent = header + content;

	std::string sha1 = utils::computeSHA1(fullContent);
	
	if (writeAsGitObject) {
		writeGitObject(sha1, fullContent);
	}

	return sha1;
}

} // namespace utils
