/*
 *  LL.h
 *
 *  COSC 052 Fall 2019
 *  Project #3
 *
 *  Due on: NOV 1, 2019
 *  Author: jsk142
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */

 
 
 
 
#ifndef _COSC052_FALL2019_P3_LL_h_
#define _COSC052_FALL2019_P3_LL_h_
 
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
 
#include "Exceptions.h"
#include "Resources.h"

#define DEBUG_LL_POP_BACK
//#define DEBUG_COPY_LIST
//#define DEBUG_LL_INSERT

using std::vector;
using std::string;
using std::endl;
using std::cout;

 
const int LOOP_OUTPUT_FREQUENCY = 5000;   //new for P3 (optional)
const int SORT_OUTPUT_FREQUENCY = 750;    //new for P3 (optional)
 
/**********************************************************
 *                                                        *
 *                                                        *
 *                  Project #3 classes                    *
 *                                                        *
 *                                                        *
 **********************************************************/
 
 
 
/****************************************************************************
 *                                                                          *
 *                       class Node declaration                             *
 *                                                                          *
 ****************************************************************************/

 
template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node<T> *previous;
     
    Node(T = T(), Node<T> *next = NULL, Node<T> *previous = NULL);
     
}; //END declaration templatized class Node
 
 
 
/****************************************************************************
 *                                                                          *
 *                        class LL declaration                              *
 *                                                                          *
 ****************************************************************************/
 
 
template <typename T>
class LL
{
    template <typename F>
    friend std::ostream& operator<<(std::ostream& os, const LL<F> &rhsObj);
     
private:
    unsigned long count;   
    Node<T> *header;       
    Node<T> *trailer;      
    void copyList(const LL<T>&);
    void initialize();
     
    void remove(unsigned long ndx);
     
public:
    LL();
    LL(const LL<T>&);
    ~LL();
     
    LL<T>& operator=(const LL<T>&);
     
    void insert(unsigned long ndx, T);
     
    void push_back(T);
    void pop_back();
    T& back() const;
     
    void push_front(T);
    void pop_front();
    T& front() const;
     
    void clear();
    bool empty() const;
    unsigned long size() const {return count;}
     
    T& at(unsigned long ndx) const;
    T& operator[](unsigned long ndx) const;
     
    T* toArray() const;
     
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    unsigned long linearSearch(T lookFor) const;
    unsigned long binarySearch(T lookFor) const;
    
     
}; //END declaration templatized class LL


 
 
/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                      class Node implementation                         **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

 
 
/****************************************************************************
 *                         default constructor                              *
 ****************************************************************************/
 
template <typename T>
Node<T>::Node(T infoValue, Node<T> *nPtr, Node<T> *pPtr)
{
    // Constructor with paramters and default constructor
    info = infoValue;
    next = nPtr;
    previous = nPtr;

} //END Node<T>::Node(T infoValue, Node *nodePtr)

 
/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                       class LL implementation                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
 
 
 
/****************************************************************************
 *              non-member function overloaded operator<<                   *
 ****************************************************************************/
 
template <typename F>
std::ostream& operator<<(std::ostream& os, const LL<F> &rhsObj)
{
    // Output the info data member of each node on the linked list on one line
    Node<F> *current = rhsObj.header->next;

    while ( current != rhsObj.trailer )
    {
        os << current->info << " ";
        current = current->next;
    }

    os << endl;
     
    return os;
     
} //END overloaded stream insertion operator for LL<T> class
 
 

/****************************************************************************
 *                  private method copyList of LL class                     *
 ****************************************************************************/
 
template <typename T>
void LL<T>::copyList(const LL<T> &otherLL)
{
    // Test if the list being copied to is empty and delete those contents if necessary
    if ( !this->empty() )
    {
        this->clear();
    }

    // Copies the contents of one existing list into another existing list
    Node<T> *current = otherLL.header->next;

    while ( current != otherLL.trailer )
    {
        this->push_back( current->info );
        current = current->next;
    }
     
} //END function copyList(const LL &otherLL)
 
 
 
/****************************************************************************
 *                 private method initialize of LL class                    *
 ****************************************************************************/
 
template <typename T>
void LL<T>::initialize()
{
    // Initializes the sentinal pointers such that the list is empty and sets count to zero
    header->next = trailer;
    trailer->previous = header;
    header->previous = header;
    trailer->next = trailer;
   
    count = 0;
     
} //END private method LL<T>::initialize

 
 
/****************************************************************************
 *                 private method remove of LL class                    *
 ****************************************************************************/

