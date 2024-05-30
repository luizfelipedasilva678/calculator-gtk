#ifndef __STACK_H__
#define __STACK_H__

struct node;
struct stack;
void push(struct stack *, char);
char pop(struct stack *);
char peek(struct stack *);
int is_empty(struct stack *);

#endif