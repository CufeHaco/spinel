/* src/byte_matcher.h - High-performance byte matcher */
#ifndef SPINEL_BYTE_MATCHER_H
#define SPINEL_BYTE_MATCHER_H

#include <stdint.h>
#include <stddef.h>

int byte_ends_with(const uint8_t* bytes, size_t len, const uint8_t* pattern, size_t plen);
int byte_contains(const uint8_t* bytes, size_t len, const uint8_t* pattern, size_t plen);
int byte_equals(const uint8_t* a, size_t alen, const uint8_t* b, size_t blen);

typedef struct {
    const char** paths;
    size_t count;
    uint8_t** path_bytes;
    uint8_t** basename_bytes;
} PathIndex;

PathIndex* path_index_build(const char** paths, size_t count);
const char* path_index_find_ending_with(PathIndex* idx, const char* pattern);
void path_index_free(PathIndex* idx);

#endif