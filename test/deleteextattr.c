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

    // Get list of extended attributes
    ssize_t list_size = listxattr(argv[1], NULL, 0, XATTR_NOFOLLOW);
    if (list_size == -1) {
        fprintf(stderr, "Error: Failed to get extended attributes list for '%s': %s\n",
                argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    // If no extended attributes exist, exit successfully
    if (list_size == 0) {
        return EXIT_SUCCESS;
    }

    // Allocate buffer for extended attributes list
    char *attr_list = malloc(list_size);
    if (attr_list == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Get the actual list of extended attributes
    if (listxattr(argv[1], attr_list, list_size, XATTR_NOFOLLOW) == -1) {
        fprintf(stderr, "Error: Failed to get extended attributes list for '%s': %s\n",
                argv[1], strerror(errno));
        free(attr_list);
        return EXIT_FAILURE;
    }

    // Iterate through each attribute and remove it
    char *attr = attr_list;
    while (attr < attr_list + list_size) {
        if (removexattr(argv[1], attr, XATTR_NOFOLLOW) == -1) {
            fprintf(stderr, "Error: Failed to remove extended attribute '%s' from '%s': %s\n",
                    attr, argv[1], strerror(errno));
            free(attr_list);
            return EXIT_FAILURE;
        }
        attr += strlen(attr) + 1;
    }

    free(attr_list);
    return EXIT_SUCCESS;
}
