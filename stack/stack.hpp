#ifndef _STACK_HPP
#define _STACK_HPP

template <typename T>
Stack<T>::Stack() {}

template <typename T>
Stack<T>::~Stack() {}

template <typename T>
Stack<T>::Stack(const Stack<T>& rhs) : data(rhs.data) {}

template <typename T>
Stack<T>::Stack(Stack<T>&& rhs) : data(std::move(rhs.data)) {}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
    data = rhs.data;
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& rhs)
{
    data = std::move(rhs.data);
    return *this;
}

template <typename T>
bool Stack<T>::empty() const
{
    return data.empty();
}

template <typename T>
void Stack<T>::clear()
{
    data.clear();
}

template <typename T>
void Stack<T>::push(const T& x)
{
    data.push_back(x);
}

template <typename T>
void Stack<T>::push(T&& x)
{
    data.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop()
{
    data.pop_back();
}

template <typename T>
T& Stack<T>::top()
{
    return data.back();    // 'back' is the top of the stack
}

template <typename T>
const T& Stack<T>::top() const
{
    return data.back();
}

template <typename T>
int Stack<T>::size() const
{
    return data.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
    for(auto it = data.rbegin(); it != data.rend(); ++it)
        os << *it << ofc; 
}

// non-member functions
template <typename T>
std::ostream& operator<<(std::ostream&os, const Stack<T>& a)
{
    a.print(os);
    return os;
}

template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b)
{
    Stack<T> tempA = a;
    Stack<T> tempB = b;
    if(a.size() != b.size())
        return false;
    while(!tempA.empty())
    {
        if(tempA.top() != tempB.top())
            return false;
        tempA.pop();
        tempB.pop();
    }
    return true;
}

template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b)
{
    return !(a == b);
}

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b)
{
    Stack<T> tempA = a;
    Stack<T> tempB = b;

    if(a.size() > b.size())
        return false;
    while(!tempA.empty())
    {
        if(tempA.top() > tempB.top())
            return false;
        tempA.pop();
        tempB.pop();
    }
    return true;
}

#endif