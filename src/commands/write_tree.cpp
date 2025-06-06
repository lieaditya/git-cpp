#include <algorithm>
#include <iostream>
#include <filesystem>
#include <openssl/sha.h>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "commands/write_tree.hpp"
#include "utils/git_object.hpp"
#include "utils/hash.hpp"

std::string hexToRaw(const std::string& hex) {
    std::string raw;
    for (size_t i = 0; i < hex.size(); i += 2) {
        unsigned char byte = (unsigned char) std::stoi(hex.substr(i, 2), nullptr, 16);
        raw.push_back((char)byte);
    }
    return raw;
}

std::string serializeTreeEntry(const std::string& mode, const std::string& name, const std::string& shaHex) {
    std::string entry;
    entry += mode + " " + name + '\0';
    entry += hexToRaw(shaHex);
    return entry;
}

std::string writeTree(const std::filesystem::path& dirPath) {
	std::vector<std::tuple<std::string /*mode*/, std::string /*name*/, std::string /*sha*/>> entries;

	for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
		if (entry.path().filename() == ".git")
			continue;


		if (entry.is_directory()) {
			std::string treeSha = writeTree(entry.path());
			entries.emplace_back("40000", entry.path().filename().string(), treeSha);
		} else {
			std::string blobSha = utils::writeBlob(entry.path());
            entries.emplace_back("100644", entry.path().filename().string(), blobSha);
		}
	}

	std::sort(entries.begin(), entries.end(),
		  [](const auto& a, const auto& b) {
			  return std::get<1>(a) < std::get<1>(b);
		  });

	// unsigned char rawHash[SHA_DIGEST_LENGTH];
	// for (int i = 0; i < 20; ++i)
	// 	sscanf(hash.c_str() + 2*i, "%2hhx", &rawHash[i]);
	// 
	// entryStream << mode << ' ' << name << '\0';
	// std::string entryStr = entryStream.str();
	// entryStr.append(reinterpret_cast<char*>(rawHash), 20);
	// entries.push_back(entryStr);
	//
	// std::string content;
	// for (const auto& entry : entries)
	// 	content += entry;
	std::string treeContent;
    for (const auto& [mode, name, sha] : entries) {
        treeContent += serializeTreeEntry(mode, name, sha);
    }

	
	std::string header = "tree " + std::to_string(treeContent.size()) + '\0';
	std::string store = header + treeContent;
	std::string treeSha = utils::computeSHA1(store);
	utils::writeGitObject(treeSha, store);
	return treeSha;
}

void writeTreeCommand() {
	std::string treeHash = writeTree(std::filesystem::current_path());
	std::cout << treeHash << '\n';
}
