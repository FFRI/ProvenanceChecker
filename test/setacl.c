/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/acl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    // Check if a file path is provided as argument
    if (argc != 2) {
        fprintf(stderr, "Error: Please provide a file path as argument\n");
        return EXIT_FAILURE;
    }

    // Create a basic ACL entry that grants read/write access
    acl_t acl = acl_init(1);
    if (acl == NULL) {
        fprintf(stderr, "Error: Failed to initialize ACL: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    acl_entry_t entry;
    if (acl_create_entry(&acl, &entry) == -1) {
        fprintf(stderr, "Error: Failed to create ACL entry: %s\n", strerror(errno));
        acl_free(acl);
        return EXIT_FAILURE;
    }

    // Set the tag type to user
    if (acl_set_tag_type(entry, ACL_EXTENDED_ALLOW) == -1) {
        fprintf(stderr, "Error: Failed to set ACL tag type: %s\n", strerror(errno));
        acl_free(acl);
        return EXIT_FAILURE;
    }

    // Set the permissions (read and write)
    acl_permset_t permset;
    if (acl_get_permset(entry, &permset) == -1) {
        fprintf(stderr, "Error: Failed to get ACL permission set: %s\n", strerror(errno));
        acl_free(acl);
        return EXIT_FAILURE;
    }
    
    acl_add_perm(permset, ACL_READ_DATA);
    acl_add_perm(permset, ACL_WRITE_DATA);

    // Apply the ACL to the file
    if (acl_set_file(argv[1], ACL_TYPE_EXTENDED, acl) == -1) {
        fprintf(stderr, "Error: Failed to set ACL on file '%s': %s\n", argv[1], strerror(errno));
        acl_free(acl);
        return EXIT_FAILURE;
    }

    // Clean up
    acl_free(acl);
    
    return EXIT_SUCCESS;
}
