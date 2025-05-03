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

 ~RAII() {delete[] data; }

  void add_element(int NewElement)
  { 
    if (capacity <= size )
    {
      size_t new_capacity = capacity *2;
      int* new_data = new int [new_capacity];

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

  RAII (const RAII&) = delete ;
  RAII& operator=(const RAII&) = delete;
};

int main ()
{
   try {
   
  RAII arr(10); 
  arr.add_element(1);
	arr.add_element(4);
	arr.add_element(155);
	arr.add_element(14);
	arr.add_element(15);
	std::cout << arr.get_element(1) << std::endl;
   }
   catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
}
