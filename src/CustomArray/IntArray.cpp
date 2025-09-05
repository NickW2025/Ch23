#include "IntArray.h"
#include <cassert>
#include <initializer_list>
#include <iostream>

namespace CustomArray {

  ///////////////
  //cstr + dstr//
  ///////////////

  IntArray::IntArray(const uint length_): length(length_) {
    if (length > 0) data = new int[static_cast<std::size_t>(length)];
  } //cstr

  IntArray::IntArray(std::initializer_list<int> values) {
    length = values.size();
    data = new int[length];
    uint index = 0;
    for (const int i: values) {
      data[index] = i;
      ++index;
    }
  } //cstr

  IntArray::IntArray(const IntArray& other) {
    if (&other != this) {
      this->length = other.length;
      this->data = new int[length];

      for (uint i = 0; i < length; ++i) {
        this->data[i] = other[i];
      }
    }
  } //copy cstr

  IntArray::IntArray(IntArray&& other) noexcept {
    length = other.length;
    data = other.data;
    other.length = 0;
    other.data = nullptr;
  } //move cstr

  IntArray::~IntArray() {
    delete[] data;
  } //dstr

  /////////////
  //Operators//
  /////////////

  int& IntArray::operator[](uint index_) {
    assert(index_ < length);
    return data[index_];
  } //operator[]

  int IntArray::operator[](uint index_) const {
    assert(index_ < length);
    return data[index_];
  } //operator[] const

  IntArray& IntArray::operator=(const IntArray& other) {
    if (&other != this) {
      this->erase();
      this->length = other.length;
      this->data = new int[length];

      for (uint i = 0; i < length; ++i) {
        this->data[i] = other[i];
      }
    }
    return *this;
  } //copy assignment

  IntArray& IntArray::operator=(IntArray&& other) noexcept {
    if (&other != this) {
      length = other.length;
      other.length = 0;
      delete[] data;
      data = other.data;
      other.data = nullptr;
    }
    return *this;
  } //move assignment

  IntArray& IntArray::operator=(std::initializer_list<int> values) {
    if (values.size() != length) {
      delete[] data;
      length = values.size();
      data = new int[length];
    }
    auto iterator = values.begin();
    for (uint i = 0; i < length; ++i) {
      data[i] = iterator[i];
    }
    return *this;
  } //list assignment

  ////////////////////
  //member functions//
  ////////////////////

  uint IntArray::getLength() const {
    return length;
  } //size()

  void IntArray::reallocate(uint new_length) {
    erase();
    length = new_length;
    data = new int[length];
  } //reallocate()

  void IntArray::resize(uint new_length) {
    if (new_length == length) return;
    if (new_length <= 0) erase();
    else {
      int* new_data = new int[new_length];
      for (uint i = 0; i < new_length; ++i) {
        new_data[i] = data[i];
      }
      erase();
      length = new_length;
      data = new_data;
    }
  } //resize()

  void IntArray::erase() {
    delete[] data;
    data = nullptr;
    length = 0;
  } //erase()

  void IntArray::insertBefore(int value, uint index) {
    assert (index <= length);
    int* new_data = new int[length+1];
    for (uint i = 0; i < index; ++i) {
      new_data[i] = data[i];
    }
    new_data[index] = value;
    for (uint i = index + 1; i <= length; ++i) {
      new_data[i] = data[i-1];
    }
    delete[] data;
    data = new_data;
    ++length;
  } //insertBefore()

  void IntArray::remove(uint index) {
    assert (index < length);
    --length;
    for (uint i = index; i < length; ++i) {
      data[i] = data[i + 1];
    }
  } //remove()

  //////////////////
  //test functions//
  //////////////////

  void IntArray::insertAtBeginning(int value) {
    insertBefore(value, 0);
  } //insertAtBeginning()

  void IntArray::insertAtEnd(int value) {
    insertBefore(value, length);
  } //insertAtEnd()

  void test() {
    IntArray array { 5, 4, 3, 2, 1 }; // initializer list
    for (int count{ 0 }; count < array.getLength(); ++count)
      std::cout << array[count] << ' ';

    std::cout << '\n';

    array = { 1, 3, 5, 7, 9, 11 };

    for (int count{ 0 }; count < array.getLength(); ++count)
      std::cout << array[count] << ' ';

    std::cout << '\n';
  } //test()

  void test2() {
    // Declare an array with 10 elements
    IntArray array(10);

    // Fill the array with numbers 1 through 10
    for (int i{ 0 }; i<10; ++i)
      array[i] = i+1;

    // Resize the array to 8 elements
    array.resize(8);

    // Insert the number 20 before element with index 5
    array.insertBefore(20, 5);

    // Remove the element with index 3
    array.remove(3);

    // Add 30 and 40 to the end and beginning
    array.insertAtEnd(30);
    array.insertAtBeginning(40);

    // A few more tests to ensure copy constructing / assigning arrays
    // doesn't break things
    {
      IntArray b{ array };
      b = array;
      b = b;
      array = array;
    }

    // Print out all the numbers
    for (int i{ 0 }; i<array.getLength(); ++i)
      std::cout << array[i] << ' ';

    std::cout << '\n';
  } //test2()

} // CustomArray