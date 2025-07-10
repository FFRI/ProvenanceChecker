/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// Create a hard link from source file to target path
int main(int argc, char *argv[]) {
    // Check if exactly two arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Error: Program requires exactly two file paths as arguments\n");
        fprintf(stderr, "Usage: %s <source_file> <target_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source = argv[1];
    const char *target = argv[2];

    // Attempt to create hard link from source to target
    if (link(source, target) != 0) {
        // Print error message if link creation fails
        fprintf(stderr, "Error: Failed to create hard link from '%s' to '%s': %s\n",
                source, target, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
