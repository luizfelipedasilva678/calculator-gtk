#ifndef __STACK_H__
#define __STACK_H__

struct node
{
    char data;
    struct node *next;
};

struct stack
{
    struct node *top;
    int size;
};

void push(struct stack *, char);
char pop(struct stack *);
char peek(struct stack *);
int is_empty(struct stack *);
void free_stack(struct stack *);

#endif