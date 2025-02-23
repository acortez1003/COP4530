#ifndef _TVECTOR_H
#define _TVECTOR_H
using namespace std;

template<typename T> // stand-alone, concatenates two TVector objects
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2)
{
    TVector<T> tNew;
    TVectorIterator<T> iter1 = t1.GetIterator();
    TVectorIterator<T> iter2 = t2.GetIterator();
    while(iter1.HasNext())
        tNew.Insert(iter1.Next(), iter1.GetData());
    while(iter2.HasNext())
        tNew.Insert(iter2.Next(), iter2.GetData());
    return tNew;
}

//-----TVector Definitions-----
template<typename T> // default constructor
TVector<T>::TVector()
{
    capacity = SPARECAPACITY;
    size = 0;
    array = new T[capacity]{};
}

template<typename T> // constructor /w param
TVector<T>::TVector(T val, int num)
{
    size = num;
    capacity = num + SPARECAPACITY;
    array = new T[capacity];
    for(unsigned int i = 0; i < num; i++)
        array[i] = val;
}

template<typename T> // destructor
TVector<T>::~TVector()
{
    delete [] array;
}

template<typename T> // copy constructor
TVector<T>::TVector(const TVector<T>& v)
{
    capacity = v.capacity;
    size = v.size;

    array = new T[v.capacity];

    for(unsigned int i = 0; i < size; i++)
        array[i] = v.array[i];
}

template<typename T> // copy assignment operator
TVector<T>& TVector<T>::operator=(const TVector<T>& v)
{
    if(this != &v)
    {
        delete [] array;
        capacity = v.capacity;
        size = v.size;
        array = new T[v.capacity];
        for(unsigned int i = 0; i < size; i++)
            array[i] = v.array[i];
    }
    return *this;   // return object itself
}

template<typename T> // move constructor
TVector<T>::TVector(TVector<T> && v)
{
    capacity = v.capacity;
    size = v.size;

    array = new T[v.capacity];

    for(unsigned int i = 0; i < size; i++)
        array[i] = v.array[i];
}

template<typename T> // move assignment operator
TVector<T>& TVector<T>::operator=(TVector<T> && v)
{
    if(this != &v)
    {
        delete [] array;
        capacity = v.capacity;
        size = v.size;
        array = new T[v.capacity];
        for(int i = 0; i < size; i++)
            array[i] = v.array[i];
    }
    return *this;   // return object itself
}

template<typename T> // container empty?
bool TVector<T>::IsEmpty() const
{
    if(size == 0)
        return true;
    return false;
}

template<typename T> // clears vector, reset to empty
void TVector<T>::Clear()
{
    delete [] array;
    capacity = SPARECAPACITY;
    size = 0;
    array = new T[capacity]{};
}

template<typename T> // return size of vector
int TVector<T>::GetSize() const
{
    return size;
}

template<typename T> // insert data d as last element
void TVector<T>::InsertBack(const T& d)
{
    if(size == capacity) // if maxxed
        SetCapacity(2 * capacity);
    if(IsEmpty())
        array[0] = d;
    else
    {
        array[size] = d;
        size += 1;
    }
}

template<typename T> // remove last element
void TVector<T>::RemoveBack()
{
    if(!IsEmpty()) // if not empty
        Remove(GetIteratorEnd());
}

template<typename T> // return first element of vector
T& TVector<T>::GetFirst() const
{
    if(IsEmpty())
        return dummy;
    return array[0];
}

template<typename T> // return last element of vector
T& TVector<T>::GetLast() const
{
    if(IsEmpty())
        return dummy;
    return array[size - 1];
}

template<typename T> // return iterator to first item
TVectorIterator<T> TVector<T>::GetIterator() const
{
    TVectorIterator<T> itr;
    if(IsEmpty())
        return itr;
    itr.index = 0;
    itr.ptr = &array[0];
    itr.vsize = size;
    return itr;
}

template<typename T> // return iterator to last item
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
    TVectorIterator<T> itr;
    if(IsEmpty())
        return itr;
    itr.index = size - 1;
    itr.ptr = &array[size - 1];
    itr.vsize = size;
    return itr;
}

template<typename T> // reset the capacity of the vector to c
void TVector<T>::SetCapacity(unsigned int c)
{
    T* temp = new T[c];
    for(unsigned int i = 0; i < size; i++)
        temp[i] = array[i];
    delete [] array;
    array = temp;
    capacity = c;
}

template<typename T>
// insert data element d just before item as pos position
// return iterator to the new data item
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d)
{
    if(IsEmpty())
    {
        array[0] = d;
        pos.index = 0;
        pos.ptr = &array[0];
        size += 1; //increase size
        pos.vsize = size;
    }
    else if(pos.index >= size || pos.index < 0)
    {
        if(size == capacity) // increase size
            SetCapacity(size * 2);
        array[size] = d;
        size += 1;
        pos.index = size - 1;
        pos.ptr = &array[pos.index];
        pos.vsize = size;
    }
    else
    {
        if(size == capacity)
            SetCapacity(size * 2);
        for(int i = size; i > static_cast<int>(pos.index); i--)
            array[i] = array[i - 1];
        size += 1;
        array[pos.index] = d; // index stays the same
        pos.ptr = &array[pos.index];
        pos.vsize = size;
    }
    return pos;
}

template<typename T>
// remove data item at position pos
// return iterator to the item that comes after the one being deleted
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
    if(IsEmpty() || pos.index >= size || pos.index < 0)
        return pos; // do nothing
    // shift over 1 to the left
    for(unsigned int i = pos.index; i < size - 1; i++)
        array[i] = array[i + 1];
    size -= 1;
    pos.ptr = &array[pos.index];
    pos.vsize = size;
    return pos;
}

template<typename T>
// remove data item in range [pos1, pos2)
// return iterator to the item that comes after the deleted items
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
    unsigned int diff = pos2.index - pos1.index;
    TVectorIterator<T> posNew;

    if(IsEmpty())
        return posNew;
    if(pos1.index >= pos2.index)
        return pos1;

    // shifts over the range
    for(unsigned int i = pos1.index; i < size - diff; i++)
        array[i] = array[i + diff];
    size -= diff;
    posNew.index = pos1.index;
    posNew.ptr = &array[posNew.index];
    posNew.vsize = size;
    return posNew;
}

template<typename T> // print vector contents in order, separated by delim
void TVector<T>::Print(std::ostream& os, char delim) const
{
    os << array[0]; //without delim
    for(unsigned int i = 1; i < size; i++)
        os << delim << array[i];
}

//-----TVectorIterator Definitons-------
template<typename T> // default constructor
TVectorIterator<T>::TVectorIterator()
{
    index = 0;
    ptr = nullptr;
    vsize = 0;
}

template<typename T> // next item available?
bool TVectorIterator<T>::HasNext() const
{
    return(index + 1 < vsize);
}

template<typename T> // previous item available?
bool TVectorIterator<T>::HasPrevious() const
{
    return(index > 0);
}

template<typename T> // advance to next item
TVectorIterator<T> TVectorIterator<T>::Next()
{
    if(HasNext())
    {
        index += 1;
        ptr += 1;
    }
    return *this;
}

template<typename T> // move to previous item
TVectorIterator<T> TVectorIterator<T>::Previous()
{
    if(HasPrevious())
    {
        index -= 1;
        ptr -= 1;
    }
    return *this;
}

template<typename T> // return data element of current node
T& TVectorIterator<T>::GetData() const
{
    if (ptr && index < vsize) 
        return *ptr;
    else
        return TVector<T>::dummy;
}

#endif