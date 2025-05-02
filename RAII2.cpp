#include <iostream>
#include <stdexcept>

using namespace std;


class RAII 
{
private:
  size_t size;
  int* data ;
  size_t capacity;
public: 
 explicit RAII (size_t initial_capacity) : size(0), capacity(initial_capacity)
 {
  if (initial_capacity == 0)
  {
    throw std :: invalid_argument("Initial capacity must be greater than zero.");
  }
  data = new int[capacity];
 } 

 RAII (const RAII& other): size(other.size),capacity(other.capacity)
 {
    data  = new int [capacity];
    for(size_t i = 0 ; i < size; ++i)
    {
        data [i] = other.data[i];
    }
 } 
 RAII& operator=(RAII other)
 {
    swap (*this , other);
    return *this;
 }

 ~RAII() {delete[] data; }

  void add_element(int NewElement)
  { 
    if (capacity <= size )
    {
      size_t new_capacity = capacity *2;
      int* new_data = new int [capacity];

      for (int i = 0 ; i < size ; ++i)
      {
        new_data [i] = data[i];
      }
      delete[] data ;

      data = new_data;
      capacity = new_capacity;
    }
    data[size++] = NewElement;
  }
  auto get_element(size_t index )
  {
    if(index >= size )
    {
      throw std :: out_of_range("Index out range");
    }
    return data[index];
  } 

  friend void swap (RAII& first, RAII& second) noexcept
  {
    using std::swap;
    swap (first.data, second.data);
    swap(first.size,second.size);
    swap(first.capacity,second.capacity);
  }
};

int main ()
{
   try {
   
  RAII arr(5); 
  arr.add_element(1);
  arr.add_element(4);
  arr.add_element(155);
  
  RAII new_array(2);
  new_array.add_element(44); 
  new_array.add_element(34);

  arr = new_array;
   }
   catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
}