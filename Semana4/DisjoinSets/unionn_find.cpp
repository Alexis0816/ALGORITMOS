#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
private:
    vector<int> parent;

public:
    UnionFind(int size) {
        parent.resize(size);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;  // Inicialmente, cada elemento es su propio representante.
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            // Si el elemento no es su propio representante, encontrar el representante recursivamente.
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        // Unir dos conjuntos representados por x e y.
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            parent[rootX] = rootY;  // Establecer el representante de un conjunto como el representante del otro.
        }
    }
};

int main() {
    UnionFind uf(6);  // Crear una estructura Union-Find con 6 elementos.

    // Realizar algunas operaciones de unión.
    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(4, 5);

    // Realizar algunas operaciones de búsqueda.
    std::cout << "Representante de 1: " << uf.find(1) << std::endl;
    std::cout << "Representante de 4: " << uf.find(4) << std::endl;

    // Verificar si dos elementos pertenecen al mismo conjunto.
    std::cout << "1 y 3 pertenecen al mismo conjunto: " << (uf.find(1) == uf.find(3) ? "Si" : "No") << std::endl;

    return 0;
}