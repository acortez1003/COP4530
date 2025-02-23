#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "stack.h"
using namespace std;
using namespace cop4530;

string in2post(const string &infix);   // infix --> postfix
void postEval(const string &post);           // postfix eval (only int/float)

int precedence(char op);
bool userInput(char input);                 // user input

int main()
{
    string infix, post;
    char user;
    bool exit = false;
    while(!exit)
    {
        cout << "\nEnter infix expression: ";
        getline(cin, infix);

        post = in2post(infix);      // infix to postfix conversion
        cout << "\n" << post;

        postEval(post);             // postfix evaluation

        cout << "\n\nDo you want to enter another infix expression? (Y/N): ";
        cin >> user;
        exit = userInput(user);
        cin.ignore();
    }
    return 0;
}

string in2post(const string &infix)
{
    string postfix;
    Stack<char> opStack;
    string token;               // ex; a_12
    stringstream ss(infix);     // reads infix
    int operandCount = 0, operatorCount = 0;

    while(ss >> token)
    {
        // if beggining of token is letter, then it is an operand
        if(isalpha(token[0]) || isdigit(token[0]))
        {
            postfix += token + " ";
            operandCount++;
        }
        // else, it's an operator
        else if(token[0] == '(')
        // if (
            opStack.push(token[0]);

        else if(token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
        // if it's +, -, *, /
        {
            operatorCount++;
            while(!opStack.empty() && opStack.top() != '(' && precedence(opStack.top()) >= precedence(token[0]))
            // adding to postfix when top of stack is higher than token
            {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            opStack.push(token[0]);     // pushing what we have into stack
        }
        else if(token[0] == ')')
        // if )
        {
            while(!opStack.empty() && opStack.top() != '(')
            {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            if(!opStack.empty() && opStack.top() == '(')
                opStack.pop();      // removes '('
            else
            {
                cout << "\nERROR: Mismatched parantheses.";
                return "";
            }
        }
        else    // not valid operator / operand
        {
            cout << "\nERROR: Not valid operator / operand.";
            return "";
        }
    } // end of string traversal
    while(!opStack.empty())
    {
        if(opStack.top() == '(' || opStack.top() == ')')    // mismatch parantheses check
        {
            cout << "\nERROR: Mismatched parantheses.";
            return "";
        }
        postfix += opStack.top();
        postfix += " ";
        opStack.pop();
    }
    if(operandCount != operatorCount + 1)
    {
        cout << "\nERROR: Incorrect number of operands and operators.";
        return "";
    }
    return postfix;
}

void postEval(const string &post)
{
    Stack<double> evalStack;
    stringstream ss(post);
    string token;
    double op1, op2, result;

    if(post == "")
    {
        cout << "= N/A";
        return;
    }
    while(ss >> token)
    {
        if(isalpha(token[0]))
        {
            cout << "\n= " << post;
            return;
        }
        else if(isdigit(token[0]))          // all digits get pushed
            evalStack.push(stod(token));    // convert string to double
        else
        // operations
        {
            op2 = evalStack.top();
            evalStack.pop();
            op1 = evalStack.top();
            evalStack.pop();
            switch(token[0])
            {
                case '+':
                    result = op1 + op2; break;
                case '-':
                    result = op1 - op2; break;
                case '*':
                    result = op1 * op2; break;
                case '/':
                    result = op1 / op2; break;
            }
            evalStack.push(result);
        }
    }
    cout << "\n= " << evalStack.top();
}

int precedence(char op)
// *, / > +, -
{
    if(op == '+' || op == '-')
        return 1;
    else if(op == '*' || op == '/')
        return 2;
    else
        return -1;
}

bool userInput(char input)
{
    switch(input)
    {
        case 'Y':
        case 'y':
            return false;
            break;
        case 'N':
        case 'n':
            return true;
            break;
    }
    return true;
}