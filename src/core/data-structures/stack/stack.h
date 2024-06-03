#ifndef __STACK_H__
#define __STACK_H__

#define STACK(label, type)                                               \
    struct label##_stack_node {                                          \
        type data;                                                       \
        struct label##_stack_node *next;                                 \
    };                                                                   \
    struct label##_stack {                                               \
        struct label##_stack_node *top;                                  \
        size_t size;                                                     \
        size_t node_size;                                                \
    };                                                                   \
    struct label##_stack_action_result {                                 \
        uint8_t error;                                                   \
        type data;                                                       \
    };                                                                   \
    void label##_stack_init(struct label##_stack *s, size_t node_size) { \
        s->top = NULL;                                                   \
        s->size = 0;                                                     \
        s->node_size = node_size;                                        \
    }                                                                    \
    void label##_stack_push(struct label##_stack *stack, type data,      \
                            void(onerror)(void)) {                       \
        struct label##_stack_node *node =                                \
            (struct label##_stack_node *)malloc(stack->node_size);       \
        node->next = NULL;                                               \
                                                                         \
        if (node == NULL) {                                              \
            if (onerror != NULL) onerror();                              \
            return;                                                      \
        }                                                                \
                                                                         \
        node->data = data;                                               \
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
    struct label##_stack_action_result label##_stack_pop(                \
        struct label##_stack *stack) {                                   \
        struct label##_stack_action_result result;                       \
        struct label##_stack_node *node = stack->top;                    \
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
    struct label##_stack_action_result label##_stack_peek(               \
        struct label##_stack *stack) {                                   \
        struct label##_stack_action_result result;                       \
        struct label##_stack_node *node = stack->top;                    \
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
    uint8_t label##_stack_is_empty(struct label##_stack *stack) {        \
        return stack->top == NULL;                                       \
    }                                                                    \
    void label##_stack_clear_stack(struct label##_stack *stack) {        \
        struct label##_stack_node *node = stack->top;                    \
                                                                         \
        while (node != NULL) {                                           \
            struct label##_stack_node *next = node->next;                \
            free(node);                                                  \
            node = next;                                                 \
        }                                                                \
    }

#endif