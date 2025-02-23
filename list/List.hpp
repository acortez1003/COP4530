#ifndef DL_LIST_HPP
#define DL_LIST_HPP

//#include "List.h"

//namespace cop4530
//{

template <typename T>
void List<T>::init()
{
   theSize = 0;
   head = new Node;
   tail = new Node;
   head->next = tail;
   tail->prev = head;
}

// constructor, copy constructor, destructor
template <typename T>
List<T>::List()
{
   init();
}

template <typename T>
List<T>::List(const List & rhs) 
{
   init();
   for( auto & x : rhs )
   push_back(x); 
}

template <typename T>                                  // move constructor
List<T>::List(List && rhs) : theSize{ rhs.theSize}, head{rhs.head}, tail{rhs.tail}
{
   rhs.theSize = 0;
   rhs.head = nullptr;
   rhs.tail = nullptr;
}

template <typename T>
List<T>::List(int num, const T& val)
{
   init();

   for (int i = 0; i < num; ++i)
   {
      push_back(val);
   }
}

template <typename T>
List<T>::List(typename List<T>::const_iterator start, typename List<T>::const_iterator end)
{
   init();

   for (auto itr = start; itr != end; ++itr)
   {
      push_back(*itr);
   }
}

template <typename T>
List<T>::~List()
{
   clear();
   delete head;
   delete tail;
}

template <typename T>
const List<T>& List<T>::operator=(const List &rhs) // Copy assignment operator=
{
   List copy = rhs;
   std::swap( *this, copy);
   return *this;
}

template <typename T>                      // move assignment operator=
List<T>& List<T>::operator=(List<T>&& rhs)
{
   std::swap(theSize, rhs.theSize);
   std::swap(head, rhs.head);
   std::swap(tail, rhs.tail);

   return *this;
}

// member functions 
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
   while( !empty())
      pop_front();
}

template <typename T>
void List<T>::reverse()
{
   if (empty())
   {
      return;
   }

   Node* current = head;

   while (current != nullptr)
   {
      std::swap(current->next, current->prev);
      current = current->prev;
   }

   std::swap(head, tail);
}

template <typename T>
T& List<T>::front()
{
   return *begin();
}

template <typename T>
const T& List<T>::front() const
{
   return *begin();
}

template <typename T>
T& List<T>::back()
{
   return *--end();
}

template <typename T>
const T& List<T>::back() const
{
   return *--end();
}

template <typename T>
void List<T>::push_front(const T & val)
{
   insert(begin(), val);
}

template <typename T>
void List<T>::push_front(T && val)
{
   insert(begin(), std::move(val));
}

template <typename T>
void List<T>::push_back(const T & val)
{
   insert(end(), val);
}

template <typename T>
void List<T>::push_back(T && val)
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
   Node* current = head->next;

   while (current != tail)
   {
      if (current->data == val)
      {
            Node* temp = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
            delete temp;
            --theSize;
      }
      else 
      {
            current = current->next;
      }
   }
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const 
{
   Node* current = head->next;

   bool firstElement = true;
   while (current != tail)
   {
      if (!firstElement)
      {
            os << ofc;
      }
      os << current->data;
      firstElement = false;
      current = current->next;
   }
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
   return iterator( head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
   return const_iterator(head->next);
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
   return iterator(tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
   return const_iterator(tail);
}

template <typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, const T& val)
{
   Node *p = itr.current;
   ++theSize;
   return iterator( p->prev = p->prev->next = new Node{val, p->prev, p});
}

template <typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, T && val)
{
   Node *p = itr.current;
   ++theSize;
   return iterator( p->prev = p->prev->next = new Node{std::move(val), p->prev, p});
}

template <typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator itr)
{
   Node *p = itr.current;
   iterator retVal(p->next);
   p->prev->next = p->next;
   p->next->prev = p->prev;
   delete p;
   --theSize;
   return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator start, typename List<T>::iterator end)
{
   for(iterator itr = start; itr != end;)
      itr = erase(itr);

   return end;
}

// Overloaded operators

template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs)
{
   if (lhs.size() != rhs.size())
   {
      return false;
   }

   auto lhs_itr = lhs.begin();
   auto rhs_itr = rhs.begin();

   while (lhs_itr != lhs.end() && rhs_itr != rhs.end())
   {
      if (*lhs_itr != *rhs_itr)
      {
            return false;
      }
      ++lhs_itr;
      ++rhs_itr;
   }
   return true;
}

template <typename T>
bool operator !=(const List<T> & lhs, const List<T> &rhs)
{
   return !(lhs == rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const List<T> &l)
{
   auto itr = l.begin();

   bool firstElement = true;
   while (itr != l.end())
   {
      if (!firstElement)
      {
            os << ' ';
      }
      os << *itr;
      firstElement = false;
      ++itr;
   }
   return os;
}

template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr}
{
   // empty
}

template <typename T>   
List<T>::const_iterator::const_iterator(Node *p) : current{p} 
{
   //empty
}

template <typename T>
const T& List<T>::const_iterator::operator*() const
{
   return retrieve();
}

template <typename T>
const T* List<T>::const_iterator::operator->() const
{
   return &(this->operator*());
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()
{
   current = current->next;
   return *this;
}

template <typename T> 
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
   const_iterator old = *this;
   ++(*this);
   return old;
}

template <typename T> 
typename  List<T>::const_iterator & List<T>::const_iterator::operator--()
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
   return!( *this == rhs);
}

template <typename T>
T& List<T>::const_iterator::retrieve() const
{
    return current->data;
}

template <typename T>
List<T>::iterator::iterator()
{
   //empty
}

template <typename T> 
List<T>::iterator::iterator(Node *p) : const_iterator(p) 
{
   //empty
}

template <typename T>
T & List<T>::iterator::operator*() 
{
   return const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const
{
   return const_iterator::operator*();
}

template <typename T>
T* List<T>::iterator::operator->()
{
   return &(this->operator*());
}

template <typename T>
const T* List<T>::iterator::operator->() const
{
   return &(this->operator*());
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{
   this->current= this->current->next;
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
typename List<T>::iterator & List<T>::iterator::operator--()
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
//}
#endif