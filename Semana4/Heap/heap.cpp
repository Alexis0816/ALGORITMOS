#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

template <typename T>
class Heap
{
public:
  enum Type{
    MAX_HEAP,
    MIN_HEAP
  };

private:
  T *elements;
  int capacity;
  int n;
  Type type;

public:
  Heap(T *elements, int n, Type type = MAX_HEAP) : elements(new T[n]), n(n), type(type)
  {
    copy(elements, elements + n, this->elements);
    buildHeap();
  }

  Heap(int capacity, Type type = MAX_HEAP) : elements(new T[capacity]), capacity(capacity), n(0), type(type) {}

  ~Heap()
  {
    delete[] elements;
  }

  void buildFromArray(T *arr, int n)
  {
    this->n = n;
    delete[] elements;
    elements = new T[n];
    copy(arr, arr + n, elements);
    buildHeap();
  }

  int size(){
    return n;
  }

  bool is_empty()
  {
    return n == 0;
  }

  void push(T value){
    if (n == capacity){
      throw overflow_error("Heap is full");
    }

    elements[n++] = value;
    heapify_up(n - 1);
  }

  T pop(){
    if (is_empty()){
      throw underflow_error("Heap is empty");
    }

    T root = elements[0];
    elements[0] = elements[--n];
    heapify_down(0);
    return root;
  }

  T top(){
    if (is_empty()){
      throw underflow_error("Heap is empty");
    }

    return elements[0];
  }

  vector<T> extractTheTopK(int k)
  {
    if (k > n)
    {
      throw invalid_argument("K exceeds the heap size");
    }

    vector<T> result;
    for (int i = 0; i < k; ++i)
    {
      result.push_back(pop());
    }
    return result;
  }

  static void sortAsc(T *arr, int n)
  {
    Heap<T> heap(arr, n);
    for (int i = n - 1; i >= 0; --i)
    {
      arr[i] = heap.pop();
    }
  }

  static void sortDesc(T *arr, int n)
  {
    Heap<T> heap(arr, n, MIN_HEAP);
    for (int i = n - 1; i >= 0; --i)
    {
      arr[i] = heap.pop();
    }
  }

private:
  int Parent(int i)
  {
    return (i - 1) / 2;
  }

  int Left(int i)
  {
    return (2 * i + 1);
  }

  int Right(int i)
  {
    return (2 * i + 2);
  }

  void heapify_down(int i)
  {
    int left = Left(i);
    int right = Right(i);
    int extreme = i;

    if (left < n && ((type == MAX_HEAP && elements[left] > elements[extreme]) || (type == MIN_HEAP && elements[left] < elements[extreme])))
    {
      extreme = left;
    }

    if (right < n && ((type == MAX_HEAP && elements[right] > elements[extreme]) || (type == MIN_HEAP && elements[right] < elements[extreme])))
    {
      extreme = right;
    }

    if (extreme != i)
    {
      swap(elements[i], elements[extreme]);
      heapify_down(extreme);
    }
  }

  void heapify_up(int i)
  {
    while (i > 0 && ((type == MAX_HEAP && elements[Parent(i)] < elements[i]) || (type == MIN_HEAP && elements[Parent(i)] > elements[i])))
    {
      swap(elements[i], elements[Parent(i)]);
      i = Parent(i);
    }
  }

  void buildHeap(){
    for (int i = n / 2 - 1; i >= 0; --i) 
      heapify_down(i);
  }
};

int main()
{
  // Ejemplo de uso
  int arr[] = {4, 10, 3, 5, 1};
  int n = sizeof(arr) / sizeof(arr[0]);

  Heap<int> maxHeap(arr, n);
  cout << "Max Heap Top: " << maxHeap.top() << endl;

  Heap<int> minHeap(arr, n, Heap<int>::MIN_HEAP);
  cout << "Min Heap Top: " << minHeap.top() << endl;

  Heap<int>::sortAsc(arr, n);
  cout << "Sorted Array (Ascending): ";
  for (int i = 0; i < n; ++i)
  {
    cout << arr[i] << " ";
  }
  cout << endl;

  Heap<int>::sortDesc(arr, n);
  cout << "Sorted Array (Descending): ";
  for (int i = 0; i < n; ++i)
  {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}
