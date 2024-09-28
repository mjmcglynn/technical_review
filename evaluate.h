#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdbool.h>

enum Operator {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

Operator detectOperatorAndNegativeNumber(const char *&ptr, int &negNum, Operator currOp);
bool evaluate(const char *expression, int &result);
bool evaluateExpression(int &sum, int num, Operator op, int negNum);
bool evaluateParentheses(const char *&ptr, int &innerResult);
int parseNumber(const char *&ptr);

const char *testExpressions[] = {
    "1 + 1 - 33",              // -31
    " 2 + 11",                 // 13
    "-1 +2",                   // 1
    "1 + 3",                   // 4
    "(1 + 3) * 2",             // 8
    "(4 / 2) + 6",             // 8
    "4 + (12 / (1 * 2))",      // 10
    "(1 + (12 * 2))",          // 25
    "(1 + (12 * -2))",         // -23
    "(1 + (12 - 2))",          // 11
    "1 + (2 * (1 + 1)) + 1",   // 6
    "(1 + (2 * (3 + 4))) * 2", // 30
    "(1 - 1)" ,                // 0
    "0 + 1 + 1",                // 2
    "1111111 + 1111111",       // 2222222
    "1 + )",                   // Error
    "1 + -)",                  // Error
    "1/0",                     // Error
    "1 + (2 * (1 + 1)"        // Error
};

int numberOfExpressions = sizeof(testExpressions) / sizeof(testExpressions[0]);

#endif // EVALUATE_H