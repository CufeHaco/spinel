/* src/bop_tracker.c */
#include "bop_tracker.h"
#include <string.h>

void bop_tracker_init(BOPTracker *t) {
    memset(t, 0, sizeof(BOPTracker));
}

void bop_tracker_record(BOPTracker *t, uint32_t site_id, bop_t op, uint32_t type_tag) {
    if (site_id >= 8192) return;
    BOPCallSite *site = &t->sites[site_id];
    site->exec_count++;
    if (site->type_tag == 0) site->type_tag = type_tag;
    if (site->exec_count > 50) site->hotness = 255;
}

int bop_tracker_is_hot(BOPTracker *t, uint32_t site_id) {
    if (site_id >= 8192) return 0;
    return t->sites[site_id].hotness > 128;
}