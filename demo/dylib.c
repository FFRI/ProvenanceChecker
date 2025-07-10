/*
 *  (c) FFRI Security, Inc., 2025 / Author: FFRI Security, Inc.
 */
#include <stdio.h>

__attribute__((constructor))
void init(void) {
    printf("Hello dylib!\n");
}
