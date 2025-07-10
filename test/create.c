/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// Create a new file at the specified path
int main(int argc, char *argv[]) {
    // Check if exactly one argument is provided
    if (argc != 2) {
        fprintf(stderr, "Error: Program requires exactly one file path as argument\n");
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    int fd;

    // Attempt to create file with read/write permissions for user
    // O_CREAT: Create file if it doesn't exist
    // O_EXCL: Fail if file already exists
    // 0644: rw-r--r-- permissions
    if ((fd = open(file_path, O_CREAT | O_EXCL, 0644)) == -1) {
        fprintf(stderr, "Error: Failed to create file '%s': %s\n",
                file_path, strerror(errno));
        return EXIT_FAILURE;
    }

    // Close file descriptor before exit
    close(fd);
    return EXIT_SUCCESS;
}
