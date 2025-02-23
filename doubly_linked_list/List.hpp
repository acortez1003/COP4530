#ifndef _LIST_HPP
#define _LIST_HPP

//--------------List class functions-------------------
//private List func
template <typename T>
void List<T>::init()    // initializes a new doubly-linked list
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

// BIG FIVE + some more
template <typename T>           // default constructor
List<T>::List()
{
    init();
}

template <typename T>           // copy constructor
List<T>::List(const List &rhs)
{
    init(); // new object
    for(auto &x : rhs)
        push_back(x);
}

template <typename T>           // move constructor
List<T>::List(List &&rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} // transfer of resources
{
    rhs.theSize = 0;        // releasing temp object rhs
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <typename T>           // crease List /w num elements of value val
List<T>::List(int num, const T& val)
{
    init();
    for(int i = 0; i < num; i++)
        push_back(val);
}

template <typename T>           // create new List with elements [start, end]
List<T>::List(const_iterator start, const_iterator end)
{
    init();
    for(auto itr = start; itr != end; ++itr)
        push_back(*itr);
}

template <typename T>
List<T>::List(std::initializer_list<T> iList)
{
    init();
    for(const auto &x: iList)   // const because initializer_list is read-only
        push_back(x);
}

template <typename T>           // destructor
List<T>::~List()
{
    clear();
    delete head;
    delete tail;
}

template <typename T>           // copy assignment operator
const List<T>& List<T>::operator=(const List &rhs)
{
    List copy = rhs;
    std::swap(*this, copy); // deep copy
    return *this;
}

template <typename T>           // move assignment operator
List<T>& List<T>::operator=(List &&rhs)
{
    std::swap(theSize, rhs.theSize);    // transfer of resources
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList)
{
    List temp(iList);
    std::swap(*this, temp);
    return *this;
}

// Member Functions

template <typename T>
int List<T>::size() const
{
    return theSize;
}

template <typename T>
bool List<T>::empty() const
{
    return size() == 0;
}

template <typename T>
void List<T>::clear()
{
    while(!empty())
        pop_front();
}

template <typename T>
void List<T>::reverse()
{
    List temp;
    for(auto& x : *this)
        temp.push_front(x);
    std::swap(*this, temp);
}

template<typename T>
T& List<T>::front()
{
    return *begin();
}

template<typename T>
const T& List<T>::front() const
{
    return *begin();
}

template<typename T>
T& List<T>::back()
{
    return *--end();
}

template<typename T>
const T& List<T>::back() const
{
    return *--end();
}

template<typename T>
void List<T>::push_front(const T &val)
{
    insert(begin(), val);     // inserts in front of head 
}

template<typename T>
void List<T>::push_front(T &&val)
{
    insert(begin(), std::move(val)); 
}

template <typename T>
void List<T>::push_back(const T &val)
{
    insert(end(), val);        // inserts in front of last node
}

template <typename T>
void List<T>::push_back(T &&val)
{
    insert(end(), std::move(val));
}

template <typename T>
void List<T>::pop_front()
{
    erase(begin());
}

template <typename T>
void List<T>::pop_back()
{
    erase(--end());
}

template <typename T>
void List<T>::remove(const T &val)
{
    auto cur = begin();
    for(auto& x : *this)
    {
        if(x == val)
            cur = erase(cur);   // erase moves iterator over
        else
            ++cur;
    }
}

template <typename T>
template <typename PREDICATE>    //ex; isOdd, isPositive
void List<T>::remove_if(PREDICATE pred)
{
    auto cur = begin();
    for(auto& x : *this)
    {
        if(pred(x))
            cur = erase(cur);
        else
            ++cur;
    }
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
    bool first = true;
    for(const auto& x : *this)
    {
        if(!first)
            os << ofc;
        os << x;
        first = false;
    }
}

template <typename T>   // first ACTUAL node
typename List<T>::iterator List<T>::begin()
{
    return iterator(head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(head->next);
}

template <typename T>   // last ACTUAL node
typename List<T>::iterator List<T>::end()
{
    return iterator(tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(tail);
}

template <typename T>   // inserts in FRONT of param
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node(val, p->prev, p));
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T &&val)
{
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node(std::move(val), p->prev, p));
}

template <typename T>   // erase one node
typename List<T>::iterator List<T>::erase(iterator itr)
{
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;
}

template <typename T>   // erase [start, end]
typename List<T>::iterator List<T>::erase(iterator start, iterator end)
{
    for(iterator itr = start; itr != end;)
        itr = erase(itr);
    return end;
}

//--------Nested const_iterator Class-------------
template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr} {}

template <typename T>
const T& List<T>::const_iterator::operator*() const
{
    return retrieve();
}

template <typename T>   // prefix ++i
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    current = current->next;
    return *this;
}

template <typename T>   // postfix i++
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++(*this); // using prefix to not rewrite
    return old;
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator old = *this;
    --(*this);
    return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{
    return current == rhs.current;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{
    return !(*this == rhs); // using == operator as to not rewrite
}

template <typename T>   // protected
T& List<T>::const_iterator::retrieve() const
{
    return current->data;
}

template <typename T>   // protected
List<T>::const_iterator::const_iterator(Node *p) : current{p} {}

//----------Nested iterator Class-------------
template <typename T>
List<T>::iterator::iterator() {}

template <typename T>
T& List<T>::iterator::operator*()
{
    return const_iterator::retrieve();
}

template <typename T>
const T& List<T>::iterator::operator*() const
{
    return const_iterator::operator*();
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator old = *this;
    --(*this);
    return old;
}

template <typename T>   // protected constructor
List<T>::iterator::iterator(Node *p) : const_iterator(p) {}

//stand-alone (comparison operators)
template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs)
{
    if(lhs.size() != rhs.size())
        return false;
    auto l_itr = lhs.begin();   // iterator for lhs
    auto r_itr = rhs.begin();   // iterator for rhs
    // goes through each value and checks if they're equal
    while(l_itr != lhs.end() && r_itr != rhs.end())
    {
        if(*l_itr != *r_itr)
            return false;   // func stops if not equal
        ++l_itr;
        ++r_itr;
    }
    return true;    // if it gets to the end, they're equal
}

template <typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const List<T> &l)
{
    l.print(os);
    return os;
}

#endif //_LIST_HPP