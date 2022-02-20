#include "doubly-linked-list.h"
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    // initialize values for Node
    value = data;
    next = nullptr;
    prev = nullptr;

}

DoublyLinkedList::DoublyLinkedList()
{
    // initialize values in list
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;

}

DoublyLinkedList::~DoublyLinkedList()
{
    //didn't use, so kept blank
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0 )
    {
        return true;
    }
    return false;
}

bool DoublyLinkedList::full() const
{
    if (size_ >= CAPACITY )
    {
        return true;
    }
    return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    // define a node that points to head
    Node *currentNode = head_;

    // tests for invalid indexes
    if ( index < 0 || index > size_ )
    {
        return tail_ -> value;
    }
    // initiate count
    int count = 0;

    while ( count != index )
    {
        if ( count == index )
        {
            return currentNode -> value;
        }
        currentNode = currentNode -> next;
        count ++;
    }
    return currentNode -> value;

}

unsigned int DoublyLinkedList::search(DataType value) const
{
    // initiate node pointed to head
    Node *currentNode = head_;
    int count = 0;

    while ( currentNode != NULL)
    {
        if ( currentNode -> value == value)
        {
            return count;
        }
        currentNode = currentNode -> next;
        count ++;
    }
    return size_;
}

void DoublyLinkedList::print() const
{
    Node *currentNode = head_;

    int count = 0;
    while ( count < size_ )
    {
        cout << currentNode;
        currentNode = currentNode -> next;
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    // didn't need to use
    /*
    Node *currentNode = head_;

    if ( index < 0 || index > size_ )
    {
        return NULL;
    }

    int count = 0;
    while ( count < size_ + 1 )
    {
        if ( count == index )
        {
        }

        count++;
    }

    */
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    // initiate a new node, and a node pointed to head
    Node *newNode = new Node(value);
    Node *currentNode = head_;

    // test for invalid cases
    if ( index < 0 || index > size_ || size_ >= CAPACITY )
    {
        return false;
    }
    // if list is empty
    else if ( head_ == NULL )
    {
        head_ = newNode;
        tail_ = newNode;
    }
    // if index is at end
    else if ( index == size_ )
    {
        return insert_back(value);
    }
    // if index is at front
    else if ( index == 0 )
    {
       return insert_front(value);
    }
    else
    {
        int count = 0;

        while ( currentNode != NULL )
        {
            if ( count == index )
            {
                // swap positions of nodes
                newNode -> prev = currentNode -> prev;
                newNode -> next = currentNode;
                currentNode -> prev -> next = newNode;
                currentNode -> prev = newNode;
            }
            currentNode = currentNode -> next;
            count++;
        }
    }
    size_++;
    return true;
}

bool DoublyLinkedList::insert_front(DataType value)
{
    // initialize new node
    Node *newNode = new Node(value);

     if ( size_ >= CAPACITY )
     {
         return false;
     }
     // if list is empty
     if ( size_ == 0 )
     {
         head_ = newNode;
         tail_ = head_;
     }
     else
     {
         // swap new node into front
         head_ -> prev = newNode;
         newNode -> next = head_;
     }
     head_ = newNode;
     size_ ++;
     return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
    // initialize new node
    Node *newNode = new Node(value);

    if ( size_ >= CAPACITY )
    {
        return false;
    }
    if ( size_ == 0 )
    {
        tail_ = newNode;
        head_ = tail_;
    }
    else
    {
        // swap node to end
        tail_ -> next = newNode;
        newNode -> prev = tail_;
        tail_ = newNode;
    }
    size_ ++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    Node *currentNode = head_;
    // test for invalid indexes and cases
    if ( index < 0 || index > size_ || currentNode == NULL)
    {
        return false;
    }
    // if index is at back
    else if ( index == size_ - 1)
    {
        return remove_back();
    }
    // if index is at front ( can use remove_front() )
    else if ( index == 0 )
    {
        if ( currentNode -> next == NULL )
        {
            head_ = nullptr;
            tail_ = nullptr;
        }
        else
        {
            head_ = currentNode -> next;
            head_ -> prev = nullptr;
            currentNode = nullptr;
            delete currentNode;
        }
        size_--;
        return true;
    }
    // initialize count and run down list until on index
    int count = 0;
    while ( currentNode != NULL )
    {
        if (count == index )
        {
            currentNode = nullptr;
            delete currentNode;
            size_--;
            return true;
        }

        currentNode = currentNode -> next;
        count++;
    }
    return false;
}

bool DoublyLinkedList::remove_front()
{
    if (size_ == 0)
    {
        return false;
    }
    if (size_ == 1)
    {
        head_ = nullptr;
        tail_ = nullptr;
    }
    else
    {
        Node *currentNode = head_;
        head_ = currentNode->next;
        head_->prev = nullptr;
        delete currentNode;
    }
    size_--;
    return true;
}

bool DoublyLinkedList::remove_back()
{
    if (size_ == 0)
    {
        return false;
    }
    if (size_ == 1)
    {
        head_ = nullptr;
        tail_ = nullptr;
    }
    else
    {
        Node *currentNode = tail_;
        tail_ = currentNode -> prev;
        tail_ -> next = nullptr;
        delete currentNode;
    }
    size_--;
    return true;

}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{

    Node *currentNode = head_;
    int count = 0;

    if ( index < 0 || index > size_ )
    {
        return false;
    }
    while ( currentNode != NULL )
    {
        if ( count == index )
        {
            currentNode -> value = value;
            return true;
        }
        currentNode = currentNode -> next;
        count ++;
    }
    return false;

}

