#ifndef __LEXER_H__
#define __LEXER_H__

#define NUMBER 0
#define OPERATOR 1
#define LEFT_PARENTHESIS 2
#define RIGHT_PARENTHESIS 3

struct token {
    uint8_t type;
    char value[50];
};

struct tokenizer_result {
    struct token *tokens;
    size_t quantity;
};

struct tokenizer_result tokenize_input(char *input);

#endif