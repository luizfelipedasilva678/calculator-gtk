#include <stdio.h>
#include "parser.h"
#include "../data-structures/stack/stack.h"

void parse(char *input) {
    struct tokenizer_result tokenizer_result = tokenize_input(input);

    for (int i = 0; i < tokenizer_result.quantity; i++) {
        printf("%s\n", tokenizer_result.tokens[i].value);
    }
}

int main(void) {
    parse("1 + 2 * -3");
    return 0;
}