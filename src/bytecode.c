/* src/bytecode.c */
#include "bytecode.h"
#include <stdlib.h>
#include <string.h>

SpinelBytecode* spinel_bytecode_new(uint32_t len) {
    SpinelBytecode* bc = calloc(1, sizeof(SpinelBytecode));
    bc->code = calloc(len, sizeof(SpinelInsn));
    bc->length = len;
    bc->max_stack = 64;
    bc->local_count = 16;
    return bc;
}

void spinel_bytecode_free(SpinelBytecode *bc) {
    if (bc) {
        free(bc->code);
        free(bc);
    }
}