template <typename T>
void LL<T>::remove(unsigned long ndx)
{
    // Throw out_of_range exception if parameter is not in range
    if ( ndx < 0 || ndx >= count )
    {
        throw std::out_of_range("ERROR: in LL<T>:at() index passed not valid!\n");
    }

    // Remove the object at the specified index on the list
    Node<T> *current = header->next;

    for ( unsigned long i = 0; i < ndx && current != trailer; i++ )
    {
        current = current->next;
    }

    Node<T> *aPtr = current->previous;
    Node<T> *bPtr = current->next;

    bPtr->previous = aPtr;
    aPtr->next = bPtr;

    delete current;
 
    count--;
}


 
/****************************************************************************
 *                         default constructor                              *
 ****************************************************************************/
 
template <typename T>
LL<T>::LL()
{
    // Default constructor 
    header = new Node<T>;
    trailer = new Node<T>;
  
    this->initialize();
     
} //END default constructor for LL class
 
 
 
/****************************************************************************
 *                    copy constructor of LL class                          *
 ****************************************************************************/
 
template <typename T>
LL<T>::LL(const LL<T> &otherLL)
{
    // Copy constructor
    header = new Node<T>;
    trailer = new Node<T>;

    this->initialize();

    this->copyList( otherLL );     
     
} //END LL<T>::LL(const LL<T> &otherLL)
 
 
 
/****************************************************************************
 *                         destructor of LL class                           *
 ****************************************************************************/
 
template <typename T>
LL<T>::~LL()
{
    // Destructor
    std::cout << "LL<T>::~LL() Entered destructor for class LL<T>\n";

    if ( !this->empty() )
    {
        this->clear();
    }
 
    delete header;
    delete trailer;
      
    std::cout << "LL<T>::~LL() Exiting destructor for class LL<T>\n";
    
} //END LL<T>::~LL()
 
 
 
/****************************************************************************
 *                 member function overloaded operator=                     *
 ****************************************************************************/
 
 
template <typename T>
LL<T>& LL<T>::operator=(const LL<T> &rhsLL)
{
    // Overloaded assignment operator
    
    if ( this != &rhsLL )
    {
        this->clear();
        this->copyList( rhsLL );
    } 
     
    return *this;
     
} // END LL<T>::operator=(const LL<T> &rhsLL)
 
 

/****************************************************************************
 *                         member function insert                           *
 ****************************************************************************/
 
template <typename T>
void LL<T>::insert(unsigned long ndx, T infoToAdd)
{
  
#ifdef DEBUG_LL_INSERT
        cout << "Entered function LL<T>::insert() " << endl;
#endif

    // Throw out_of_range exception if paraneter is not in range
    if ( ndx < 0 || ndx > count )
    {
        throw std::out_of_range("ERROR: in LL<T>:at() index passed not valid!\n");
    }

    // Inserts a new node object between two existing nodes already on the doubly-linked list
    Node<T> *addMe = new Node<T>( infoToAdd, NULL, NULL ); 
    Node<T> *current = header;

    for ( unsigned long i = 0; i < ndx && current != trailer; i++ )
    {
        current = current->next;
    }

    Node<T> *aPtr = current->next;

    addMe->previous = current;
    addMe->next = aPtr;
    current->next = addMe;
    aPtr->previous = addMe;
 
    count++;
     
#ifdef DEBUG_LL_INSERT
    cout << "Exiting function LL<T>::insert() " << endl;
#endif
     
} //END memmber function insert
 
 
     
/****************************************************************************
 *                        member function push_back                         *
 ****************************************************************************/
 
template <typename T>
void LL<T>::push_back(T infoToAdd)
{
     
#ifdef DEBUG_LL_PUSH_BACK
    cout << "Entered function LL<T>::push_back() " << endl;
#endif
     
    // Call insert method to append a new node object to the end of a linked list
    this->insert( count, infoToAdd );
        
#ifdef DEBUG_LL_PUSH_BACK
    cout << "Exiting function LL::push_back() " << endl;
#endif
    
} //END LL<T>::push_back(T infoToAdd)
 
 
 
/****************************************************************************
 *                        member function pop_back                          *
 ****************************************************************************/
 
template <typename T>
void LL<T>::pop_back()
{
    // Removes the last object on the list
    // Throw no_such_object exception if the list is empty
    if ( this->empty() )
    {
        throw no_such_object("ERROR: The list is empty!\n");
    }
    else
    {
        this->remove( count - 1 );
    }
     
} //END LL<T>::pop_back()
 
 
 
