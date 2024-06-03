#ifndef __STACK_H__
#define __STACK_H__

#define STACK(type)                                                      \
    struct node {                                                        \
        type data;                                                       \
        struct node *next;                                               \
    };                                                                   \
    struct stack {                                                       \
        struct node *top;                                                \
        size_t size;                                                     \
    };                                                                   \
    struct stack_action_result {                                         \
        uint8_t error;                                                   \
        type data;                                                       \
    };                                                                   \
    void stack_init(struct stack *s) {                                   \
        s->top = NULL;                                                   \
        s->size = 0;                                                     \
    }                                                                    \
    void push(struct stack *stack, type data, void(onerror)(void)) {     \
        struct node *node = (struct node *)malloc(sizeof(struct node));  \
        node->data = data;                                               \
                                                                         \
        if (!node) onerror();                                            \
                                                                         \
        node->next = stack->top;                                         \
                                                                         \
        if (stack->top == NULL) {                                        \
            stack->top = node;                                           \
        } else {                                                         \
            node->next = stack->top;                                     \
            stack->top = node;                                           \
        }                                                                \
                                                                         \
        stack->size++;                                                   \
    }                                                                    \
    struct stack_action_result pop(struct stack *stack) {                \
        struct stack_action_result result;                               \
        struct node *node = stack->top;                                  \
                                                                         \
        if (stack->size == 0 || node == NULL) {                          \
            result.error = 1;                                            \
            return result;                                               \
        };                                                               \
                                                                         \
        stack->top = node->next;                                         \
        result.data = node->data;                                        \
        result.error = 0;                                                \
        free(node);                                                      \
                                                                         \
        stack->size--;                                                   \
                                                                         \
        return result;                                                   \
    }                                                                    \
    struct stack_action_result peek(struct stack *stack) {               \
        struct stack_action_result result;                               \
        struct node *node = stack->top;                                  \
                                                                         \
        if (stack->size == 0 || node == NULL) {                          \
            result.error = 1;                                            \
            return result;                                               \
        }                                                                \
                                                                         \
        result.data = node->data;                                        \
        result.error = 0;                                                \
                                                                         \
        return result;                                                   \
    }                                                                    \
    uint8_t is_empty(struct stack *stack) { return stack->top == NULL; } \
    void clear_stack(struct stack *stack) {                              \
        struct node *node = stack->top;                                  \
                                                                         \
        while (node != NULL) {                                           \
            struct node *next = node->next;                              \
            free(node);                                                  \
            node = next;                                                 \
        }                                                                \
    }

#endif