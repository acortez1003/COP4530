#include "BET.h"

BET::BET() : root{nullptr} {}

BET::BET(const string &postfix)
{
    if(!buildFromPostfix(postfix))
        cout << "\nInvalid postfix expression.";
}

BET::BET(const BET &x)  // copy constructor
{
    root = clone(x.root);   // clone performs deep copy
}

BET::~BET()
{
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string &postfix)
{
    stack<BinaryNode*> stack;   // stack of BET's
    stringstream ss(postfix);
    string token;

    while(ss >> token)
    {
        if(isOperand(token))
        {
           BinaryNode* node = new BinaryNode(token);
           stack.push(node); 
        }
        else if(isOperator(token))
        {
            if(stack.size() < 2)
            // not enough operands
                return false;

            BinaryNode* right = stack.top();
            stack.pop();
            BinaryNode* left = stack.top();
            stack.pop();
            BinaryNode* node = new BinaryNode(token, left, right);
            stack.push(node);                   // pushing new tree
        }
        else
        // not valid operator / operand
            return false;  
    }

    if(stack.size() != 1)
    // must end up with 1 tree
        return false;

    root = stack.top();                         // new root
    return true;
}

const BET& BET::operator=(const BET& x)
{
    if(this != &x)
    {
        makeEmpty(root);
        root = clone(x.root);
    }
    return *this;
}

void BET::printInfixExpression() const
{
    printInfixExpression(root);
}

void BET::printPostfixExpression() const
{
    printPostfixExpression(root);
}

size_t BET::size() const
{
    return size(root);
}

size_t BET::leaf_nodes() const
{
    return leaf_nodes(root);
}

bool BET::empty()
{
    if(root == nullptr)
        return true;
    return false;
}

//----------priv
BET::BinaryNode::BinaryNode(string ele, BinaryNode *l, BinaryNode* r) // creates single node
: element{ele}, left{l}, right{r} {}

void BET::printInfixExpression(BinaryNode *n) const
// in-order traversal
{
    bool needParenth = false;

    if(n == nullptr)
        return;

    if(isOperator(n->element))
    {
        // check left precedence
        if(n->left != nullptr && isOperator(n->left->element) &&
           comparePrecedence(n->left->element[0], n->element[0]))
        {
            needParenth = true;
            cout << "( ";
        }
        // print left
        printInfixExpression(n->left);
        if(needParenth)
        {
            cout << ") ";
            needParenth = false;
        }

        // print root
        cout << n->element << " ";

        // check right precedence
        if(n->right != nullptr && isOperator(n->right->element) &&
           comparePrecedence(n->right->element[0], n->element[0]))
        {
            needParenth = true;
            cout << "( ";
        }
        printInfixExpression(n->right);
        if(needParenth)
        {
            cout << ") ";
            needParenth = false;
        }
    }
    // operand, print directly
    else
    {
        cout << n->element << " ";
    }
}

void BET::makeEmpty(BinaryNode* &t)
{
    if(t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode *t)
{
    if(t == nullptr)
        return nullptr;
    return new BinaryNode(t->element, clone(t->left), clone(t->right));

}

void BET::printPostfixExpression(BinaryNode *n) const
// post-order traversal
{
    if(n != nullptr)
    {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";
    }
}

size_t BET::size(BinaryNode *t) const
{
    if(t == nullptr)
        return 0;

    size_t leftSize = size(t->left);
    size_t rightSize = size(t->right);
    return 1 + leftSize + rightSize;
}

size_t BET::leaf_nodes(BinaryNode *t) const
{
    if(t == nullptr)
        return 0;
    else if(t->left == nullptr && t->right == nullptr)
        return 1;
    else
    {
        size_t leftLeaves = leaf_nodes(t->left);
        size_t rightLeaves = leaf_nodes(t->right);
        return leftLeaves + rightLeaves;
    }
}

bool BET::isOperator(const string &token) const
{
    if(!(token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
        return false;
    return true;
}

bool BET::isOperand(const string &token) const
{
    if(!(isalpha(token[0]) || isdigit(token[0])))
        return false;
    return true;
}

bool BET::comparePrecedence(char n1, char n2) const
{
    int precedence1 = (n1 == '+' || n1 == '-') ? 1 : 2;
    int precedence2 = (n2 == '+' || n2 == '-') ? 1 : 2;
    return precedence1 <= precedence2;
}