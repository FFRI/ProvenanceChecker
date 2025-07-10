/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/attr.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Check if a file path is provided as argument
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a file path as argument\n");
        return EXIT_FAILURE;
    }

    // Initialize attribute list structure
    struct attrlist attrs;
    memset(&attrs, 0, sizeof(attrs));
    attrs.bitmapcount = ATTR_BIT_MAP_COUNT;
    attrs.commonattr = ATTR_CMN_CRTIME | ATTR_CMN_MODTIME; // Set creation and modification times

    // Initialize attribute buffer with current time
    struct timespec times[2];
    times[0].tv_sec = time(NULL);  // Creation time
    times[0].tv_nsec = 0;
    times[1].tv_sec = time(NULL);  // Modification time 
    times[1].tv_nsec = 0;

    // Set attributes on the file
    if (setattrlist(argv[1], &attrs, times, sizeof(times), 0) != 0) {
        fprintf(stderr, "Error: Failed to set attributes on file '%s': %s\n", 
                argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
