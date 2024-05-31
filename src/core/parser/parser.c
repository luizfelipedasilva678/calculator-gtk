#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "../data-structures/stack/stack.h"

static int is_operator(char token)
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
}

static int precedence(char token)
{
    switch (token)
    {
    case '+':
    case '-':
        return MINUS_AND_PLUS_PRECENDENCE;
    case '*':
    case '/':
        return ASTERISK_AND_SLASH_PRECENDENCE;
    default:
        return 0;
    }
}

static void handle_operator(struct stack *operators_stack, char token, char *converted_exp, size_t *idx_converted_exp)
{
    char operator= peek(operators_stack);

    while (operator!= '\0' && precedence(operator) >= precedence(token))
    {
        strcpy(&converted_exp[*idx_converted_exp], &operator);
        (*idx_converted_exp)++;
        pop(operators_stack);
        operator= peek(operators_stack);
    }

    push(operators_stack, token);
}

static void handle_right_parenthesis(struct stack *operators_stack, char *converted_exp, size_t *idx_converted_exp)
{
    char operator= pop(operators_stack);

    while (operator!= '(')
    {
        converted_exp[*idx_converted_exp] = operator;
        (*idx_converted_exp)++;
        operator= pop(operators_stack);
    }
}

static char *transform(char *exp)
{
    struct stack *operators_stack = (struct stack *)malloc(sizeof(struct stack *));
    size_t i, length, idx_converted_exp;
    char *converted_exp, operator;

    length = strlen(exp);
    converted_exp = (char *)malloc(sizeof(char) * length);
    idx_converted_exp = 0;
    operators_stack->top = NULL;
    operators_stack->size = 0;

    for (i = 0; i < length; i++)
    {
        if (is_operator(exp[i]))
        {
            handle_operator(operators_stack, exp[i], converted_exp, &idx_converted_exp);
            continue;
        }

        if (exp[i] == '(')
        {
            push(operators_stack, exp[i]);
            continue;
        }

        if (exp[i] == ')')
        {
            handle_right_parenthesis(operators_stack, converted_exp, &idx_converted_exp);
            continue;
        }

        converted_exp[idx_converted_exp] = exp[i];
        idx_converted_exp++;
    }

    operator= pop(operators_stack);
    while (operator!= '\0')
    {
        converted_exp[idx_converted_exp] = operator;
        idx_converted_exp++;
        operator= pop(operators_stack);
    }
    converted_exp[idx_converted_exp] = '\0';

    free_stack(operators_stack);

    return converted_exp;
}

int resolve(char *exp)
{
    struct stack *operands_stack = (struct stack *)malloc(sizeof(struct stack *));
    char *converted_exp = transform(exp);

    operands_stack->top = NULL;
    operands_stack->size = 0;

    printf("%s\n", converted_exp);

    free(converted_exp);
    free(operands_stack);
    return 0;
}

int main(void)
{
    int result = resolve("3+4+8");

    printf("%d\n", result);

    return 0;
}