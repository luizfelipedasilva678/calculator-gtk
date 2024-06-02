#include <stdio.h>
#include <string.h>
#include "stack.h"

struct stack *stack_init(size_t type_size, void(onerror)(void))
{
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack *));

    if (!stack)
        onerror();

    stack->top = NULL;
    stack->size = 0;
    stack->type_size = type_size;

    return stack;
}

void push(struct stack *stack, void *data, void(onerror)(void))
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = malloc(stack->type_size);

    if (!node || !node->data)
        onerror();

    memcpy(node->data, data, stack->type_size);
    node->next = stack->top;

    if (stack->top == NULL)
    {
        stack->top = node;
    }
    else
    {
        node->next = stack->top;
        stack->top = node;
    }

    stack->size++;
}

void *pop(struct stack *stack)
{
    struct node *node = stack->top;
    void *data = NULL;

    if (node == NULL)
        return NULL;

    stack->top = node->next;
    data = node->data;
    free(node);

    stack->size--;

    return data;
}

void *peek(struct stack *stack)
{
    struct node *node = stack->top;

    if (node == NULL)
        return NULL;

    return node->data;
}

uint8_t is_empty(struct stack *stack)
{
    return stack->top == NULL;
}

void clear_stack(struct stack *stack)
{
    struct node *node = stack->top;

    while (node != NULL)
    {
        struct node *next = node->next;
        free(node->data);
        free(node);
        node = next;
    }

    free(stack);
}
