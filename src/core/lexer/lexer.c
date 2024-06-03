#include <stdio.h>
#include <string.h>
#include "lexer.h"

static uint8_t is_digit(char c) { return c >= '0' && c <= '9'; }

static uint8_t is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

static uint8_t is_parenthesis(char c) { return c == '(' || c == ')'; }

static void push_token(struct tokenizer_result* tokenizer_result,
                       struct token token) {
    tokenizer_result->tokens[tokenizer_result->quantity] = token;
    tokenizer_result->quantity++;
}

static size_t count_digits(char* number, size_t start, size_t end) {
    size_t count, i;

    count = 0;
    for (i = start; i < end && (is_digit(number[i]) || number[i] == '.'); i++) {
        count++;
    }

    return count;
}

static void make_number(struct tokenizer_result* tokenizer_result, char* input,
                        size_t* idx_input, size_t input_len) {
    size_t idx = 0;

    struct token token;
    token.type = NUMBER;
    token.value = (char*)malloc(
        count_digits(input, *idx_input, input_len) * sizeof(char) + 1);

    while (*idx_input < input_len &&
           (is_digit(input[*idx_input]) || input[*idx_input] == '.')) {
        token.value[idx] = input[*idx_input];
        idx++;
        (*idx_input)++;
    }
    token.value[idx] = '\0';
    push_token(tokenizer_result, token);
}

static void make_operator(struct tokenizer_result* tokenizer_result,
                          char* input, size_t* idx_input, size_t input_len) {
    struct token token;
    token.type = OPERATOR;
    token.value = (char*)malloc(2 * sizeof(char));
    token.value[1] = '\0';

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

    push_token(tokenizer_result, token);
    (*idx_input)++;
}

static void make_parenthesis(struct tokenizer_result* tokenizer_result,
                             char parenthesis, size_t* idx_input) {
    struct token token;
    token.value = (char*)malloc(2 * sizeof(char));
    token.value[1] = '\0';

    switch (parenthesis) {
        case '(': {
            token.type = LEFT_PARENTHESIS;
            token.value[0] = '(';
            push_token(tokenizer_result, token);
            break;
        }
        case ')': {
            token.type = RIGHT_PARENTHESIS;
            token.value[0] = ')';
            push_token(tokenizer_result, token);
            break;
        } break;
    }

    (*idx_input)++;
}

static void tokenize(struct tokenizer_result* tokenizer_result, char* input) {
    size_t idx_input, input_len;

    input_len = strlen(input);
    idx_input = 0;

    while (idx_input < input_len) {
        if (is_digit(input[idx_input])) {
            make_number(tokenizer_result, input, &idx_input, input_len);
            continue;
        }

        if (is_operator(input[idx_input])) {
            make_operator(tokenizer_result, input, &idx_input, input_len);
            continue;
        }

        if (is_parenthesis(input[idx_input])) {
            make_parenthesis(tokenizer_result, input[idx_input], &idx_input);
            continue;
        }

        idx_input++;
    }
}

static char* remove_whitespaces(char* input) {
    size_t length = strlen(input);
    char *new_input, *ptr1, *ptr2;

    new_input = (char*)malloc(length * sizeof(char) + 1);
    ptr1 = input;
    ptr2 = new_input;

    while (*ptr1) {
        if (*ptr1 != ' ') {
            *ptr2 = *ptr1;
            ptr2++;
        }
        ptr1++;
    }
    *ptr2 = '\0';

    return new_input;
}

struct tokenizer_result* tokenize_input(char* input) {
    size_t length;
    char* clean_input;
    struct tokenizer_result* tokenizer_result =
        (struct tokenizer_result*)malloc(sizeof(struct tokenizer_result));

    clean_input = remove_whitespaces(input);
    length = strlen(clean_input);
    tokenizer_result->quantity = 0;
    tokenizer_result->tokens =
        (struct token*)malloc(sizeof(struct token) * length);

    tokenize(tokenizer_result, clean_input);
    free(clean_input);

    return tokenizer_result;
}