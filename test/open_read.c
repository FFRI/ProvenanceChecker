/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

// Open and read a file in read-only mode
int main(int argc, char *argv[]) {
    // Check if exactly one argument is provided
    if (argc != 2) {
        fprintf(stderr, "Error: Program requires exactly one file path as argument\n");
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Attempt to open file in read-only mode
    if ((fd = open(file_path, O_RDONLY)) == -1) {
        fprintf(stderr, "Error: Failed to open file '%s': %s\n",
                file_path, strerror(errno));
        return EXIT_FAILURE;
    }

    // Read file contents and write to stdout
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            fprintf(stderr, "Error: Failed to write to stdout: %s\n",
                    strerror(errno));
            close(fd);
            return EXIT_FAILURE;
        }
    }

    // Check if read operation failed
    if (bytes_read == -1) {
        fprintf(stderr, "Error: Failed to read file '%s': %s\n",
                file_path, strerror(errno));
        close(fd);
        return EXIT_FAILURE;
    }

    // Close file descriptor before exit
    close(fd);
    return EXIT_SUCCESS;
}