/****************************************************************************
 *                          member function back                            *
 ****************************************************************************/
 
template <typename T>
T& LL<T>::back() const
{
    // Returns a reference to the info data member of the last object on the list
    // Throw no_such_object exception if the list is empty
    if ( this->empty() )
    {
        throw no_such_object("ERROR: The list is empty!\n");
    }
    else
    {
        return trailer->previous->info;
    }

}
 
 
 
/****************************************************************************
 *                       member function push_front                         *
 ****************************************************************************/
 
template <typename T>
void LL<T>::push_front(T infoToAdd)
{
    // Calls the insert method to insert a new node at the front of a linked list
    this->insert( 0, infoToAdd );
  
} //END LL::push_front(T infoToAdd)
 
 
 
/****************************************************************************
 *                       member function pop_front                          *
 ****************************************************************************/

template <typename T>
void LL<T>::pop_front()
{
    // Removes the first object on the list
    // Throw no_such_object exception if the list is empty
    if ( this->empty() )
    {
        throw no_such_object("ERROR: The list is empty!\n");
    }
    else
    {
        this->remove( 0 );
    }
     
} //END LL<T>::pop_front()

 

/****************************************************************************
 *                          member function front                           *
 ****************************************************************************/

template <typename T>
T& LL<T>::front() const
{
    // Returns a reference to the info data member of the first object on the list
    if ( this->empty() )
    {
        throw no_such_object("ERROR: The list is empty!\n");
    }
    else
    {
        return header->next->info;
    }

}
 
 
 
/****************************************************************************
 *                         member function clear                            *
 ****************************************************************************/
 
template <typename T>
void LL<T>::clear()
{
    // for testing
    unsigned long i = 0;
     
    std::cout << "\tLL<T>::clear() preparing to remove " << count;
    std::cout << " Nodes from the linked list\n";

    // Removes all objects from an existing doubly-linked list
    while ( !this->empty() )
    {
        this->pop_back();
        i++;
    }
      
    std::cout << "\tLL<T>::clear() removed " << i << " Nodes from the list\n";
    std::cout << "\tLL<T>::clear() new count is: " << count << std::endl;
     
} //END LL<T>::clear()
 
 
 
/****************************************************************************
 *                        method empty of LL class                          *
 ****************************************************************************/
 
template <typename T>
bool LL<T>::empty() const
{
    // Returns true if the linked list is empty
    bool answer = true;

    if ( header->next != trailer )
    {
        answer = false;
    }
     
    return answer;
    
} // END LL<T>::empty
 
 

/****************************************************************************
 *                         member function at const                         *
 ****************************************************************************/
 
template <typename T>
T& LL<T>::at(unsigned long location) const
{
    // Throw out_of_range exception if the parameter is within range
    if ( location < 0 || location >= count )
    {
        throw std::out_of_range("ERROR: in LL<T>:at() index passed not valid!\n");
    }
 
    // Returns a reference to the info data member of the object at the specified index
    Node<T> *current = header->next;

    for ( unsigned long i = 0; i < location && current != trailer; i++ )
    {
        current = current->next;
    }
  
    return current->info;
 
} //END LL::at(int location)
 
 

/****************************************************************************
 *                       overloaded operator[] const                        *
 ****************************************************************************/

template <typename T>
T& LL<T>::operator[](unsigned long ndx) const
{
    // Call at method to return a reference to the info data member at the specified index
    return this->at(ndx);
 
} //END overloaded subscript operator
 
     
 
/****************************************************************************
 *                         member function toArray                          *
 ****************************************************************************/
     
template <typename T>
T* LL<T>::toArray() const
{
    // IMPORTANT NOTE!!!
    // remember that the code calling this method is responsible
    // for deallocating this dynamically allocated array
     
    // Creates a dynamic array of type T
    T *tPtr = new T[count];
   
    for ( unsigned long i = 0; i < count; i++ )
    {
        tPtr[i] = this->at(i);
    }

    return tPtr;
     
} // END LL<T>::toArray()
 

 
/****************************************************************************
 *                       member function bubbleSort                         *
 ****************************************************************************/
 
template <typename T>
void LL<T>::bubbleSort()
{
    cout << "Entered member function bubbleSort()" << endl;
     
    //for testing
    unsigned long swapCount = 0;

    // Sorts the contents of the linked list in ascending order using the bubble sort algorithm
    unsigned long iteration = 0;
    unsigned long index = 0;
    T temp;

    for ( iteration = 1; iteration < count; iteration++ )
    {     
        for ( index = 0; index < count - iteration; index++ )
        {
            if ( this->at(index) > this->at(index + 1) )
            {
                // must swap this pair of values
                swapCount++;
                temp = this->at(index);
                this->at(index) = this->at(index + 1);
                this->at(index + 1) = temp;
            }
        }
    }
     
    cout << "Exiting member function bubbleSort() \nresults: swapCount = " << swapCount << endl;
     
} //END member function LL<T>::bubbleSort()

 

