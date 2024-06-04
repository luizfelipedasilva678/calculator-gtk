#ifndef __EVALUATOR_H__
#define __EVALUATOR_H__

enum evaluation_status {
    EVALUATOR_SUCCESS = 0,
    EVALUATOR_INVALID_EXPRESSION = 1,
    EVALUATOR_INTERNAL_ERROR = 2
};

struct evaluation_result {
    double value;
    enum evaluation_status status;
};

struct evaluation_result evaluate(char *input);

#endif