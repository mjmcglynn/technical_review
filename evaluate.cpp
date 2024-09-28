#include "evaluate.h"
#include <iostream>
#include <cctype>

using namespace std;

bool evaluateExpression(int &sum, int num, Operator op, int negNum)
{
    switch (op)
    {
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
        if (num == 0)
        {
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

bool evaluate(const char *expression, int &result)
{
    Operator op = ADD;
    const char *ptr = expression;

    int negNum = 1;
    int sum = 0;
    int parenStack = 0;
    int innerResult = 0;

    while (*ptr != '\0')
    {
        if (isspace(*ptr))
        {
            ++ptr; // Skip spaces and parentheses
            continue;
        }

        // Set the operator
        switch (*ptr)
        {
        case '*':
            op = MULTIPLY;
            ++ptr;
            break;
        case '/':
            op = DIVIDE;
            ++ptr;
            break;
        case '+':
            op = ADD;
            ++ptr;
            break;
        case '-':
            if (isdigit(*(ptr + 1))) // Handle negative number
            {
                negNum = -1;
                ++ptr;
            }
            else // Handle subtraction operation
            {
                op = SUBTRACT;
                ++ptr;
            }
            break;
        }

        int num = 0;
        if (*ptr == '(')
        {
            parenStack++;                // Increment the count of opening parentheses
            const char *start = ptr + 1; // Start after the opening parenthesis
            while (*(++ptr) != '\0')
            {
                if (*ptr == '(')
                    parenStack++;
                if (*ptr == ')')
                {
                    parenStack--;
                    if (parenStack == 0)
                        break; // Found matching closing parenthesis
                }
            }

            if (parenStack != 0)
            { // If there are unmatched parentheses
                cerr << "Error: Mismatched parentheses | ";
                return false;
            }

            if (!evaluate(start, innerResult))
            {
                return false;
            }
            else
            {
                ++ptr;
            }

            num = innerResult;
            negNum = 1;
        }
        else if (*ptr == ')') // Handle closing parentheses without a match
        {
            if (parenStack == 0)
            {
                cerr << "Error: Unmatched closing parenthesis | ";
                return false;
            }
            return false;
        }

        // Parse the number
        while (isdigit(*ptr))
        {
            num = num * 10 + (*ptr - '0');
            ++ptr;
        }

        if (num != 0 || negNum == -1)
        { // Check if the number is valid or it's a negative number
            evaluateExpression(sum, num, op, negNum);
        }

        if (*ptr == ')')
        {
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
    for (int i = 0; i < numberOfExpressions; ++i)
    {
        int result = 0;
        if (evaluate(testExpressions[i], result))
        {
            cout << "Result: " << result << "\t|\tTest Expression " << i + 1 << ": " << testExpressions[i] << endl;
        }
        else
        {
            cout << "Invalid expression: " << testExpressions[i] << endl;
        }
    }
    return 0;
}
