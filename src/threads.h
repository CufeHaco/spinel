/* src/threads.h */
#ifndef SPINEL_THREADS_H
#define SPINEL_THREADS_H

#include <stdint.h>

typedef int64_t mrb_int;

typedef struct sp_Thread sp_Thread;

sp_Thread* sp_thread_new(void (*fn)(void*), void* arg);
void sp_thread_join(sp_Thread* t);

void spinel_threads_init(void);

#endif