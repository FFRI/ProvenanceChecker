/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/attr.h>

// Swap two files using renamex_np with RENAME_SWAP flag
int main(int argc, char *argv[]) {
    // Check if exactly two arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Error: Program requires exactly two file paths as arguments\n");
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    // Attempt to swap files using renamex_np
    if (renamex_np(file1, file2, RENAME_SWAP) != 0) {
        // Print error message if swap fails
        fprintf(stderr, "Error: Failed to swap files '%s' and '%s': %s\n",
                file1, file2, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
