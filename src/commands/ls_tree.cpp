#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <sstream>
#include "commands/ls_tree.hpp"
#include "utils/compression.hpp"
#include "utils/file_io.hpp"
#include "utils/git_object.hpp"

#define OPT_NAME_ONLY 0

using utils::TreeEntry;

static struct option longOptions[] = {
	{"name-only", no_argument, 0, OPT_NAME_ONLY},
	{0, 0, 0, 0}
};

bool nameOnlyFlag = false;
std::string treeSHA;

namespace {
void parseArgs(const int& argc, char *const argv[]) {
	int opt;

	while ((opt = getopt_long(argc, argv, "", longOptions, nullptr)) != -1) {
		switch (opt) {
			case OPT_NAME_ONLY:
				nameOnlyFlag = true;
				break;
			default:
				std::cerr << "Usage: " << argv[0] << " " << argv[1] << " [options] <tree_sha>\n";
				exit(EXIT_FAILURE);
		}
	}

	optind++;
	if (optind >= argc) {
		std::cerr << "Missing tree SHA.\n";
		std::cerr << "Usage: " << argv[0] << " " << argv[1] << " [options] <tree_sha>\n";
		exit(EXIT_FAILURE);
	}
	treeSHA = argv[optind];
}

void printName(const std::vector<TreeEntry>& entries) {
	for (const auto& entry : entries) {
		std::cout << entry.name << '\n';
	}
}

std::vector<TreeEntry> parseTreeObject(const std::string& objPath) {
	std::vector<unsigned char> compressedData = utils::readFile(objPath);
	std::string contents = utils::decompress(compressedData);
	std::vector<TreeEntry> entries;

	size_t pos = 0;

	// skip tree size\0 header
	std::ostringstream treeStringStream;
	while (contents[pos] != '\0') {
		if (pos < 4) {
			treeStringStream << contents[pos];
		}
		if (pos == 4 && treeStringStream.str() != "tree") {
			std::cerr << "The given object is not a tree object.\n";
			exit(EXIT_FAILURE);
		}
		pos++;
	}	
	pos++;
	
	// parse content
	while (pos < contents.size()) { 
		TreeEntry entry;

		while (contents[pos] != ' ') {
			entry.mode += contents[pos++];
		}
		pos++;
		while (contents[pos] != '\0') {
			entry.name += contents[pos++];
		}
		pos++;
		entry.sha.append(&contents[pos], 20);
		pos += 20;
		entries.push_back(std::move(entry));

	}
	return entries;
}
} // empty namespace


void lsTreeCommand(const int& argc, char *const argv[]) {
	parseArgs(argc, argv);
	std::string objPath = ".git/objects/" + treeSHA.substr(0, 2) + '/' + treeSHA.substr(2);
	auto entries = parseTreeObject(objPath);
	if (nameOnlyFlag) {
		printName(entries);	
	}
}
