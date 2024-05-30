#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../data-structures/stack/stack.h"

/* static int is_operator(char token)
{
    switch (token)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return 1;
    default:
        return 0;
    }
} */

void transform(char *exp)
{
    struct stack *operators_stack = (struct stack *)malloc(sizeof(struct stack *));
    size_t length;
    char *converted_exp;

    length = strlen(exp);
    converted_exp = (char *)malloc(sizeof(char) * length);
    operators_stack->top = NULL;
    operators_stack->size = 0;

    free_stack(operators_stack);
    free(converted_exp);
}

int main(void)
{
    printf("Hello");

    return 0;
}