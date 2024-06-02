#ifndef __PARSER_H__
#define __PARSER_H__

#include "../lexer/lexer.h"

struct parser_result {
    struct token *tokens;
    size_t quantity;
};

void parse(char *input);

#endif