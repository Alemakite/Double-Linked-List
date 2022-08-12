#pragma once

/*! \file doubleLinkedList.h 
    \brief File containing Double Linked List class
*/


#include <memory>
#include <string>
#include <algorithm>
#include "listNode.h"

using namespace std;

/*<! \class DoubleLinkedList
*     \brief Double linked list data structure.
*/
template <class G>
class DoubleLinkedList
{
private :
    unsigned int size; //!< Number of elements in the list
    shared_ptr<ListNode<G>> front;  //!< First node in the list
    shared_ptr<ListNode<G>> back;   //!< Last node in the list
    shared_ptr<ListNode<G>> current;    //!< Node created as first becomes the current, then the current pointer
                                        //!  can bo moved through the list backwards and forwards 'selecting' different nodes.
public :
    DoubleLinkedList(); //!<  default Contructor
    void push_front(G newNode); //!<  Adds a new element to the beginning of list
    void push_back(G newNode); //!<  Adds a new element to the end of list
    void push_before_curr(G newNode);   //<! Adds a new element before the current element
    void push_after_curr(G newNode);     //<!  Adds a new element after the current element
    G pop_front();  //!<  Removes a front node from the list
    G pop_back();   //!<  Removes a back node from the list
    int getSize();  //!<  Returns the size of the list
    bool isEmpty(); //!< Returns true if the list is empty
    G look_front(); //!<  Returns data stored in the first node
    G look_back(); //!<  Returns data stored in the last node
    G look_current(); //!<  Returns data stored in the current node
    void traverse_forwards();   //!<  Moves the current pointer forwards in the list
    void traverse_backwards();  //!<  Moves the current pointer backwards in the list
    void printList(); //!< Function to print the list
    void listSort(); //!< Function to sort the list
    void swap(shared_ptr<ListNode<G>> first, shared_ptr<ListNode<G>> second);
    bool compareData(shared_ptr<ListNode<G>> first, shared_ptr<ListNode<G>> second);

};

// Below are the definitions for the forward declarated methods

//!     Assigns size to be 0 and nullptr to each of the pointers as the structure is empty.
template <class G>
DoubleLinkedList<G>::DoubleLinkedList()
{
    front = nullptr;    //no data to point, so each of the pointers are null
    back = nullptr;
    current = nullptr;
    size = 0; //empty list
}

//!< \brief  Creates a temporary shared pointer to the listNode object, newly created on the Heap, with the value.
//! 
//!     If the list is empty, makes the new node front, back and current of the list ( as it is the only element ) and
//!     sets the node's next and previous to nullptr ( nothing to point to ) .
//! 
//!     If the list is not empty, sets the new node's previous to nullptr and next to front, sets the front's previous to be new node, then 
//!     makes the new node front.
//!     
//!     At the end, increase the size of list.
template <class G>
void DoubleLinkedList<G>::push_front(G val)
{
    shared_ptr<ListNode<G>> temp = shared_ptr<ListNode<G>>(new ListNode<G>(val));
    if (isEmpty())
    {
        temp->setNext(nullptr);
        temp->setPrevious(nullptr);
        front = temp;
        back = temp;
        current = temp;
    }
    else 
    {
        temp->setNext(front);
        temp->setPrevious(nullptr);
        front->setPrevious(temp);
        front = temp;
    }
    size++;
}

//!< \brief  Adds a new element to the end of list
//!     Creates a temporary shared pointer to the listNode object, newly created on the Heap, with the value.
//!     If the list is empty, makes the new node front, back and current of the list ( as it is the only element ) and
//!     sets the node's next and previous to nullptr ( nothing to point to ) .
//! 
//!     If the list is not empty, sets the new node's next to nullptr and previous to back, sets the back's next to be the new node, then 
//!     makes the new node back.
//!     
//!     At the end, increase the size of list.
template <class G>
void DoubleLinkedList<G>::push_back(G val)
{
    shared_ptr<ListNode<G>> temp_back = shared_ptr<ListNode<G>>(new ListNode<G>(val));
    if (isEmpty())
    {
        temp_back->setNext(nullptr);
        temp_back->setPrevious(nullptr);
        back = temp_back;
        front = temp_back;
        current = temp_back;
    }
    else
    {
        temp_back->setNext(nullptr);
        temp_back->setPrevious(back);
        back->setNext(temp_back);
        back = temp_back;
    }
    size++;

}

