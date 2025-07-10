/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Check if a file path is provided as argument
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a file path as argument\n");
        return EXIT_FAILURE;
    }

    // Set mode to read/write for owner only (600)
    mode_t mode = S_IRUSR | S_IWUSR;

    // Set mode on the file using chmod
    if (chmod(argv[1], mode) == -1) {
        fprintf(stderr, "Error: Failed to set mode on file '%s': %s\n",
                argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
