#ifndef _STACK_H
#define _STACK_H
#include <iostream>
#include <vector>

namespace cop4530
{

template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();
    Stack(const Stack<T>& rhs);                 // copy constructor
    Stack(Stack<T>&& rhs);                      // move constructor
    Stack<T>& operator=(const Stack<T>& rhs);   // assignment operator=
    Stack<T>& operator=(Stack<T>&& rhs);         // move assignment operator=
    
    bool empty() const;
    void clear();
    void push(const T& x);
    void push(T&& x);
    void pop();
    T& top();
    const T& top() const;
    int size() const;
    void print(std::ostream& os, char ofc = ' ') const;

private:
    std::vector<T> data;

};  // end Stack class

// non-member functions
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a);

template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b);

template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b);

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b);

#include "stack.hpp"


}   // end namespace cop4530

#endif