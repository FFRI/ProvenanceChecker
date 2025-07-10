/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    // Check if a file path is provided as argument
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a file path as argument\n");
        return EXIT_FAILURE;
    }

    // Set current time for both access and modification times
    struct timeval times[2];
    gettimeofday(&times[0], NULL); // Access time
    gettimeofday(&times[1], NULL); // Modification time

    // Set timestamps on the file using utimes
    if (utimes(argv[1], times) == -1) {
        fprintf(stderr, "Error: Failed to set timestamps on file '%s': %s\n",
                argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
