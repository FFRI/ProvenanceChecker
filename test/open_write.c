/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// Open file in read-write mode and write "Hello World!" to it
int main(int argc, char *argv[]) {
    // Check if exactly one argument is provided
    if (argc != 2) {
        fprintf(stderr, "Error: Program requires exactly one file path as argument\n");
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    int fd;
    const char *message = "Hello World!";
    ssize_t bytes_written;

    // Attempt to open file in read-write mode
    if ((fd = open(file_path, O_RDWR)) == -1) {
        fprintf(stderr, "Error: Failed to open file '%s': %s\n",
                file_path, strerror(errno));
        return EXIT_FAILURE;
    }

    // Write message to file
    bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1 || bytes_written != strlen(message)) {
        fprintf(stderr, "Error: Failed to write to file '%s': %s\n",
                file_path, strerror(errno));
        close(fd);
        return EXIT_FAILURE;
    }

    // Close file descriptor before exit
    close(fd);
    return EXIT_SUCCESS;
}
