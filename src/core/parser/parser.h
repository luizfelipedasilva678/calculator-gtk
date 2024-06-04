#ifndef __PARSER_H__
#define __PARSER_H__

#include "../lexer/lexer.h"

#define LEFT_ASSOCIATIVITY 0
#define RIGHT_ASSOCIATIVITY 1

#define PLUS_AND_MINUS_PRECEDENCE 0
#define MULTIPLY_AND_DIVIDE_PRECEDENCE 1
#define NED_AND_POW_PRECEDENCE 2

enum parser_result_status {
    PARSER_SUCCESS = 0,
    PARSER_MISSING_PARENTHESIS = 1,
    PARSER_INTERNAL_ERROR = 2
};

struct parser_result {
    struct token *tokens;
    size_t quantity;
    enum parser_result_status status;
};

struct parser_result *parse(char *input);

#endif