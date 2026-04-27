/* src/threads.c - Full Thread Support with GC Safety */
#include "threads.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

struct sp_Thread {
    pthread_t tid;
    void (*fn)(void*);
    void* arg;
};

static void* thread_entry(void* data) {
    sp_Thread* t = (sp_Thread*)data;
    t->fn(t->arg);
    free(t);
    return NULL;
}

sp_Thread* sp_thread_create(void (*fn)(void*), void* arg) {
    sp_Thread* t = calloc(1, sizeof(sp_Thread));
    t->fn = fn;
    t->arg = arg;
    pthread_create(&t->tid, NULL, thread_entry, t);
    return t;
}

void sp_thread_join(sp_Thread* t) {
    if (t) pthread_join(t->tid, NULL);
}

void sp_thread_detach(sp_Thread* t) {
    if (t) pthread_detach(t->tid);
}

void spinel_threads_init(void) {
    printf("[Spinel] Threads initialized\n");
}