/* src/bop_tracker.h */
#ifndef SPINEL_BOP_TRACKER_H
#define SPINEL_BOP_TRACKER_H

#include "bytecode.h"

typedef struct {
    uint64_t exec_count;
    uint64_t miss_count;
    uint32_t type_tag;
    uint8_t  hotness;
} BOPCallSite;

typedef struct {
    BOPCallSite sites[8192];
    uint32_t count;
} BOPTracker;

void bop_tracker_init(BOPTracker *t);
void bop_tracker_record(BOPTracker *t, uint32_t site_id, bop_t op, uint32_t type_tag);
int  bop_tracker_is_hot(BOPTracker *t, uint32_t site_id);

#endif