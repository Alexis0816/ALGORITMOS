#include <iostream>
using namespace std;

template <typename T>
struct Node{
  T data;
  Node<T> *next;
  Node<T> *prev;
  Node(T value = T()) : data(value), next(nullptr), prev(nullptr) {}
  Node(T value, Node<T> *_next, Node<T> *_prev) : data(value), next(_next), prev(_prev) {}
};

template <class T>
class ArrayIterator{
private:
  Node<T> *current;

public:
  ArrayIterator(Node<T> *ptr) : current(ptr) {}

  T &operator*() { return current->data; }

  ArrayIterator &operator++(){
    current = current->next;
    return *this;
  }

  ArrayIterator &operator--(){
    current = current->prev;
    return *this;
  }

  bool operator!=(const ArrayIterator &other){
    return current != other.current;
  }
};

template <class T>
class DoublyLinkedList{
private:
  int nodes = 0;
  Node<T> *head = nullptr;
  Node<T> *tail = nullptr;

public:
  using iterator = ArrayIterator<T>;
  // O(n)
  void clear()
  {
    auto *trav = head;
    while (trav != nullptr)
    {
      Node<T> *next = trav->next;
      trav->prev = trav->next = nullptr;
      trav = next;
    }
    delete trav;
    head = tail = trav = nullptr;
    nodes = 0;
  }

  int size() { return nodes; }

  bool isEmpty() { return size() == 0; }

  // O(1)
  void push_front(T elem)
  {
    if (isEmpty())
    {
      head = tail = new Node<T>{elem};
    }
    else
    {
      head->prev = new Node<T>{elem, head, nullptr};
      head = head->prev;
    }
    nodes++;
  }

  // O(1)
  void push_back(T elem)
  {
    if (isEmpty())
    {
      head = tail = new Node<T>{elem};
    }
    else
    {
      tail->next = new Node<T>{elem, nullptr, tail};
      tail = tail->next;
    }
    nodes++;
  }

  // O(1)
  void insert(T data, int pos)
  {
    if (pos <=0)
    {
      push_front(data);
    } // inserta al inicio si la posición es negativa
    else if (pos > size())
    {
      push_back(data);
    } // inserta al final si la posición es mayor a la cantidad de nodos
    else
    {
      auto *nuevo = new Node<T>{data};
      auto *temp = head;
      int i = 1;
      while (i < pos && temp != nullptr){
        temp = temp->next;
        i++;
      }
      nuevo->next = temp->next;
      nuevo->prev = temp;
      if (temp->next != nullptr)
      {
        temp->next->prev = nuevo;
      }
      temp->next = nuevo;
      ++nodes;
    }
  }

  // O(1)
  T front()
  {
    if (isEmpty())
      throw out_of_range("List is empty");
    return head->data;
  }

  // O(1)
  T back()
  {
    if (isEmpty())
      throw out_of_range("List is empty");
    return tail->data;
  }

  // O(1)
  T pop_front()
  {
    if (isEmpty())
      throw out_of_range("List is empty");
    T data = head->data;
    head = head->next;
    --nodes;
    if (isEmpty())
      tail = nullptr;
    else
    {
      delete head->prev;
      head->prev = nullptr;
    }

    return data;
  }

  // O(1)
  T pop_back()
  {
    if (isEmpty())
      throw out_of_range("List is empty");
    T data = tail->data;
    tail = tail->prev;
    --nodes;
    if (isEmpty())
      head = nullptr;
    else
    {
      delete tail->next;
      tail->next = nullptr;
    }

    return data;
  }

  // O(1)
  T removeNode(Node<T> *node)
  {
    if (node->prev == nullptr)
    {
      return pop_front();
    };
    if (node->next == nullptr)
    {
      return pop_back();
    };
    node->next->prev = node->prev;
    node->prev->next = node->next;
    T data = node->data;
    delete node;
    --nodes;

    return data;
  }

  // O(n)
  T remove(int pos)
  {
    if (pos < 0 || pos >= size())
      throw invalid_argument("Position is out of range.");
    int i;
    Node<T> *trav;
    // busca desde el principio de la lista
    if (pos < size() / 2)
      for (i = 0, trav = head; i != pos ; i++)
        trav = trav->next;
    // busca desde el final de la lista
    else
      for (i = size() - 1, trav = tail; i != pos; i--)
        trav = trav->prev;

    return removeNode(trav);
  }

  iterator begin(){ return iterator(head); }

  iterator end(){ return iterator(nullptr); }

  T& operator[](int pos){
    if(pos >= size()) throw "index out of range";
    Node<T> *iter = head;
    for (int i = 0; i < pos; i++)
    {
      iter = iter->next;
    }
    return iter->data;
}

  void display(){
    for (iterator it = begin(); it != end(); ++it){
      cout << *it << " ";
    }
    cout << endl;
  }
};


int main() {
    DoublyLinkedList<int> myList;

    // Agregar elementos
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    // Mostrar la lista
    cout << "Original List: ";
    myList.display(); // Salida esperada: 1 2 3

    // Usar iteradores para recorrer la lista
    cout << "Using Iterator: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Acceder a elementos por índice
    cout << "Accessing by Index: ";
    for (int i = 0; i < myList.size(); ++i) {
        cout << myList[i] << " ";
    }
    cout << endl;

    // Insertar en una posición específica
    myList.insert(10, 1);
    myList.insert(20, 3);

    // Mostrar la lista después de la inserción
    cout << "List after Insertion: ";
    myList.display(); // Salida esperada: 1 10 2 20 3

    // Eliminar un elemento por posición
    myList.remove(2);

    // Mostrar la lista después de la eliminación
    cout << "List after Removal: ";
    myList.display(); // Salida esperada: 1 10 20 3

    return 0;
}
