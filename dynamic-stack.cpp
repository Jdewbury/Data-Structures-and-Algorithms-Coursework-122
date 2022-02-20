#include "dynamic-stack.h"
#include <iostream>
using namespace std;

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
    // initialize values and array
    init_capacity_ = 16;
    size_ = 0;
    items_ = new DynamicStack::StackItem[init_capacity_];

}

DynamicStack::DynamicStack(unsigned int capacity)
{
    // initialize init capacity as passed argument, and initialize capacity and array
    capacity_ = capacity;
    init_capacity_ = capacity_;
    size_ = 0;
    items_ = new DynamicStack::StackItem[capacity_];

}

DynamicStack::~DynamicStack()
{
    // delete array items
    delete[] items_;
}

bool DynamicStack::empty() const
{
    // Test for empty array
    if (size_ <= 0 )
    {
        return true;
    }
    return false;
}

int DynamicStack::size() const
{
    // returns size of array
    return size_;

}

void DynamicStack::push(StackItem value)
{
    // Check for stack overflow
    if ( size_ >= capacity_  )
    {
        // double capacity
        capacity_ = 2*(capacity_);

        //Create a temporary array temp
        StackItem* temp_ = new DynamicStack::StackItem[capacity_];

        // run through all elements in size and pass them into temp
        for ( int i = 0; i < size_; i++ )
        {
            temp_[i] = items_[i];
        }
        //delete items array
        delete[] items_;

        // clone temp array as items
        items_ = temp_;
    }
    // add passed value on top of stack and increment array size by 1
    items_[size_] = value;
    size_ ++;

}

DynamicStack::StackItem DynamicStack::pop()
{
    // create value pup value that will hold the value on top of the stack to return later
    DynamicStack::StackItem pop_Val = items_[size_ - 1];

    // check for an empty stack
    if (size_ <= 0 )
    {
        return EMPTY_STACK;
    }
    else
    {
        // make value on top of stack NULL
        items_[size_ - 1] = NULL;
        size_ --;
            // Check if we need to adjust capacity of the array
            if ( (size_ <= (0.25)*capacity_) && (capacity_*(0.5) >= init_capacity_) )
            {
                capacity_ = capacity_*(0.5);
            }
    }
    // return pop value that we declared at the top of the method
    return pop_Val;

}

DynamicStack::StackItem DynamicStack::peek() const
{
    // Check for an empty array
    if ( size_ <= 0 )
    {
        return EMPTY_STACK;
    }

    // return element on top of the stack
    return items_[size_-1];

}

void DynamicStack::print() const
{
    for(int i = 0; i < size_+1; i ++)
    {
        cout<< items_[i];
    }

}

