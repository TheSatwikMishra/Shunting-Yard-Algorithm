#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Method is used to get the precedence of operators
bool letterOrDigit(char c)
{
    // boolean check
    if (isalnum(c))
        return true;
    else
        return false;
}

// Operator having higher precedence
// value will be returned
int getPrecedence(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '^')
        return 3;
    else
        return -1;
}

// Operator has Left --> Right associativity
bool hasLeftAssociativity(char ch)
{
    if (ch == '+' || ch == '-' || ch == '/' || ch == '*') {
        return true;
    } else {
        return false;
    }
}

// Method converts  given infixto postfix expression
// to illustrate shunting yard algorithm
string infixToRpn(string expression)
{
    // Initialising an empty String
    // (for output) and an empty stack
    stack<char> stack;

    // Initially empty string taken
    string output = "";

    // Iterating over tokens using inbuilt
    // .length() function
    for (int i = 0; i < expression.length(); ++i) {
        // Finding character at 'i'th index
        char c = expression[i];

        // If the scanned Token is an
        // operand, add it to output
        if (letterOrDigit(c))
            output += c;

        // If the scanned Token is an '('
        // push it to the stack
        else if (c == '(')
            stack.push(c);

        // If the scanned Token is an ')' pop and append
        // it to output from the stack until an '(' is
        // encountered
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                output += stack.top();
                stack.pop();
            }
            stack.pop();
        }

        // If an operator is encountered then taken the
        // further action based on the precedence of the
        // operator
        else {
            while (!stack.empty() && getPrecedence(c) <= getPrecedence(stack.top())
                   && hasLeftAssociativity(c)) {
                // peek() inbuilt stack function to
                // fetch the top element(token)
                output += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    // pop all the remaining operators from
    // the stack and append them to output
    while (!stack.empty()) {
        if (stack.top() == '(')
            return "This expression is invalid";
        output += stack.top();
        stack.pop();
    }
    return output;
}

// Main driver code
int main()
{
    // Considering random infix string notation
    string expression = "5+2/(3-8)^5^2";

    // Printing RPN for the above infix notation
    // Illustrating shunting yard algorithm
    cout << infixToRpn(expression) << endl;

    return 0;
}
