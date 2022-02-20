#include "sequential-list.h"
#include <iostream>

using namespace std;

SequentialList::SequentialList(unsigned int cap)
{
    // Initialize global variables
    capacity_ = cap;
    size_ = 0;

    // Create an empty list of type DataType
    // Capacity of list is declared and passed by user
    data_ = new SequentialList::DataType[capacity_];
}

SequentialList::~SequentialList()
{
    delete data_;
}

unsigned int SequentialList::size() const
{
    // Returns size of list
    return size_;
}

unsigned int SequentialList::capacity() const
{
    // Returns total capacity of list
   return capacity_;
}

bool SequentialList::empty() const
{
    // Checks to see if list has no elements
    if ( size_ == 0 )
    {
        return true;
    }
    return false;
}

bool SequentialList::full() const
{
    // Checks to see if list has all indexes filled
    if ( size_ == capacity_ )
    {
        return true;
    }
    return false;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if ( index > size_ ) // If index value is invalid
    {
        return data_[size_];
    }
    return data_[index];

}

unsigned int SequentialList::search(DataType val) const
{
    for (int i = 0; i < size_ + 1; i++ )
    {
        if ( data_[i] == val )
        {
            return i; // If desired value is found, returns index of value
        }
    }
    return size_; // If desired value is not found
}

void SequentialList::print() const
{
    for(int i = 0; i < size_+1; i ++)
    {
        cout<< data_[i];
    }
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    // Checks for values outside of given parameters
    if (index < 0 || index > size_ || size_ >= capacity_ )
    {
        return false;
    }
    // Considers if list is only a single element
    if ( size_ == 1 )
    {
        size_++;
        data_[1] = data_[0];
        data_[0] = val;
    }
    // Starts at back of list, moves all values to right of index up one index
    for ( int i = size_; i > index - 1; i-- )
    {
        data_[i] = data_[ i-1 ];
    }
    data_[index] = val;
    size_ ++;
    return true;

}

bool SequentialList::insert_front(DataType val)
{
    // Checks if size_ is full or out of bounds
    if ( size_ >= capacity_ )
    {
        return false;
    }
    // Moves all elements up one index
    for( int i = size_; i > -1; i-- )
        {
            data_[i] = data_[ i - 1 ];
        }
    data_[0] = val;
    size_ ++;
    return true;


}

bool SequentialList::insert_back(DataType val)
{
    // Checks for full or invalid list
    if ( size_ >= capacity_ )
    {
        return false;
    }
    // Makes last element into value
    data_[size_] = val;
    size_ ++;
    return true;

}

bool SequentialList::remove(unsigned int index)
{
    // Checks for invalid index or empty list
    if (index > size_ || size_ <= 0 )
    {
        return false;
    }
    // Considers if there is only 1 element in list
    if ( size_ == 1 )
    {
        data_[0] = NULL;
        size_ = 0;
    }
    // Shifts all elements to right of index down one (final two elements will be identical, with last being deleted)
    for( int i = index; i < size_ + 1; i++ )
    {
        data_[i] = data_[ i+1 ];
    }
    // Turns last element into NULL
    data_[size_] = NULL;
    size_ --;
    return true;
}

bool SequentialList::remove_front()
{
    if (size_ <= 0 )
    {
        return false;
    }
    // Shifts all elements down one index (replaces first value)
    for ( int i = 0; i < size_ + 1; i++ )
    {
        data_[i] = data_[i+1];
    }
    // Deletes final value (which is a repeat)
    data_[size_] = NULL;
    size_ --;
    return true;
}

bool SequentialList::remove_back()
{
    if ( size_ <= 0 )
    {
        return false;
    }
    // Removes final value
    data_[size_-1] = NULL;
    size_ --;
    return true;
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    // Replaces given value
    data_[index] = val;

}

