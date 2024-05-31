#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(struct stack *const stack, char data)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;

    if (stack->top == NULL)
    {
        stack->top = new;
    }
    else
    {
        new->next = stack->top;
        stack->top = new;
    }

    stack->size++;
}

char pop(struct stack *const stack)
{
    struct node *tmp = stack->top;

    if (tmp == NULL)
        return '\0';

    char data = tmp->data;
    stack->top = stack->top->next;
    free(tmp);

    stack->size--;

    return data;
}

int is_empty(struct stack *const stack)
{
    return stack->size == 0;
}

char peek(struct stack *const stack)
{
    return stack->top == NULL ? '\0' : stack->top->data;
}

void free_stack(struct stack *const stack)
{
    struct node *tmp = stack->top;

    while (tmp != NULL)
    {
        struct node *next = tmp->next;
        free(tmp);
        tmp = next;
    }

    free(stack);
}
