#ifndef OBJECTRELATIONSHIPS_INTARRAY_H
#define OBJECTRELATIONSHIPS_INTARRAY_H

#include <initializer_list>

namespace CustomArray {

  using uint = std::size_t;

  class IntArray {

    private: //data members
      uint length{};
      int* data{};

    public: //cstr + dstr
      IntArray() = default;
      explicit IntArray(uint length_);
      IntArray(std::initializer_list<int> values);
      IntArray(const IntArray& other);
      IntArray(IntArray&& other) noexcept;
      ~IntArray();

    public: //operators
      int& operator[](uint index_);
      int operator[](uint index_) const;
      IntArray& operator=(const IntArray& other);
      IntArray& operator=(IntArray&& other) noexcept;
      IntArray& operator=(std::initializer_list<int> values);

    public: //member functions
      void erase();
      uint getLength() const;
      void reallocate(uint new_length);
      void resize(uint new_length);
      void insertBefore(int value, uint index);
      void remove(uint index);

    public: //test functions
      void insertAtBeginning(int value);
      void insertAtEnd(int value);

  }; //class IntArray

  void test();
  void test2();

} // CustomArray

#endif //OBJECTRELATIONSHIPS_INTARRAY_H