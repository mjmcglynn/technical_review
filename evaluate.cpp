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
            std::cerr << "Error: Division by zero!" << std::endl;
            return false;
        }
        sum /= num * negNum;
        break;
    default:
        std::cerr << "Unknown operator!" << std::endl;
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
        if (*ptr == '*')
        {
            op = MULTIPLY;
            ++ptr;
            continue;
        }
        if (*ptr == '/')
        {
            op = DIVIDE;
            ++ptr;
            continue;
        }
        if (*ptr == '+')
        {
            op = ADD;
            ++ptr;
            continue;
        }
        if (*ptr == '-')
        {
            if (isdigit(*(ptr + 1))) // If the next character is a digit, it's a negative number
            {
                negNum = -1;
                ++ptr;
            }
            else // Otherwise, it's a subtraction operation
            {
                op = SUBTRACT;
                ++ptr;
                continue;
            }
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
                std::cerr << "Error: Mismatched parentheses!" << std::endl;
                return false;
            }

            if (!evaluate(start, innerResult))
            {
                return false;
            }

            cout << "Inner result: " << innerResult << endl;
            num = innerResult;
            negNum = 1;
            op = ADD;
            ++ptr;
            continue;
        }

        // Parse the number
        while (isdigit(*ptr))
        {
            num = num * 10 + (*ptr - '0');
            ++ptr;
        }

        // Evaluate the expression with the parsed number
        if (num != 0 || negNum == -1)
        { // Check if the number is valid or it's a negative number
            evaluateExpression(sum, num, op, negNum);
        }

        cout << "Num  " << num << " | Operator " << op << " | NegNumber " << negNum << " | sum " << sum << endl;

        if (*ptr == ')')
        {
            cout << sum << endl;
            return true;
        }

        negNum = 1;
    }

    if (parenStack > 0)
    {
        std::cerr << "Error: Mismatched parentheses!" << std::endl;
        return false;
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
            cout << "Result: " << result << " | Test Expression " << i + 1 << ": " << testExpressions[i] << endl;
        }
        else
        {
            cout << "Invalid expression: " << testExpressions[i] << endl;
        }
    }
    return 0;
}
