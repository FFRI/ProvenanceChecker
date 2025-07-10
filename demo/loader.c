/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) {
    // Check if a dylib path is provided as argument
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a dylib path as argument\n");
        return EXIT_FAILURE;
    }

    // Try to load the dynamic library
    void *handle = dlopen(argv[1], RTLD_NOW);
    if (!handle) {
        fprintf(stderr, "Error: Failed to load dylib '%s': %s\n",
                argv[1], dlerror());
        return EXIT_FAILURE;
    }

    // Successfully loaded the dylib
    printf("Successfully loaded dylib: %s\n", argv[1]);

    // Close the library
    dlclose(handle);

    return EXIT_SUCCESS;
}
