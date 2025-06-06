#include "commands/commands_handler.hpp"

CommandType getCommandType(const std::string& command) {
    if (command == "init") return CommandType::INIT;
    if (command == "cat-file") return CommandType::CAT_FILE;
    if (command == "hash-object") return CommandType::HASH_OBJECT;
	if (command == "ls-tree") return CommandType::LS_TREE;
	if (command == "write-tree") return CommandType::WRITE_TREE;
    return CommandType::UNKNOWN;
}
