#ifndef GIT_OBJECT_HPP
#define GIT_OBJECT_HPP

#include <string>
#include <filesystem>


namespace utils {

const std::filesystem::path GIT_OBJECTS_DIR = ".git/objects";

struct TreeEntry {
	std::string mode;
	std::string type;
	std::string sha;
	std::string name;
};

void writeGitObject(const std::string& hash, const std::string& content);

std::string writeBlob(const std::string& path, bool writeAsGitObject = false);

} // namespace utils

#endif // GIT_OBJECT_HPP
