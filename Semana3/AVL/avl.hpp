// árbol binario
#include <iostream>
#include <queue>
#include <stack>
#include <initializer_list>
using namespace std;

template <typename T>
class AVLTree
{
private:
    int _size{};

    struct Node
    {
        T data;
        Node *left;
        Node *right;
        Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };
    Node *raiz;

public:
    AVLTree() : raiz(nullptr) {}

    int size() { return _size; };

    bool find(T data) { return find(this->raiz, data); }

    // se utiliza para hallar el predecesor y sucesor
    Node *find_root(T data) { return find_root(this->raiz, data); }

    int height() { return height(this->raiz); }

    bool isBalanced() { return isBalanced(this->raiz); }

    void insert(T data)
    {
        insert(this->raiz, data);
    }

    void insert(std::initializer_list<T> &&data)
    {
        for (const auto e : data)
        {
            insert(this->raiz, e);
        }
    } // Insert para varios valores a la vez

    T maxValue()
    {
        return maxValue(this->raiz);
    } // Listo

    T minValue() { return minValue(this->raiz); } // Listo

    void remove(T data)
    {
        cout << "Removing " << data << " ..." << endl;
        remove(this->raiz, data);
    }

    T successor(T value) { return successor(this->raiz, value); }     // Retornar el valor siguiente de "value" en el árbol
    T predecessor(T value) { return predecessor(this->raiz, value); } // Retornar el valor anterior de "value" en el árbol

    void display_in_order() { display_in_order(raiz); }
    void display_pre_order() { display_pre_order(raiz); }
    void display_post_order() { display_post_order(raiz); }
    void displayBFS() { displayBFS(raiz); }
    void displayDFS() { displayDFS(raiz); }

private:
    Node *find_root(Node *root, T data)
    {
        if (root == nullptr)
            throw "arbol vacio";
        if (data < root->data)
        {
            return find_root(root->left, data);
        }
        else if (data > root->data)
        {
            return find_root(root->right, data);
        }
        else
        {
            return root;
        }
    } // Busca y devuelve un nodo con valor == data

    bool find(Node *nodo, T data)
    {
        if (nodo == nullptr)
            return false;
        if (data < nodo->data)
        {
            return find(nodo->left, data);
        }
        else if (data > nodo->data)
        {
            return find(nodo->right, data);
        }
        else
        {
            return true;
        }
    } // True si "data" existe en el arbol, false otherwise

    int height(Node *nodo)
    {
        return nodo == nullptr ? -1 : 1 + max(height(nodo->left), height(nodo->right)); // Credits: Daniel Casquino
    }                                                                                   // One liner chistoso

    bool isBalanced(Node *nodo)
    {
        return nodo == nullptr ? true : abs(height(nodo->left) - height(nodo->right)) <= 1 && isBalanced(nodo->left) && isBalanced(nodo->right);
    }

    int getBalanceFactor(Node *node)
    {
        if (!node)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    } // Devuelve el balanceFactor de un nodo

#pragma region Rotations

    void leftRotation(Node *&x)
    {
        // Guardamos el nodo derecho (el del medio entre los dos nodos)
        Node *y = x->right;
        // El izquierdo del derecho
        Node *bottom = y->left;

        // Conectamos el central con el superior
        y->left = x;
        // Conectamos el superior con el de abajo
        x->right = bottom;

        // Reasignamos y rompemos el enlace extra
        x = y;
    }

    void rightRotation(Node *&y)
    {
        Node *x = y->left;
        Node *bottom = x->right;

        x->right = y;
        y->left = bottom;

        y = x;
    } // Lo mismo pero al reves
    // Me duelen las neuronas que ya no tengo

#pragma endregion

    // mine idea (I don't know if works) --> It works
    void insert(Node *&root, T data)
    {
        if (root == nullptr)
        {
            root = new Node(data);
            _size++;
        }
        else if (root->data < data)
        {
            insert(root->right, data);
        }
        else if (root->data > data)
        {
            insert(root->left, data);
        }
        else
        {
            return;
        }

        int bF = getBalanceFactor(root); // Revisamos si el nodo esta mareadito

        // L
        if (bF > 1)
        {
            if (data < root->left->data)
            {
                // LL Rotation
                rightRotation(root);
            }
            else
            {
                // LR Rotation
                leftRotation(root->left);
                rightRotation(root);
            }
        }
        // R
        else if (bF < -1)
        {
            if (data > root->right->data)
            {
                // RR Rotation
                leftRotation(root);
            }
            else
            {
                // RL Rotation
                rightRotation(root->right);
                leftRotation(root);
            }
        }
    } // Root = nodo actual

