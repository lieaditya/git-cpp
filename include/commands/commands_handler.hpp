#ifndef COMMANDS_HANDLER_HPP
#define COMMANDS_HANDLER_HPP

#include <string>
#include "commands/init.hpp"
#include "commands/cat_file.hpp"
#include "commands/hash_object.hpp"
#include "commands/ls_tree.hpp"
#include "commands/write_tree.hpp"

enum class CommandType {
    INIT,
    CAT_FILE,
    HASH_OBJECT,
	LS_TREE,
	WRITE_TREE,
    UNKNOWN
};

CommandType getCommandType(const std::string& command); 

#endif // COMMANDS_HANDLER_HPP
