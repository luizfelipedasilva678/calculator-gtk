#include <stdio.h>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../data-structures/stack/stack.h"

STACK(double, double);

double evaluate(char *input) {
    struct parser_result *parser_result = parse(input);
    struct double_stack stack;
    struct double_stack_action_result pop_result;

    double_stack_init(&stack, sizeof(struct double_stack_node));

    for (int i = 0; i < parser_result->quantity; i++) {
        if (parser_result->tokens[i].type == NUMBER) {
            double_stack_push(
                &stack, strtod(parser_result->tokens[i].value, NULL), NULL);
            free(parser_result->tokens[i].value);
            continue;
        }

        free(parser_result->tokens[i].value);
    }

    pop_result = double_stack_pop(&stack);
    while (pop_result.error == 0) {
        printf("%f\n", pop_result.data);
        pop_result = double_stack_pop(&stack);
    }

    free(parser_result->tokens);
    free(parser_result);
    double_stack_clear_stack(&stack);
    return 0;
}

int main(void) {
    evaluate("(1+2)*3");
    return 0;
}