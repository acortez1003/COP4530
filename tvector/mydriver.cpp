#include <iostream>
#include <string>
#include "tvector.h"
using namespace std;

int main()
{
    TVector<int> v1;    // type int
    TVectorIterator<int> intIterator = v1.GetIterator();

    //IsEmpty
    cout << "\nIsEmpty test:";
    if(v1.IsEmpty())
        cout << "\nThis vector is empty. Test Passed.";
    
    //Insert
    cout << "\n\nInserting 20 as first value in vector.";
    v1.Insert(intIterator, 20);
    cout << "\nShould print one value (20): ";
    v1.Print(std::cout);

    //Clear
    cout << "\n\nClearing vector. Should print nothing: ";
    v1.Clear();
    v1.Print(std::cout);
    cout << "\nPass.";

    //Constructor with param
    TVector<int> newV(5, 20);
    cout << "\n\nTesting constructor with 2 param. \nNew vector has 20 values of the number 5:\n";
    newV.Print(std::cout);

    //Copy constructor and assignment operator
    //Testing type double
    cout << "\n\nCreating vector of type double.";
    TVector<double> OGVector;
    TVectorIterator<double> OGiter = OGVector.GetIterator();
    OGVector.Insert(OGiter, 51.5);
    OGVector.Insert(OGiter, 23.6);
    OGVector.Insert(OGiter, 11.2);
    cout << "\nPrinting original vector: ";
    OGVector.Print(std::cout);
    TVector<double> copy(OGVector);
    cout << "\nPrinting copy: ";
    copy.Print(std::cout);

    TVector<double> assigned;
    assigned = OGVector;
    cout << "\n\nTesting assignment operator: ";
    assigned.Print(std::cout);

    //GetSize
    cout << "\n\nTesting GetSize. Should be 3: " << OGVector.GetSize();

    //InsertBack
    cout << "\n\nTesting InsertBack. \nInserting value 82.5 at back: \n";
    OGVector.InsertBack(82.5);
    OGVector.Print(std::cout);

    //RemoveBack
    cout << "\n\nTesting RemoveBack. Should remove 82.5: \n";
    OGVector.RemoveBack();
    OGVector.Print(std::cout);


    //GetFirst and GetLast
    cout << "\n\nTesting GetFirst and GetLast. \nShould return 11.2 and then 51.5: "
         << OGVector.GetFirst() << " " << OGVector.GetLast();

    //Creating a new vector and testing all Insert and Remove
    TVector<double> v2;
    TVectorIterator<double> v2Iterator = v2.GetIterator();
    cout << "\n\nTesting insert function 9 times:";
    double x = 0.5;
    for(int i = 0; i < 10; i++)
    {
        cout << "\nv2 loop #" << i << ": ";
        v2.Print(std::cout);
        v2.Insert(v2Iterator, x);
        x += 1;
    }
    cout << "\n\nTesting remove function:"
         << "\nShould remove from first index.";
    for(int i = 0; i < 10; i++)
    {
        cout << "\nv2 loop #" << i << ": ";
        v2.Print(std::cout);
        v2.Remove(v2Iterator);
    }

    cout << "\n\nAdding everything back as it was using Insert.";
    x = 0.5;
    for(int i = 0; i < 10; i++)
    {
        v2.Insert(v2Iterator, x);
        x += 1;
    }
    TVectorIterator<double> v2Iterator2 = v2.GetIteratorEnd();
    v2Iterator = v2.GetIterator();
    v2Iterator.Next();
    cout << "\n\nRemoving everything but the first and last value: ";
    cout << "\nBefore removal: ";
    v2.Print(std::cout);
    v2.Remove(v2Iterator, v2Iterator2);
    cout <<"\nAfter removal: ";
    v2.Print(std::cout); 

    //Resetting vector and iterators
    cout << "\n\nRemoving at different ranges.";
    v2.Clear();
    v2Iterator = v2.GetIterator();
    x = 0.5;
    for(int i = 0; i < 10; i++) // resetting vector
    {
        v2.Insert(v2Iterator, x);
        x += 1;
    }

    v2Iterator = v2.GetIterator();  // setting up iterators
    v2Iterator2 = v2.GetIterator();
    v2Iterator2.Next();
    v2Iterator2.Next();

    cout << "\nv2 before removal: ";
    v2.Print(std::cout);

    TVector<double> v2Copy(v2); // creating a copy

    for(int i = 0; i < 10; i++)     // removing by a range, resetting vector, moving over
    {
        v2.Remove(v2Iterator, v2Iterator2);
        cout << "\nv2: ";
        v2.Print(std::cout);
        v2 = v2Copy; // resetting vector
        v2Iterator.Next();  // moving iterators to next range
        v2Iterator2.Next();
    }

    //InsertBack and RemoveBack more
    cout << "\n\nRemoving and Inserting to back multiple times.";
    TVector<int> v3(3, 3);
    cout << "\nCreating new vector first: ";
    v3.Print(std::cout);

    int y = 6; // what we're adding to vector
    for(int i = 0; i < 10; i++)
    {
        v3.InsertBack(y);
        cout << "\nINSERT: ";
        v3.Print(std::cout);
        cout << "\nREMOVE: ";
        v3.RemoveBack();
        v3.Print(std::cout);
        y *= 2;
    }

    //Using iterator to traverse: Front to Back
    cout << "\n\nTraversing vector Front to Back";
    v2.Clear();                     // resetting vector
    v2Iterator = v2.GetIterator();
    x = 0.5;
    for(int i = 0; i < 10; i++)
    {
        v2.Insert(v2Iterator, x);
        x += 1;
    }

    cout << "\nEntire vector: ";
    v2.Print(std::cout);

    v2Iterator = v2.GetIterator();  // resetting iterator
    for(int i = 0; i < 10; i++)
    {
        cout << "\nData at index [" << i << "]: " << v2Iterator.GetData();
        v2Iterator.Next();
    }    

    // Back to Front
    cout << "\n\nTraversing vector Back to Front";
    cout << "\nEntire vector: ";
    v2.Print(std::cout);

    v2Iterator = v2.GetIteratorEnd();  // resetting iterator
    for(int i = 10; i > 0; i--)
    {
        cout << "\nData at index [" << i - 1 << "]: " << v2Iterator.GetData();
        v2Iterator.Previous();
    }
    return 0;
}