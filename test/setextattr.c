/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/xattr.h>

int main(int argc, char *argv[]) {
    // Check if a file path is provided as argument
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a file path as argument\n");
        return EXIT_FAILURE;
    }

    // Define an extended attribute name and value
    const char *attr_name = "user.comment";
    const char *attr_value = "This is a test extended attribute";

    // Set the extended attribute on the file
    if (setxattr(argv[1], attr_name, attr_value, strlen(attr_value), 0, 0) == -1) {
        fprintf(stderr, "Error: Failed to set extended attribute on file '%s': %s\n",
                argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
