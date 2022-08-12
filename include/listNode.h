#pragma once

/*! \file listNode.h
    \brief File containing ListNode class
*/

#include <memory>
#include <string>

using namespace std;

/*<! \class listNode
*   \brief Node in the list data structure.
*/
template <class G>
class ListNode
{
private:
    G data; //!< contents of a node
    shared_ptr<ListNode<G>> next;  //!< next element in the list
    shared_ptr<ListNode<G>> prev;  //!< previous element in the list

public:
    ListNode(G newData);  //!< Constructor
    ~ListNode(); //!< Destructor
    void setData(G newData);    //!< data : Setter
    G getData(); //!< data : Getter
    void setNext(shared_ptr<ListNode<G>> newNext);  //!< next : Setter
    shared_ptr<ListNode<G>> getNext();  //!< next : Getter
    void setPrevious(shared_ptr<ListNode<G>> newPrev);  //!< previous : Setter
    shared_ptr<ListNode<G>> getPrevious();  //!< previous : Getter
};

// Below are the definitions for the forward declarated methods

//!     Takes data and assigns it to a new node
template <class G>
ListNode<G>::ListNode(G newData)    
{
    data = newData; 
}
template <class G>
ListNode<G>::~ListNode()
{
    
}

template <class G>
void ListNode<G>::setData(G newData)
{
    data = newData;

}

//!     Returns node's data
template <class G>
G ListNode<G>::getData()
{
    return data;
}

//!     Takes a shared pointer to ListNode object and sets it as node's next node
template <class G>
void ListNode<G>::setNext(shared_ptr<ListNode<G>> newNext)
{
    next = newNext;
}

//!     Returns a shared pointer to node's next node
template <class G>
shared_ptr<ListNode<G>> ListNode<G>::getNext()
{
    return next;
}

//!     Takes a shared pointer to ListNode object and sets it as node's previous node    
template <class G>
void ListNode<G>::setPrevious(shared_ptr<ListNode<G>> newPrev)
{
    prev = newPrev;
}

//!     Returns a shared pointer to node's previous node
template <class G>
shared_ptr<ListNode<G>> ListNode<G>::getPrevious()
{
    return prev;
}