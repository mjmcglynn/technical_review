#include "evaluate.h"
#include <iostream>
#include <cctype>

using namespace std;

Operator detectOperatorAndNegativeNumber(const char *&ptr, int &negNum, Operator currOp) {
    switch (*ptr) { // Set the operator
        case '*':
            ++ptr;
            return MULTIPLY;
        case '/':
            ++ptr;
            return DIVIDE;
        case '+':
            ++ptr;
            return ADD;
        case '-':
            if (isdigit(*(ptr + 1))) { // Handle negative number
                negNum = -1;
                ++ptr;
            }
            else { // Handle subtraction operation
                ++ptr;
                return SUBTRACT;
            }
        default:
            return currOp;
    }
}

bool evaluateExpression(int &sum, int num, Operator op, int negNum) {
    switch (op) {
        case ADD:
            sum += num * negNum;
            break;
        case SUBTRACT:
            sum -= num * negNum;
            break;
        case MULTIPLY:
            sum *= num * negNum;
            break;
        case DIVIDE:
            if (num == 0) {
                cerr << "Error: Division by zero | ";
                return false;
            }
            sum /= num * negNum;
            break;
        default:
            cerr << "Unknown operator | ";
            return false;
    }
    return true;
}

bool evaluateParentheses(const char *&ptr, int &innerResult) {
    int parenStack = 1;
    const char *start = ptr + 1; // Start after the opening parenthesis
    while (*(++ptr) != '\0') {

        if (*ptr == '(') parenStack++;
        if (*ptr == ')') {
            parenStack--;
            if (parenStack == 0)
                break; // Found matching closing parenthesis
        }
    }

    if (parenStack != 0) {
        cerr << "Error: Mismatched parentheses | ";
        return false;
    }

    if (!evaluate(start, innerResult)) {
        return false;
    }

    ++ptr; // Move past the closing parenthesis
    return true;
}

int parseNumber(const char *&ptr) {
    int num = 0;
    while (isdigit(*ptr)) {
        num = num * 10 + (*ptr - '0'); // Found online - way to covert multiple chars to int
        ++ptr;
    }
    return num;
}

bool evaluate(const char *expression, int &result) {
    Operator op = ADD;
    const char *ptr = expression;

    int negNum = 1;
    int sum = 0;
    int innerResult = 0;

    while (*ptr != '\0') {
        if (isspace(*ptr)) {
            ++ptr; // Skip spaces and parentheses
            continue;
        }

        op = detectOperatorAndNegativeNumber(ptr, negNum, op);

        int num = 0;
        bool numSet = false; // Introduced to negate zero being ignored in evaluationExression if condition - was just checking if 0
        if (*ptr == '(') {
            if (!evaluateParentheses(ptr, innerResult)) return false;
            num = innerResult;
            numSet = true;
            negNum = 1;
        } else if (*ptr == ')') { // Handle closing parentheses without a match
            cerr << "Error: Unmatched closing parenthesis | ";
            return false;
        } else {
            if(!isspace(*ptr)) { // A leading space will cause the number to be 0
                num = parseNumber(ptr); // Parse the number
                numSet = true;
            }
        }

        if (numSet || negNum == -1) { // Check if the number is valid or it's a negative number
            if (!evaluateExpression(sum, num, op, negNum)) return false; // Error - divide by zero or unknown operator
        }

        if (*ptr == ')') { // Close open parentheses
            result = sum;
            return true;
        }

        negNum = 1;
    }
    result = sum;
    return true;
}

int main()
{
    for (int i = 0; i < numberOfExpressions; ++i) {
        int result = 0;
        if (evaluate(testExpressions[i], result)) {
            cout << "Result: " << result << "\t|\tTest Expression " << i + 1 << ": " << testExpressions[i] << endl;
        } else {
            cout << "Invalid expression: " << testExpressions[i] << endl;
        }
    }
    system("pause"); // Adding incase exe is run
    return 0;
}
