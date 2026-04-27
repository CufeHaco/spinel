/* src/vm.h - Spinel Dynamic Virtual Machine */
#ifndef SPINEL_VM_H
#define SPINEL_VM_H

#include "bytecode.h"
#include "bop_tracker.h"
#include <stdint.h>

typedef int64_t mrb_int;

mrb_int sp_eval(const char *code, mrb_int len);
mrb_int sp_dynamic_send(mrb_int receiver, mrb_int method_name, mrb_int *args, int argc);

void spinel_vm_init(void);
void sp_full_init(void);

#endif