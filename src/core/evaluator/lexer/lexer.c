#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

static uint8_t is_digit(char c) { return c >= '0' && c <= '9'; }

static uint8_t is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

static uint8_t is_parenthesis(char c) { return c == '(' || c == ')'; }

static void push_token(struct lexer_result* lexer_result, struct token token) {
    lexer_result->tokens[lexer_result->quantity] = token;
    lexer_result->quantity++;
}

static void make_number(struct lexer_result* lexer_result, char* input,
                        size_t* idx_input, size_t input_len) {
    size_t idx = 0;
    struct token token = {NUMBER, ""};

    while (*idx_input < input_len &&
           (is_digit(input[*idx_input]) || input[*idx_input] == '.')) {
        token.value[idx] = input[*idx_input];
        idx++;
        (*idx_input)++;
    }

    push_token(lexer_result, token);
}

static void make_operator(struct lexer_result* lexer_result, char* input,
                          size_t* idx_input, size_t input_len) {
    struct token token = {OPERATOR, ""};

    switch (input[*idx_input]) {
        case '+': {
            token.value[0] = '+';
            break;
        }
        case '-': {
            if (*idx_input - 1 >= 0 && is_digit(input[*idx_input - 1]) ||
                input[*idx_input - 1] == ')') {
                token.value[0] = '-';
            } else {
                token.value[0] = '#';
            }
            break;
        }
        case '*': {
            token.value[0] = '*';
            break;
        }
        case '/': {
            token.value[0] = '/';
            break;
        }
        case '^': {
            token.value[0] = '^';
            break;
        }
    }

    push_token(lexer_result, token);
    (*idx_input)++;
}

static void make_parenthesis(struct lexer_result* lexer_result,
                             char parenthesis, size_t* idx_input) {
    switch (parenthesis) {
        case '(': {
            struct token token = {LEFT_PARENTHESIS, "("};
            push_token(lexer_result, token);
            break;
        }
        case ')': {
            struct token token = {RIGHT_PARENTHESIS, ")"};
            push_token(lexer_result, token);
            break;
        } break;
    }

    (*idx_input)++;
}

static void tokenize(struct lexer_result* lexer_result, char* input) {
    size_t idx_input, input_len;

    input_len = strlen(input);
    idx_input = 0;

    while (idx_input < input_len) {
        if (is_digit(input[idx_input])) {
            make_number(lexer_result, input, &idx_input, input_len);
            continue;
        }

        if (is_operator(input[idx_input])) {
            make_operator(lexer_result, input, &idx_input, input_len);
            continue;
        }

        if (is_parenthesis(input[idx_input])) {
            make_parenthesis(lexer_result, input[idx_input], &idx_input);
            continue;
        }

        idx_input++;
    }
}

struct lexer_result get_tokens(char* input) {
    size_t length = strlen(input);
    struct lexer_result lexer_result = {NULL, 0};
    lexer_result.quantity = 0;
    lexer_result.tokens = (struct token*)malloc(sizeof(struct token) * length);

    tokenize(&lexer_result, input);

    return lexer_result;
}

int main(void) {
    struct lexer_result lexer_result = get_tokens("22+22.000+(2 + 3)");

    for (int i = 0; i < lexer_result.quantity; i++) {
        printf("%s\n", lexer_result.tokens[i].value);
    }

    free(lexer_result.tokens);
    return 0;
}