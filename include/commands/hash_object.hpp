#ifndef HASH_OBJECT_HPP
#define HASH_OBJECT_HPP

/**
 * @brief Computes the SHA-1 hash of a Git object. When used with the -w flag, it also writes the object to the .git/objects directory.
 *
 * The input for the SHA-1 hash is the header (blob size\0) + the contents of the file.
 *
 * Usage:
 *		git hash-object [-w] <file>
 *	
 * @param argc Number of arguments
 * @param argv Argument values
*/
void hashObjectCommand(const int& argc, char* const argv[]);

#endif // HASH_OBJECT_HPP
