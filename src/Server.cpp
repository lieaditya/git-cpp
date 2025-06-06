#include <iostream>
#include <string>
#include "commands/commands_handler.hpp"


int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

	if (argc < 2) {
		std::cerr << "Missing command.\n";
		std::cerr << "Usage: " << argv[0] << " <command> [options] [arguments]\n";
		return EXIT_FAILURE;
	}

	std::string commandStr = argv[1];
	CommandType command = getCommandType(commandStr);

	switch (command) {
		case CommandType::INIT:
			initCommand();
			break;
		case CommandType::CAT_FILE:
			catFileCommand(argc, argv);
			break;
		case CommandType::HASH_OBJECT:
			hashObjectCommand(argc, argv);
			break;
		case CommandType::LS_TREE:
			lsTreeCommand(argc, argv);
			break;
		case CommandType::WRITE_TREE:
			writeTreeCommand();
			break;
		default:
			std::cerr << "Unknown command: " << argv[1] << '\n';
			return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
