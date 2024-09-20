#include <iostream>
#include <string>
#include <cctype>  // I'm using isdigt in is_operand because it's a standard library function
#include "stack_L_T.h"  

using namespace std;

/**
 * @brief Get the priority of an operator
 * 
 * @param op Operator whose priority is needed
 * @return int Priority of the operator (higher number means higher priority)
 */
int get_priority(char op);

/**
 * @brief Check if the character is an operator
 * 
 * @param ch Character to check
 * @return true If the character is an operator (+, -, *, /)
 * @return false Otherwise
 */
bool is_operator(char ch);

/**
 * @brief Check if the character is an operand (a digit)
 * 
 * @param ch Character to check
 * @return true If the character is a digit (0-9)
 * @return false Otherwise
 */
bool is_operand(char ch);

/**
 * @brief Convert an infix expression to postfix
 * 
 * @param infix The infix expression as a string
 * @return string The converted postfix expression
 */
string infix_to_postfix(const string& infix);

/**
 * @brief Evaluate a postfix expression
 * 
 * @param postfix The postfix expression as a string
 * @return double The evaluated result of the postfix expression
 */
double evaluate_postfix(const string& postfix);

int main() {
    try {
        string infix;
        //cout << "Enter an infix expression: ";
        cin >> infix;

        // Convert infix to postfix
        string postfix = infix_to_postfix(infix);
        cout << postfix << endl;
        
        // Evaluate the postfix expression
        double result = evaluate_postfix(postfix);
        cout << result << endl;

    } catch (const char* msg) {

        // Catch and display any format errors
        cout << msg << endl;  
    } 

    // Catch underflow errors
    catch (Stack<int>::Underflow) {
        cout << "The expression is in a wrong format" << endl;  
    }

    return 0;
}

/**
 * @brief Get the priority of an operator. Higher values indicate higher precedence.
 * 
 * @param op The operator character ('+', '-', '*', '/')
 * @return int The priority of the operator
 */
int get_priority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;  // Parentheses and invalid characters get priority 0
}

/**
 * @brief Check if a character is a valid operator
 * 
 * @param ch Character to check
 * @return true If character is an operator (+, -, *, /)
 * @return false Otherwise
 */
bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

/**
 * @brief Check if a character is a valid operand
 * 
 * @param ch Character to check
 * @return true If character is an operand
 * @return false Otherwise
 */
bool is_operand(char ch) {
    return isdigit(ch); 
}

/**
 * @brief Convert an infix expression to postfix notation using a stack.
 * 
 * @param infix The infix expression as a string
 * @return string The converted postfix expression
 * 
 * @throws const char* "The expression is in a wrong format" for invalid input
 */
string infix_to_postfix(const string& infix) {
    Stack<char> stack; // Create a stack to store operators
    string postfix = ""; // Initialize an empty string to store the postfix expression

    // Iterate over the characters in the infix expression
    for (char token : infix) {
        if (is_operand(token)) {

            // Append operand (digit) to postfix
            postfix += token;  
        } else if (token == '(') {

            // Push opening parenthesis to stack
            stack.push(token);  
        } else if (token == ')') {

            // Pop and append everything until '(' is found
            while (!stack.empty() && stack.getTop() != '(') {
                postfix += stack.getTop();
                stack.pop();
            }

            // Mismatched parentheses
            if (stack.empty()) throw "The expression is in a wrong format"; 

            // Remove the '(' from the stack
            stack.pop();  
        } else if (is_operator(token)) {

            // Pop operators from stack with higher or equal priority
            while (!stack.empty() && get_priority(stack.getTop()) >= get_priority(token)) {
                postfix += stack.getTop();
                stack.pop();
            }

            // Push current operator to stack
            stack.push(token);  
        } else {

            // Invalid character found
            throw "The expression is in a wrong format";
        }
    }

    // Pop remaining operators from the stack
    while (!stack.empty()) {
        if (stack.getTop() == '(' || stack.getTop() == ')') throw "The expression is in a wrong format";
        postfix += stack.getTop();
        stack.pop();
    }

    return postfix;  // Return the postfix expression
}

/**
 * @brief Evaluate a postfix expression using a stack
 * 
 * @param postfix The postfix expression as a string
 * @return double The result of evaluating the expression
 * 
 * @throws Stack<int>::Underflow if there is a stack underflow (invalid expression)
 * @throws const char* "The expression is in a wrong format" for other errors
 */
double evaluate_postfix(const string& postfix) {
    Stack<double> stack;

    for (char token : postfix) {
        if (is_operand(token)) {

            // Convert the character digit to an integer and push to stack
            stack.push(token - '0');
        } else if (is_operator(token)) {

            // Pop the top two operands from the stack
            if (stack.empty()) throw Stack<int>::Underflow();
            double operand2 = stack.getTop();
            stack.pop();

            if (stack.empty()) throw Stack<int>::Underflow();
            double operand1 = stack.getTop();
            stack.pop();

            // Perform the operation
            double result = 0;

            // Perform the operation based on the operator
            switch (token) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
            }

            // Push the result onto the stack
            stack.push(result);  
        } else {

            // Throw an error for invalid characters
            throw "The expression is in a wrong format"; 
        }
    }

    // Check for leftover items in the stack
    if (stack.empty()) throw Stack<int>::Underflow();  
    double result = stack.getTop();
    stack.pop();

    // Leftover items in stack
    if (!stack.empty()) throw "The expression is in a wrong format";  

    // Return the final result
    return result;  
}