//!< \brief Adds a new element before the current element
//!     Creates a temporary shared pointer to the listNode object, newly created on the Heap, with the value.
//!     If the list is empty, makes the new node front, back and current of the list ( as it is the only element ) and
//!     sets the node's next and previous to nullptr ( nothing to point to ).
//!     
//!     If the list is not empty and the current node is the front node, sets the new node's next to current and previous to nullptr, sets 
//!     current's previous to be the new node, after that makes the new node front ( as the new node is added before the first
//!     element of the list so to the front ).
//! 
//!     If the list is not empty and current is not front, creates temporary shared pointer to current's previous then sets the new node's 
//!     next to current and previous to current's previous, after that sets the current's previous's next to be the new node and
//!     makes the new node current's previous ( the new node is inserted between current and current's previous ).
//!     
//!     At the end, increase the size of list.
template <class G>
void DoubleLinkedList<G>::push_before_curr(G val)
{
    shared_ptr<ListNode<G>> temp_before_current = shared_ptr<ListNode<G>>(new ListNode<G>(val));

    if (isEmpty())
    {
        current = temp_before_current;
        front = temp_before_current;
        back = temp_before_current;
        temp_before_current->setNext(nullptr);
        temp_before_current->setPrevious(nullptr);
    }
    else if (current == front) //if current is the front
    {
        temp_before_current->setNext(current);
        temp_before_current->setPrevious(nullptr);
        current->setPrevious(temp_before_current);
        front = temp_before_current;
    }
    else
    {
        shared_ptr<ListNode<G>> temp_prev = current->getPrevious();
        temp_before_current->setNext(current);
        temp_before_current->setPrevious(temp_prev);
        temp_prev->setNext(temp_before_current);
        current->setPrevious(temp_before_current);
    }
    size++;

}

//!< \brief Adds a new element after the current element 
//!     Creates a temporary shared pointer to the listNode object, newly created on the Heap, with the value.
//!     If the list is empty, makes the new node front, back and current of the list ( as it is the only element ) and
//!     sets the node's next and previous to nullptr ( nothing to point to ).
//!     
//!     If the list is not empty and the current node is the back node, sets the new node's previous to current and next to nullptr, sets 
//!     current's next to be the new node, after that makes the new node back ( as the new node is added after the last
//!     element of the list so to the back ).
//! 
//!     If the list is not empty and current is not back, creates temporary shared pointer to current's next then sets the new node's 
//!     next to current's next and previous to current, after that sets the current's next's previous to be the new node and
//!     makes the new node current's next ( the new node is inserted between current and current's next ).
//!     
//!     At the end, increase the size of list.
template <class G>
void DoubleLinkedList<G>::push_after_curr(G val)
{
    shared_ptr<ListNode<G>> temp_after_current = shared_ptr<ListNode<G>>(new ListNode<G>(val));

    if (isEmpty())
    {
        current = temp_after_current;
        front = temp_after_current;
        back = temp_after_current;
        temp_after_current->setNext(nullptr);
        temp_after_current->setPrevious(nullptr);
    }
    else if (current == back)  //if current is at the end of the list
    {
        temp_after_current->setPrevious(current);
        temp_after_current->setNext(nullptr);
        current->setNext(temp_after_current);
        back = temp_after_current;
    }
    else
    {
        shared_ptr<ListNode<G>> temp_next = current->getNext();
        temp_after_current->setNext(temp_next);
        temp_after_current->setPrevious(current);
        temp_next->setPrevious(temp_after_current);
        current->setNext(temp_after_current);
    }
    size++;

}

//!< \brief Removes a front node from the list
//!     Declares result variable and assigns the value of a front node to it. Creates a temporary shared pointer pointing to front, then 
//!     moves front to the next node.
//! 
//!     If list size is bigger then 1, sets the old front's next and new front's previous to nullptr ( which in effect disconnects
//!     node to-be-deleted from the list ). After that, if this first node is current, moves the current to new front.
//! 
//!     If list size is equal 1, only sets the rest of shared pointers ( back, current ) to nullptr to avoid memory leaks.
//! 
//!     At the end, decrements list size and returns previously get value.
template <class G>
G DoubleLinkedList<G>::pop_front()
{
    G result = front->getData();
    shared_ptr<ListNode<G>> temp_front = front;   //create temporary pointer pointing to the location of front
    front = front->getNext(); //move the pointer pointing to front
    
    if (size != 1)
    {
        temp_front->setNext(nullptr);
        front->setPrevious(nullptr);

        if (current == temp_front)
        {
            current = front;    //if the to be deleted node is current node, move the current pointer to the previous node
        }
    }

    else
    {
        back = nullptr;
        current = nullptr;
    }
    size--; //decrease the list size
    
    return result;
}