    T maxValue(Node *root)
    {
        if (root == nullptr)
            throw "arbo vacio";
        while (root->right != nullptr)
        {
            root = root->right;
        }
        return root->data;
    }

    T minValue(Node *root)
    {
        if (root == nullptr)
            throw "arbol vacio";
        while (root->left != nullptr)
        {
            root = root->left;
        }
        return root->data;
    }

    void remove(Node *&root, T data)
    {
        if (root == nullptr)
            throw "arbol vacio";
        else if (data < root->data)
        {
            remove(root->left, data);
        }
        else if (data > root->data)
        {
            remove(root->right, data);
        } // Busca el nodo hasta encontrar el que se quiere eliminar, mismo principio que el insert
        else
        {
            // sin hijos
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
                _size--;
            }
            // 1 hijo
            else if (root->left == nullptr)
            {
                Node *temp = root;
                root = root->right;
                delete temp;
                _size--;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root;
                root = root->left;
                delete temp;
                _size--;
            }
            // 2 hijos
            else
            {
                int temp = minValue(root->right);
                root->data = temp;
                remove(root->right, temp);
            }
        }

        // Hacemos lo mismo que al insertar

        int bF = getBalanceFactor(root);

        // L
        if (bF > 1)
        {
            if (data < root->left->data)
            {
                // LL Rotation
                rightRotation(root);
            }
            else
            {
                // LR Rotation
                leftRotation(root->left);
                rightRotation(root);
            }
        }
        // R
        else if (bF < -1)
        {
            if (data > root->right->data)
            {
                // RR Rotation
                leftRotation(root);
            }
            else
            {
                // RL Rotation
                rightRotation(root->right);
                leftRotation(root);
            }
        }
    }

    T successor(Node *root, T value)
    {
        Node *current = find_root(value);
        if (current == nullptr)
            throw "sucesor no encontrado";
        if (current->right != nullptr)
        {
            return minValue(current->right);
        }
        else
        {
            Node *successor = nullptr;
            Node *ancestor = root;
            while (ancestor != current)
            {
                if (current->data < ancestor->data)
                {
                    successor = ancestor;
                    ancestor = ancestor->left;
                }
                else
                    ancestor = ancestor->right;
            }
            return successor->data;
        }
    }

    T predecessor(Node *root, T value)
    {
        Node *current = find_root(value);
        if (current == nullptr)
            throw "predecesor no encontrado";
        if (current->left != nullptr)
        {
            return maxValue(current->left);
        }
        else
        {
            Node *predecessor = nullptr;
            Node *ancestor = root;
            while (ancestor != current)
            {
                if (current->data > ancestor->data)
                {
                    predecessor = ancestor;
                    ancestor = ancestor->right;
                }
                else
                    ancestor = ancestor->left;
            }
            return predecessor->data;
        }
    }

    // in_order
    void display_in_order(Node *root)
    {
        if (root == nullptr)
            return;
        display_in_order(root->left);
        cout << root->data << " ";
        display_in_order(root->right);
    }

    // pre_order
    void display_pre_order(Node *root)
    {
        if (root == nullptr)
            return;
        cout << root->data << " ";
        display_pre_order(root->left);
        display_pre_order(root->right);
    }

    // post_order
    void display_post_order(Node *root)
    {
        if (root == nullptr)
            return;
        display_post_order(root->left);
        display_post_order(root->right);
        cout << root->data << " ";
    }

    // BreadthFirstSearch
    void displayBFS(Node *&root)
    {
        if (root == nullptr)
            throw "arbol vacio";
        queue<Node *> QUEUE;
        QUEUE.push(root);
        while (!QUEUE.empty())
        {
            int n = QUEUE.size();
            while (n--)
            {
                Node *nodo = QUEUE.front();
                cout << nodo->data << " ";
                QUEUE.pop();
                if (nodo->left != nullptr)
                    QUEUE.push(nodo->left);
                if (nodo->right != nullptr)
                    QUEUE.push(nodo->right);
            }
        }
    }

    // DepthFirstSearch
    void displayDFS(Node *&root)
    {
        if (root == nullptr)
            throw "arbol vacio";
        stack<Node *> STACK;
        STACK.push(root);
        while (!STACK.empty())
        {
            int n = STACK.size();
            while (n--)
            {
                Node *nodo = STACK.top();
                cout << nodo->data << " ";
                STACK.pop();
                if (nodo->right != nullptr)
                    STACK.push(nodo->right);
                if (nodo->left != nullptr)
                    STACK.push(nodo->left);
            }
        }
    }
};