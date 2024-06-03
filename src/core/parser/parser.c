#include <stdio.h>
#include "parser.h"
#include "../lexer/lexer.h"
#include "../data-structures/stack/stack.h"

STACK(token, struct token);

static uint8_t operator_precedence(char operator) {
    if (operator== '+' || operator== '-') {
        return PLUS_AND_MINUS_PRECEDENCE;
    } else if (operator== '*' || operator== '/') {
        return MULTIPLY_AND_DIVIDE_PRECEDENCE;
    } else {
        return NED_AND_POW_PRECEDENCE;
    }
}

static uint8_t operator_associativity(char operator) {
    if (operator== '+' || operator== '-') {
        return LEFT_ASSOCIATIVITY;
    } else if (operator== '*' || operator== '/') {
        return LEFT_ASSOCIATIVITY;
    } else {
        return RIGHT_ASSOCIATIVITY;
    }
}

void push_token(struct parser_result *parser_result, struct token token) {
    parser_result->tokens[parser_result->quantity] = token;
    parser_result->quantity++;
}

static void handle_operator(struct parser_result *parser_result,
                            struct token_stack *stack, struct token operator) {
    struct token_stack_action_result peek_result = token_stack_peek(stack);

    while (peek_result.error == 0 && peek_result.data.type == OPERATOR) {
        if ((operator_associativity(operator.value[0]) == LEFT_ASSOCIATIVITY &&
             operator_precedence(operator.value[0]) <=
                 operator_precedence(peek_result.data.value[0])) ||
            (operator_associativity(operator.value[0]) == RIGHT_ASSOCIATIVITY &&
             operator_precedence(operator.value[0]) <
                 operator_precedence(peek_result.data.value[0]))) {
            push_token(parser_result, token_stack_pop(stack).data);
        } else {
            break;
        }

        peek_result = token_stack_peek(stack);
    }

    token_stack_push(stack, operator, NULL);
}

static void handle_parenthesis(struct parser_result *parser_result,
                               struct token_stack *stack,
                               struct token parenthesis) {
    if (parenthesis.value[0] == '(') {
        token_stack_push(stack, parenthesis, NULL);
    } else {
        struct token_stack_action_result pop_result = token_stack_pop(stack);

        while (pop_result.error == 0 &&
               pop_result.data.type != LEFT_PARENTHESIS) {
            push_token(parser_result, pop_result.data);
            pop_result = token_stack_pop(stack);
        }

        free(parenthesis.value);
        free(pop_result.data.value);
    }
}

struct parser_result *parse(char *input) {
    struct tokenizer_result *tokenizer_result = tokenize_input(input);
    struct parser_result *parser_result;
    struct token_stack_action_result pop_result;
    struct token_stack stack;

    token_stack_init(&stack, sizeof(struct token_stack_node));

    parser_result =
        (struct parser_result *)malloc(sizeof(struct parser_result));
    parser_result->tokens = (struct token *)malloc(tokenizer_result->quantity *
                                                   sizeof(struct token));
    parser_result->quantity = 0;

    for (int i = 0; i < tokenizer_result->quantity; i++) {
        if (tokenizer_result->tokens[i].type == NUMBER) {
            push_token(parser_result, tokenizer_result->tokens[i]);
        } else if (tokenizer_result->tokens[i].type == OPERATOR) {
            handle_operator(parser_result, &stack, tokenizer_result->tokens[i]);
        } else {
            handle_parenthesis(parser_result, &stack,
                               tokenizer_result->tokens[i]);
        }
    }

    pop_result = token_stack_pop(&stack);
    while (pop_result.error == 0) {
        push_token(parser_result, pop_result.data);
        pop_result = token_stack_pop(&stack);
    }

    free(tokenizer_result->tokens);
    free(tokenizer_result);
    token_stack_clear_stack(&stack);

    return parser_result;
}
