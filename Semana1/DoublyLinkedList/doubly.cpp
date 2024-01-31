#include <iostream>
using namespace std;

template <typename T>
struct Node
{
  T data;
  Node<T> *next;
  Node<T> *prev;
  Node(T value = T()) : data(value), next(nullptr), prev(nullptr) {}
  Node(T value, Node<T>* _next, Node<T>* _prev) : data(value), next(_next), prev(_prev) {}
};

template <typename T>
class DoublyLinkedList
{
private:
  int nodes = 0;
  Node<T> *head = nullptr;
  Node<T> *tail = nullptr;

public:
  // O(n)
  void clear(){
    auto *trav = head;
    while (trav != nullptr){
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

  void insert(T data, int pos){
    if (pos <= 1) { push_front(data); } // inserta al inicio si la posición es negativa
    else if (pos > size()) { push_back(data);}// inserta al final si la posición es mayor a la cantidad de nodos
    else{
      auto *nuevo = new Node<T>{data};
      auto *temp = head;
      int i = 1;
      while (++i < pos && temp != nullptr){
        temp = temp->next;
      }
      nuevo->next = temp->next;
      nuevo->prev = temp;
      if (temp->next != nullptr) {
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
  T pop_front(){
    if (isEmpty()) throw out_of_range("List is empty");
    T data = head->data;
    head = head->next;
    --nodes;
    if (isEmpty()) tail = nullptr;
    else{
      delete head->prev;
      head->prev = nullptr;
    }

    return data;
  }

  // O(1)
  T pop_back(){
    if (isEmpty()) throw out_of_range("List is empty");
    T data = tail->data;
    tail = tail->prev;
    --nodes;
    if (isEmpty()) head = nullptr;
    else{
      delete tail->next;
      tail->next = nullptr;
    }

    return data;
  }

  // O(1)
  T removeNode(Node<T>* node){
    if(node->prev == nullptr) {return pop_front();};
    if(node->next == nullptr) {return pop_back();};
    node->next->prev = node->prev;
    node->prev->next = node->next;
    T data = node->data; //  not necessary, we can just remove the node
    delete node;
    --nodes;

    return data; 
  }

  // O(n)
  T remove(int pos){
    if(pos < 0 || pos >= size()) 
      throw invalid_argument("Position is out of range.");
    int i;
    Node<T>* trav;
    // busca desde el principio de la lista
    if (pos < size()/2)
      for (i = 0, trav = head; i != pos-1; i++)
        trav = trav->next;
    // busca desde el final de la lista
    else
      for (i = size() - 1, trav = tail; i != pos-1; i--)
        trav = trav->prev;
    
    return removeNode(trav);
  }

  void display(){
    for (Node<T> *temp = head; temp != nullptr; temp = temp->next){
      cout << temp->data << " ";
    }
    cout << endl;
  }

};

int main(){
  DoublyLinkedList<int> dl;
  dl.push_front(10);
  dl.push_front(20);
  dl.push_front(30);
  dl.push_front(40);
  dl.push_front(50);
  dl.push_front(60);
  dl.push_front(70);
  dl.push_front(80);
  dl.push_back(100);
  cout<< dl.front()<<endl;
  cout<< dl.back()<<endl;

  dl.display();
  cout<< dl.size()<<endl;
  cout<< dl.remove(3)<<endl;
  dl.display();
  cout<< dl.size()<<endl;

  dl.insert(200,3);
  dl.display();
  cout<< dl.size()<<endl;

  dl.clear();
  cout<<"Is empty?: "<<dl.isEmpty()<<endl;
  cout<< dl.size()<<endl;


  return 0; 
}