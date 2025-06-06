#ifndef CATFILE_HPP
#define CATFILE_HPP

/**
 * @brief Pretty-print the content of an object file.
 *
 * Usage:
 *		git cat-file -p <object>
 *
 * @param argc Number of CLI arguments
 * @param argv Array of argument strings
 */
void catFileCommand(const int& argc, char* const argv[]);

#endif // CATFILE_HPP
