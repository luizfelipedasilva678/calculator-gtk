#include <stdio.h>
#include "parser.h"
#include "../lexer/lexer.h"
#include "../data-structures/stack/stack.h"

STACK(struct token);

void parse(char *input) {
    struct stack stack;
    stack_init(&stack);

    struct stack_action_result result = peek(&stack);

    printf("%lu \n", stack.size);

    if (!result.error) {
        printf("%d\n", result.data);
    }

    clear_stack(&stack);
}

int main(void) {
    parse("1 + 2 * -3");
    return 0;
}