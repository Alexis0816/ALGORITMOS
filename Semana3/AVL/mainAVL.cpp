#include "AVL.hpp"

int main()
{
    std::cout << "TEST 1:" << std::endl;
    AVLTree<int> AVL;
    AVL.insert({12, 8, 20});

    // size --> 3
    cout << AVL.size() << endl;

    AVL.insert({5, 1, 15, 25, 7, 11, 9});

    // comprobamos el size --> 10
    cout << AVL.size() << endl;

    AVL.insert({13, 22, 18, 26});

    // comprobamos el size --> 14
    cout << AVL.size() << endl
         << endl;

    AVL.displayBFS();

    std::cout << std::endl
              << std::endl
              << "TEST 2:" << std::endl;

    AVLTree<int> AVL2;
    AVL2.insert({10, 15, 5});
    //  10
    // 5 15

    AVL2.insert({4, 3});
    //    10
    //   5 15
    //  4
    // 3

    // Esta desbalanceado, deberia quedar como
    //   10
    //  4 15
    // 3 5

    // Hacemos BFS para verificar: 10, 4, 15, 3, 5
    AVL2.displayBFS();

    AVL2.insert({2, 1});
    //     10
    //    4 15
    //   3 5
    //  2
    // 1

    // Esta desbalanceado, deberia quedar como
    //       10
    //    4     15
    //  2   5
    // 1 3

    // Sigue desbalanceado en el nodo 10, queda como
    //       4
    //    2     10
    //  1  3   5  15
    // Hacemos BFS para verificar: 4, 2, 10, 1, 3, 5, 15
    std::cout << std::endl;
    AVL2.displayBFS();

    AVL2.insert({6, 14, 16});
    //         4
    //    2        10
    //  1  3    5      15
    //            6   14 16
    std::cout << std::endl;
    AVL2.displayBFS();

    // Ahora eliminamos el nodo 10, deberia quedar como:
    //         4
    //    2        14
    //  1  3    5     15
    //            6      16

    std::cout << std::endl
              << std::endl;
    AVL2.remove(10);

    // Hacemos BFS para verificar: 4, 2, 14, 1, 3, 5, 15, 6, 16
    std::cout << std::endl;
    AVL2.displayBFS();
    return 0;
}