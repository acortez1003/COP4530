#ifndef _BET_H
#define _BET_H
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
using namespace std;

class BET
{
public:
    BET();
    BET(const string &postfix); // constructor /w param
    BET(const BET&);    // copy constructor
    ~BET();
    bool buildFromPostfix(const string &postfix);
    const BET &operator=(const BET&);
    void printInfixExpression() const;
    void printPostfixExpression() const;
    size_t size() const;
    size_t leaf_nodes() const;
    bool empty();

private:
    struct BinaryNode
    // creates single node
    {
        BinaryNode(string ele, BinaryNode* l = nullptr, BinaryNode* r = nullptr);
        string element;
        BinaryNode* left;
        BinaryNode* right;
    };
    BinaryNode* root;
    void printInfixExpression(BinaryNode *n) const;
    void makeEmpty(BinaryNode* &t);
    BinaryNode* clone(BinaryNode *t);
    void printPostfixExpression(BinaryNode *n) const;
    size_t size(BinaryNode *t) const;
    size_t leaf_nodes(BinaryNode *t) const;

    bool isOperator(const string &token) const;
    bool isOperand(const string &token) const;
    bool comparePrecedence(char n1, char n2) const;
};

#endif