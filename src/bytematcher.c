/* src/bytematcher.c - Main Bytecode Interpreter */
#include "bytematcher.h"
#include <stdio.h>

mrb_int bytematcher_execute(SpinelBytecode *bc, mrb_int *stack, BOPTracker *tracker, mrb_int *out_result) {
    uint32_t pc = 0;
    mrb_int *sp = stack + bc->max_stack;

    while (pc < bc->length) {
        SpinelInsn inst = bc->code[pc++];
        bop_tracker_record(tracker, pc, 0, 0);

        switch (inst.op) {
        case BOP_LOAD_INT:
            *(--sp) = inst.op1;
            break;

        case BOP_SEND:
            fprintf(stderr, "[Bytematcher] Dynamic SEND: site %u\n", pc);
            break;

        case BOP_EVAL:
            fprintf(stderr, "[Bytematcher] EVAL requested\n");
            break;

        case BOP_RETURN:
            if (out_result) *out_result = *sp;
            return 1;

        default:
            fprintf(stderr, "[Bytematcher] Unhandled opcode %d at pc=%u\n", inst.op, pc);
            return 0;
        }
    }
    return 0;
}