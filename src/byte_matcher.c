/* src/byte_matcher.c - High-performance byte matcher */
#include "byte_matcher.h"
#include <string.h>

int byte_ends_with(const uint8_t* bytes, size_t len, const uint8_t* pattern, size_t plen) {
    if (plen > len) return 0;
    return memcmp(bytes + len - plen, pattern, plen) == 0;
}

int byte_contains(const uint8_t* bytes, size_t len, const uint8_t* pattern, size_t plen) {
    if (plen > len) return 0;
    for (size_t i = 0; i <= len - plen; i++) {
        if (memcmp(bytes + i, pattern, plen) == 0) return 1;
    }
    return 0;
}

int byte_equals(const uint8_t* a, size_t alen, const uint8_t* b, size_t blen) {
    if (alen != blen) return 0;
    return memcmp(a, b, alen) == 0;
}

/* Path Index */
PathIndex* path_index_build(const char** paths, size_t count) {
    PathIndex* idx = calloc(1, sizeof(PathIndex));
    idx->count = count;
    idx->paths = paths;
    idx->path_bytes = calloc(count, sizeof(uint8_t*));
    idx->basename_bytes = calloc(count, sizeof(uint8_t*));

    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(paths[i]);
        idx->path_bytes[i] = malloc(len + 1);
        memcpy(idx->path_bytes[i], paths[i], len + 1);
        
        const char* base = strrchr(paths[i], '/');
        base = base ? base + 1 : paths[i];
        size_t blen = strlen(base);
        idx->basename_bytes[i] = malloc(blen + 1);
        memcpy(idx->basename_bytes[i], base, blen + 1);
    }
    return idx;
}

const char* path_index_find_ending_with(PathIndex* idx, const char* pattern) {
    size_t plen = strlen(pattern);
    for (size_t i = 0; i < idx->count; i++) {
        size_t len = strlen(idx->paths[i]);
        if (byte_ends_with((uint8_t*)idx->paths[i], len, (uint8_t*)pattern, plen)) {
            return idx->paths[i];
        }
    }
    return NULL;
}

void path_index_free(PathIndex* idx) {
    if (!idx) return;
    for (size_t i = 0; i < idx->count; i++) {
        free(idx->path_bytes[i]);
        free(idx->basename_bytes[i]);
    }
    free(idx->path_bytes);
    free(idx->basename_bytes);
    free(idx);
}