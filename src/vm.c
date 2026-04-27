/* src/vm.c - Spinel Dynamic VM Implementation */
#include "vm.h"
#include "bytematcher.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static BOPTracker global_bop_tracker;

static int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static void skip_ws(const char **p) {
    while (**p && is_whitespace(**p)) (*p)++;
}

static const char* parse_number(const char *p, mrb_int *out_val) {
    skip_ws(&p);
    int sign = 1;
    if (*p == '-') { sign = -1; p++; }
    else if (*p == '+') { p++; }
    
    mrb_int val = 0;
    while (*p && isdigit(*p)) {
        val = val * 10 + (*p - '0');
        p++;
    }
    *out_val = sign * val;
    return p;
}

static const char* eval_term(const char *p, mrb_int *out_val);
static const char* eval_expr(const char *p, mrb_int *out_val);

static const char* eval_term(const char *p, mrb_int *out_val) {
    skip_ws(&p);
    
    if (*p == '(') {
        p++;
        p = eval_expr(p, out_val);
        if (*p == ')') p++;
        return p;
    }
    
    return parse_number(p, out_val);
}

static const char* eval_expr(const char *p, mrb_int *out_val) {
    skip_ws(&p);
    
    mrb_int left = 0;
    p = eval_term(p, &left);
    
    while (*p) {
        skip_ws(&p);
        char op = *p;
        if (op == '+' || op == '-' || op == '*' || op == '/') {
            p++;
            mrb_int rhs = 0;
            p = eval_term(p, &rhs);
            if (op == '+') left = left + rhs;
            else if (op == '-') left = left - rhs;
            else if (op == '*') left = left * rhs;
            else if (op == '/') left = rhs != 0 ? left / rhs : 0;
        } else {
            break;
        }
    }
    
    *out_val = left;
    return p;
}

void spinel_vm_init(void) {
    bop_tracker_init(&global_bop_tracker);
    printf("[Spinel VM] Bytematcher + BOP Tracker initialized\n");
}

void sp_full_init(void) {
    spinel_vm_init();
}

mrb_int sp_eval(const char *code, mrb_int len) {
    if (!code || len == 0) return 0;
    
    char *expr = malloc(len + 1);
    strncpy(expr, code, len);
    expr[len] = '\0';
    
    fprintf(stderr, "[Spinel] eval(\"%s\")\n", expr);
    
    mrb_int result = 0;
    eval_expr(expr, &result);
    
    fprintf(stderr, "[Spinel] eval result: %ld\n", (long)result);
    
    free(expr);
    return result;
}

mrb_int sp_dynamic_send(mrb_int receiver, mrb_int method_name, mrb_int *args, int argc) {
    bop_tracker_record(&global_bop_tracker, 0, 0, 0);
    
    return receiver;
}