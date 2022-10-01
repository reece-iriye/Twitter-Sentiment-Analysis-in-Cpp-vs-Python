#ifndef DSVECTOR_H
#define DSVECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Object>
class DSVector
{
private:
    size_t theSize;
    size_t theCapacity;
    Object* objects;


public:
  // Create an empty DSVector
  explicit DSVector(size_t initSize = 0)
      : theSize{initSize}, theCapacity{initSize}
  {
    objects = new Object[theCapacity];
  }

  // C++11 initializer list with {}
  DSVector(const initializer_list<Object> &v)
  {
    theSize = 0;
    theCapacity = v.size();
    objects = new Object[theCapacity];
    for (auto itm : v)
      this->push_back(itm);
  }

  // Copy constructor
  DSVector(const DSVector &rhs)
      : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}
  {
    objects = new Object[theCapacity];
    for (size_t k = 0; k < theSize; ++k)
      objects[k] = rhs.objects[k];
  }

  // C++11 Move constructor ... steal the pointer to objects
  DSVector(DSVector &&rhs)
      : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
  {
    rhs.theSize = 0;
    rhs.theCapacity = 0;
    rhs.objects = nullptr; // so the destructor does not destroy the objects
  }

  // Destructor
  ~DSVector() {
    delete[] objects;
  }

  // Assignment operator
  DSVector &operator=(const DSVector &rhs) {
    delete[] objects;
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    objects = new Object[theCapacity];
    for (size_t k = 0; k < theSize; ++k)
      objects[k] = rhs.objects[k];

    return *this;
  }

  // C++11 move assignment operator: move elements from rhs using std::swap()
  DSVector &operator=(DSVector &&rhs) {
    swap(theSize, rhs.theSize);
    swap(theCapacity, rhs.theCapacity);
    swap(objects, rhs.objects);

    return *this;
  }

  // is the vector empty?
  bool empty() const {
    return size() == 0;
  }

  // how many elements?
  int size() const {
    return theSize;
  }

  // what is the capacity?
  size_t capacity() const {
    return theCapacity;
  }

  // subscript operator
  Object &operator[](int index) {
      if (index >= size() || index < -size())
          throw std::runtime_error("Index call is out of bounds for DSVector!");

      // I accept negative values, because I want to provide DSVector with Python list indexing

      else if (index < 0)
          index += size();

      return objects[index];
  }

  const Object &operator[](int index) const {
      if (index >= size() || index < -size())
          throw std::runtime_error("Index call is out of bounds!");
      else if (index < 0)
          index += size();

      return objects[index];
  }

  // reserve more space
  void reserve(size_t newCapacity) {
    if (newCapacity < theSize)
      return;

    Object *newArray = new Object[newCapacity];
    for (size_t k = 0; k < theSize; ++k)
      newArray[k] = objects[k];

    delete [] objects;
    objects = newArray;
    theCapacity = newCapacity;
  }

  // resize the vector
  void resize(size_t newSize) {
    if (newSize > theCapacity)
      reserve(newSize);
    theSize = newSize;
  }

  const Object &back() const {
    if (empty())
      throw std::runtime_error("Stack is empty!");
    return objects[theSize - 1];
  }

  // add an element at the end. STL calls this push_back().
  void push_back(const Object &x) {
    if (theSize == theCapacity)
      reserve((theCapacity > 0) ? 2 * theCapacity : 2);
    objects[theSize++] = x;
  }

  // Reece here: ADD MORE FUNCTIONS
  void pop_back() {
      if( empty() )
          throw std::runtime_error("Cannot pop back an empty DSVector.");
      --theSize;
  }

    void remove(size_t index) {
        switch (empty()) {
            // Exception handling in case file somehow doesn't open
            case true:
                throw std::runtime_error("Stack is empty! Cannot access elements from empty Stack!");
                break;
                // Case for when the DSVector has elements inside it
            case false:
                if(index >= this->size())
                    throw std::runtime_error("Cannot access elements from an index equal "
                                             "to or exceeding the size of DSVector!");
                else {
                    // Backtrack through this DSVector by setting every element equal to the element after
                    for (size_t i = index; i < size()-1; ++i) {
                        (*this)[i] = (*this)[i+1];
                    }
                    // Resize to previous length minus 1
                    resize(size()-1);
                }
                break; // exit switch function
        }

    }


  // STL algorithms and ranges use begin() and end() to obtain iterators.
  // Iterators for arrays are just regular pointers. operator++ and operator--
  // are already available, so we don't need to implement a nested class iterator,
  // but just reuse Object * using a nested type definition.
  typedef Object *iterator;
  typedef const Object *const_iterator;

  iterator begin()
  {
    return &objects[0];
  }

  const_iterator begin() const
  {
    return &objects[0];
  }

  iterator end()
  {
    return &objects[size()];
  }

  const_iterator end() const
  {
    return &objects[size()];
  }
};

#endif
