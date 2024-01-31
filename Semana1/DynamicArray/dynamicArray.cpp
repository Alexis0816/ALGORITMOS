#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Array
{
private:
  T *arr;
  int len = 0;
  int capacity = 16;

public:
  Array() : arr(new T[this->capacity]) {}

  Array(int capacity)
  {
    if (capacity < 0)
      throw "Capacity cannot be negative";
    this->capacity = capacity;
    this->arr = new T[this->capacity];
  }


  int size() { return len; }

  bool isEmpty() { return size() == 0; }

  T get(int index) { 
    if (index < 0 || index >= len)
      throw "Index out of range";
      
    return arr[index]; 
  }

  void set(int index, T elem){
    if (index < 0 || index >= capacity)
        throw "Index out of range";

    arr[index] = elem;
    len++;
  }

  void clear()
  {
    for (int i = 0; i < capacity; i++)
    {
      arr[i] = T();
    }
  }

  void resize(T elem)
  {
    // resize
    if (len + 1 >= capacity){
      (capacity == 0) ? capacity = 1 : capacity *= 2;
      T *new_arr = new T[capacity];

      for (int i = 0; i < len; i++){
        new_arr[i] = arr[i];
      }

      delete[] arr;  // Liberar memoria
      arr = new_arr;
    }
    arr[len++] = elem;
  }

  T removeAt(int rm_index){
    if (rm_index < 0 or rm_index >= len) throw "Index out of range";

    T data = arr[rm_index];
    for (int i = rm_index; i < len - 1; i++){
      arr[i] = arr[i + 1];
    }

    --len;

    return data;
  }

  bool remove(T elem){
    for (int i = 0; i < len; i++){
      if(arr[i] == elem){
        removeAt(i);
        return true;
      } else return false;
    }
  }

  int indexOf(T elem){
    for (int i = 0; i < len; i++){
      if(arr[i] == elem){
        return i;
      }
    }
    return -1;
  }

  bool contains (T elem){
    return (indexOf(elem) != -1);
  }

  void print(){
    for (int i = 0; i < len; i++) {
      cout << arr[i] << " ";
    } cout<<endl;
  }

  ~Array() { delete[] arr; }
};

int main()
{
  Array<int> myArray(5);
  
  // cout<<"Size: "<<myArray.size()<<endl;

  for (int i = 0; i < 5; ++i){
    myArray.set(i, i * 2);
    cout<<"Size: "<<myArray.size()<<endl;
  }

  cout << "Original Array: ";
  myArray.print();

  int index = 4;
  int removedElement = myArray.removeAt(index);

  cout << "Array after removing element at index "<<index<<": ";
  myArray.print();

  cout << "Removed Element: " << removedElement << endl;

  cout<<"Size: "<<myArray.size()<<endl;

  cout<< myArray.contains(2)<<endl;


  return 0;
}