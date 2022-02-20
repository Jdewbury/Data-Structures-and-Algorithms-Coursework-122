#include "circular-queue.h"
#include <iostream>
using namespace std;

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
    // Initiate head and tail as NULL
    // Initiate array's specifications
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
    capacity_ = 16;

    items_ = new CircularQueue::QueueItem[capacity_];

}

CircularQueue::CircularQueue(unsigned int capacity)
{
    // Initiate head and tail as NULL
    // Initiate array's specifications
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
    capacity_ = capacity;

    items_ = new CircularQueue::QueueItem[capacity_];
}

CircularQueue::~CircularQueue()
{
    // delete array items
    delete[] items_;
}

bool CircularQueue::empty() const
{
    // Test for empty array
    if (size_ <= 0 )
    {
        return true;
    }
    return false;
}

bool CircularQueue::full() const
{
    // Test for full array
    if (size_ >= capacity_ )
    {
        return true;
    }
    return false;
}

int CircularQueue::size() const
{
    // returns size of array
    return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
    // Consider if no more elements can be appended
    if ( full() )
    {
        return false;
    }
    // Consider empty array
    if ( size_ == 0 )
    {
        head_ = 0;
        tail_ = 1;
        items_[head_] = value;
    }
    else
    {
        // Set tail as value and increment tail up one index
        items_[tail_] = value;
        tail_ = (tail_ + 1) %  capacity_;
    }
    size_++;
    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue()
{
    // create a value that will hold the value at front of the queue to return later
    CircularQueue::QueueItem deq_Val = items_[head_];

    //Check for empty array
    if ( size_ <= 0 )
    {
        return EMPTY_QUEUE;
    }
    // Consider if array has a single element
    if ( size_ == 1 )
    {
        head_ = NULL;
        tail_ = NULL;
        size_--;
    }
    else
    {
        // Set head value to NULl, and increment head back one
        items_[head_] = NULL;
        head_ = (head_ + 1 ) % capacity_;
        size_--;
    }
    // Returns value dequeued
    return deq_Val;

}

CircularQueue::QueueItem CircularQueue::peek() const
{
    // Check for an empty array
    if ( size_ <= 0 )
    {
        return EMPTY_QUEUE;
    }
    // return element at front of queue
    return items_[head_];


}

void CircularQueue::print() const
{
    cout<< "The elements in Circular Queue Are:" <<endl;
    for (int i = head_; i < size_; i++ )
    {
        cout << i << ":" << items_[i] <<endl;
    }
}