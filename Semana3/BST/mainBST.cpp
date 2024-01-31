#include "BST.hpp"
int main(){

  BSTree<int> BST;
  BST.insert(12);
  BST.insert(8);
  BST.insert(20);

  // size --> 3
  cout<<BST.size()<<endl;

  BST.insert(5);
  BST.insert(1);
  BST.insert(15);
  BST.insert(25);
  BST.insert(7);
  BST.insert(11);
  BST.insert(9);
  
  // comprobamos el size --> 10
  cout<<BST.size()<<endl;

  BST.insert(13);
  BST.insert(22);
  BST.insert(18);
  BST.insert(26);

  // comprobamos el size --> 14
  cout<<BST.size()<<endl<<endl;
  
  cout<<"Pre-order: "; BST.display_pre_order(); cout<<endl;
  cout<<"In-order: "; BST.display_in_order(); cout<<endl;
  cout<<"Post-order: "; BST.display_post_order(); cout<<endl;
  cout<<"Anchura: "; BST.displayBFS(); cout<<endl;
  cout<<"Profundidad: "; BST.displayDFS(); cout<<endl;

  // Mínimo valor = 1
  cout<<endl<<"Minimo valor: "<<BST.minValue()<< endl;
  // Máximo valor = 26
  cout<<"Maximo valor: "<<BST.maxValue()<< endl <<endl;

  // true = 1 ; false = 0
  cout<<"Se encuentra el 1?: "<< BST.find(1) <<endl;

  // elimino el elemento 1
  BST.remove(1);
  
  // true = 1 ; false = 0
  cout<<"Se encuentra el 1?: "<< BST.find(1) <<endl <<endl;

  // comprobamos el size --> 13
  cout<<"Size final luego de eliminar el 1: "<< BST.size()<<endl;

  // para verificar que ya no esté el nodo con valor 1
  BST.display_in_order(); cout<<endl;

  // Valor anterior próximo a 15 --> 13
  cout<<endl<<"Predecesor de 15: "<<BST.predecessor(15)<<endl;

  // Valor posterior próximo a 15 --> 18
  cout<<"Sucesor de 15: "<<BST.successor(15)<<endl;


  return 0;
}