//!< \brief Removes a back node from the list
//!     Declares result variable and assigns the value of a back node to it. Creates a temporary shared pointer pointing to back, then 
//!     moves back to the previous node.
//! 
//!     If list size is bigger then 1, sets the old back's previous and new back's next to nullptr ( which in effect disconnects
//!     node to-be-deleted from the list ). After that, if this last node is current, moves the current to new back.
//! 
//!     If list size is equal 1, only sets the rest of shared pointers ( front, current ) to nullptr to avoid memory leaks.
//! 
//!     At the end, decrements list size and returns previously get value.
template <class G>
G DoubleLinkedList<G>::pop_back()
{
    G result = back->getData();
    shared_ptr<ListNode<G>> temp_backie = back;   //create temporary pointer pointing to the location of back
    back = back->getPrevious(); //move the pointer pointing to back
   
    if (size != 1)
    {
        temp_backie->setPrevious(nullptr);
        back->setNext(nullptr);

        if (current == temp_backie)
        {
            current = back;    //if the to be deleted node is current node, move the current pointer to the next node
        }
    }
    
    else
    {
        front = nullptr;
        current = nullptr;
    }

    size--; //decrease the list size

    return result;
    //when scope ends, temp gets deleted
}

//!< Returns true if the list is empty.
template <class G>
bool DoubleLinkedList<G>::isEmpty()
{
        return size == 0;
}

//!< Returns the size of the list.
template <class G>
int DoubleLinkedList<G>::getSize()
{
    return size;
}

//!< Returns data stored in the first ( front ) node.
template <class G>
G DoubleLinkedList<G>::look_front()
{
    return front->getData();
}

//!< Returns data stored in the last ( last ) node.
template <class G>
G DoubleLinkedList<G>::look_back()
{
    return back->getData();
}

//!< Returns data stored in the current node.
template <class G>
G DoubleLinkedList<G>::look_current()
{
    return current->getData();
}

//!< \brief Moves the current pointer forwards in the list
//!<    If the current node is the back ( last ) node, prints a message.
template <class G>
void DoubleLinkedList<G>::traverse_forwards()
{
    if (current != back)
        current = current->getNext();
    else
        cout << "Current is at the beginning of the list" << endl;
}

//!< \brief Moves the current pointer backwards in the list
//!<    If the current node is the front ( first ) node, prints a message.
template <class G>
void DoubleLinkedList<G>::traverse_backwards()
{
    if (current != front)
        current = current->getPrevious();
    else
        cout << "Current is at the end of the list" << endl;
}

//!< \brief List printer
//!     Prints the contents of list to the console using a shared pointer itarated through nodes.
template <class G>
void DoubleLinkedList<G>::printList()
{
    shared_ptr<ListNode<G>> index = front;

    for (int i = 0; i < getSize(); i++)
    {
        cout << index->getData() << endl;
        index = index->getNext();
    }
}

//!< \brief Optimised bubble sort
//!     Attemps to make optimised bubble sort algorithm for double linked list.
template <class G>
void DoubleLinkedList<G>::listSort()
{
    shared_ptr<ListNode<G>> it1 = front;
    shared_ptr<ListNode<G>> it2 = front;
    int i, j;
    bool isSwapped;
    for (i = 0; i < getSize() - 1; i++)
    {
        it1 = it1->getNext();
        isSwapped = false;
        for (j = 0; j < getSize() - i - 1; j++)
        {
            it2 = it2->getNext();
            if (compareData(it2->getPrevious(), it2))
            {
                swap(it2->getPrevious(), it2);
                isSwapped = true;
            }
        }

        // If there was no swap in inner loop, break 
        if (isSwapped == false)
            break;
    }
}

//!< \brief Compares data of two given nodes
//!     Used in optimised bubble sort.
template <class G>
bool DoubleLinkedList<G>::compareData(shared_ptr<ListNode<G>> first, shared_ptr<ListNode<G>> second)
{
    return (first->getData() > second->getData());
}

//!< \brief Swaps data between two given nodes
//!     Used in optimised bubble sort, tried different aproaches.
template <class G>
void DoubleLinkedList<G>::swap(shared_ptr<ListNode<G>> first, shared_ptr<ListNode<G>> second)
{
    shared_ptr<ListNode<G>> temp = first;
    first = second;
    second = temp;
   /* int temp = first->getData();
    first->setData(second->getData());
    second->setData(temp);*/
}