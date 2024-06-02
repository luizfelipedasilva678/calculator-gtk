#ifndef __STACK_H__
#define __STACK_H__

#include <inttypes.h>
#include <stdlib.h>

struct node {
    void *data;
    struct node *next;
};

struct stack {
    struct node *top;
    uint32_t size;
    uint32_t type_size;
};

void *peek(struct stack *);
uint8_t is_empty(struct stack *);
void *pop(struct stack *);
void push(struct stack *, void *, void(onerror)(void));
struct stack *stack_init(size_t, void(onerror)(void));
void clear_stack(struct stack *);

#endif