/* src/bytematcher.h */
#ifndef SPINEL_BYTEMATCHER_H
#define SPINEL_BYTEMATCHER_H

#include "bytecode.h"
#include "bop_tracker.h"
#include <stdint.h>

typedef int64_t mrb_int;

mrb_int bytematcher_execute(SpinelBytecode *bc, mrb_int *stack, BOPTracker *tracker, mrb_int *out_result);

#endif