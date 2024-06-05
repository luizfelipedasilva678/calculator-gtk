#include <stdio.h>
#include <math.h>
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../data-structures/stack/stack.h"
#include "evaluator.h"

STACK(double, double)

static void handle_operator(struct double_stack *stack, struct token operator,
                            struct evaluation_result * result) {
    struct double_stack_action_result pop_result1;
    struct double_stack_action_result pop_result2;

    if (operator.value[0] == '#') {
        pop_result1 = double_stack_pop(stack);

        if (pop_result1.error == 0)
            double_stack_push(stack, -1 * pop_result1.data);
        else
            result->status = EVALUATOR_INVALID_EXPRESSION;

    } else {
        pop_result2 = double_stack_pop(stack);
        pop_result1 = double_stack_pop(stack);

        if (pop_result1.error == 0 && pop_result2.error == 0)
            switch (operator.value[0]) {
                case '+': {
                    double_stack_push(stack,
                                      pop_result1.data + pop_result2.data);
                    break;
                }
                case '-': {
                    double_stack_push(stack,
                                      pop_result1.data - pop_result2.data);
                    break;
                }
                case '*': {
                    double_stack_push(stack,
                                      pop_result1.data * pop_result2.data);
                    break;
                }
                case '/': {
                    double_stack_push(stack,
                                      pop_result1.data / pop_result2.data);
                    break;
                }
                case '^': {
                    double_stack_push(stack,
                                      pow(pop_result1.data, pop_result2.data));
                    break;
                }
            }
        else
            result->status = EVALUATOR_INVALID_EXPRESSION;
    }

    free(operator.value);
}

struct evaluation_result evaluate(const char *input) {
    struct parser_result *parser_result = parse(input);
    struct evaluation_result result;
    struct double_stack stack;
    struct double_stack_action_result pop_result;

    result.status = EVALUATOR_SUCCESS;
    result.value = 0;

    double_stack_init(&stack, sizeof(struct double_stack_node));

    if (parser_result->status != PARSER_SUCCESS) {
        for (int i = 0; i < parser_result->quantity; i++) {
            free(parser_result->tokens[i].value);
        }

        free(parser_result->tokens);
        free(parser_result);
        double_stack_clear_stack(&stack);

        result.status = parser_result->status == PARSER_MISSING_PARENTHESIS
                            ? EVALUATOR_INVALID_EXPRESSION
                            : EVALUATOR_INTERNAL_ERROR;

        return result;
    }

    for (int i = 0; i < parser_result->quantity; i++) {
        if (parser_result->tokens[i].type == NUMBER) {
            double_stack_push(&stack,
                              strtod(parser_result->tokens[i].value, NULL));
            free(parser_result->tokens[i].value);
            continue;
        }

        handle_operator(&stack, parser_result->tokens[i], &result);
    }

    if (stack.size == 1) {
        pop_result = double_stack_pop(&stack);
        result.value = pop_result.data;
    } else {
        result.status = EVALUATOR_INVALID_EXPRESSION;
    }

    free(parser_result->tokens);
    free(parser_result);
    double_stack_clear_stack(&stack);

    return result;
}
