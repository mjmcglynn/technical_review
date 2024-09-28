#ifndef EVALUATE_H
#define EVALUATE_H

#include <stdbool.h>

enum Operator {
    ADD,        
    SUBTRACT,   
    MULTIPLY,  
    DIVIDE      
};


bool evaluate(const char *expression, int &result);
bool evaluateExpression(int &sum, int num, Operator op, int negNum);

const char *testExpressions[] = {
    " 1 + 1 - 33",               // -1
    "2 + 11",                    // 1
    "1 + 3",                    // 4
    "(1 + 3) * 2",           // 8
    "(4 / 2) + 6",           // 8
    "4 + (12 / (1 * 2))",    // 10
    "(1 + (12 * 2)",         // False (Bracket error)
    "(1 + (12 * -2))",       // -23
    "(1 + (12 - 2))",        // 11
};

int numberOfExpressions = sizeof(testExpressions) / sizeof(testExpressions[0]);


#endif // EVALUATE_H