/****************************************************************************
 *                     member function selectionSort                        *
 ****************************************************************************/
         
template <typename T>
void LL<T>::selectionSort()
{
    cout << "Entered function selectionSort() " << endl;
 
    //for testing
    unsigned long  swapCount = 0;

    // Sorts the contents of the linked list in ascending order
    // using the selection sort algorithm
    unsigned long index = 0;
    unsigned long smallestIndex = 0;
    unsigned long location = 0;
    T temp = 0;

    for ( index = 0; index < count - 1; index++ )
    {
        smallestIndex = index;
 
        for ( location = index + 1; location < count; location++ )
        {
            if ( this->at(location) < this->at(smallestIndex) )
            {
                smallestIndex = location;
            }
        }

        temp = this->at(smallestIndex);
        this->at(smallestIndex) = this->at(index);
        this->at(index) = temp;

        swapCount++;
    }
     
    cout << "Exiting function selectionSort() \nresults: swapCount = " << swapCount << endl;
     
} // END void LL<T>::selectionSort()

     
     
/****************************************************************************
 *                     member function insertionSort                        *
 ****************************************************************************/
 
template <typename T>
void LL<T>::insertionSort()
{
    cout << "Entered function insertionSort() " << endl;
    
    //for testing
    unsigned long  swapCount = 0;

    // Sorts the contents of the linked list in ascending order 
    // using the insertion sort algorithm
    unsigned long firstOutOfOrder = 0;
    unsigned long location = 0;
    T temp;

    for ( firstOutOfOrder = 1; firstOutOfOrder < count; firstOutOfOrder++ )
    {
        if ( this->at(firstOutOfOrder) < this->at(firstOutOfOrder - 1) )
        {
            temp = this->at(firstOutOfOrder);
            location = firstOutOfOrder;
            
            do
            {
                this->at(location) = this->at(location - 1);
                location--;
                swapCount++;
            }
            while ( location > 0 && this->at(location - 1) > temp );

            this->at(location) = temp; 	

        }
    }   
    
    cout << "Exiting function insertionSort() \nresults: swapCount = " << swapCount << endl;
   
} // END void LL<T>::insertionSort()
     
        
         
/****************************************************************************
 *                      member function linearSearch                        *
 ****************************************************************************/
 
template <typename T>
unsigned long LL<T>::linearSearch(T lookFor) const
{
    cout << "Entered function linearSearch(" << lookFor << ")" << endl;
 
    // Uses the linear search algorithm to locate the first occurance of a node,
    // storing info matching the specified value to locate.
    unsigned long index = 0;
    bool found = false;

    while ( index < count && !found )
    {
        if ( this->at(index) == lookFor )
        {
            found = true;
        }
        else
        {  
            index++;
        }     
    }

    if ( !found )
    {
        throw no_such_object("no node on the list contains the specified value.\n");
    }
     
    return index;
     
} // END unsigned long LL<T>::linearSearch(T lookFor)
 
         
         
/****************************************************************************
 *                      member function binarySearch                        *
 ****************************************************************************/
 
template <typename T>
unsigned long LL<T>::binarySearch(T lookFor) const
{
    cout << "Entered function binarySearch(" << lookFor << ")" << endl;
 
    // Uses the binary search algorithm to locate the first occurance of a node 
    // storing info matching the specified value to locate.    
    bool found = false;
 
    unsigned long index = 0;

    long first = 0, last = 0, mid = 0;

    last = count - 1;
  
    while ( first <= last && !found )
    {
        mid = ( first + last ) / 2;
    
        if ( this->at(mid) == lookFor )
        {
            found = true;
        }
        else if ( this->at(mid) > lookFor )
        {
            last = mid - 1;
        }
        else
        {
            first = mid + 1;
        }
    }

    if ( !found )
    {
       throw no_such_object("no node on the list contains the specified value.\n");
    }

    index = mid;
    
    cout << "Exiting function binarySearch()" << endl;
     
    return index;
     
} // END unsigned long LL<T>::binarySearch(T lookFor)
 
         
         
 
 
 
#endif /*  _COSC052_FALL2019_P3_LL_h_  */
