/* src/bytecode.h - Spinel Bytecode for Dynamic Features */
#ifndef SPINEL_BYTECODE_H
#define SPINEL_BYTECODE_H

#include <stdint.h>

typedef enum {
    BOP_NOP = 0,
    BOP_LOAD_INT,
    BOP_LOAD_STR,
    BOP_LOAD_LOCAL,
    BOP_STORE_LOCAL,
    BOP_SEND,
    BOP_EVAL,
    BOP_RETURN,
    BOP_JUMP,
    BOP_JUMP_IF_TRUE,
    BOP_JUMP_IF_FALSE,
    BOP_POP,
    BOP_DUP,
    BOP_MAKE_PROC,
    BOP_YIELD,
    BOP_MAX
} bop_t;

typedef struct {
    uint8_t  op;
    uint16_t op1;
    uint16_t op2;
} SpinelInsn;

typedef struct {
    SpinelInsn *code;
    uint32_t length;
    uint32_t max_stack;
    uint32_t local_count;
} SpinelBytecode;

SpinelBytecode* spinel_bytecode_new(uint32_t len);
void spinel_bytecode_free(SpinelBytecode *bc);

#endif