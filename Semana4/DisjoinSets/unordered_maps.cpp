#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*DisjoinSet with optimization by rank*/
template<typename T>
class DisjoinSet{
private:
    unordered_map<int,int> parent;
    unordered_map<T,int> rank;
public:
    DisjoinSet() = default;

    DisjoinSet(vector<T>& data){
        for (int i=0 ; i<data.size(); i++) {
            Makeset(i);
        }
    };

    void Makeset(int x){
        parent[x] = x;
        rank[x] = 0;
    };

    int Find(int x){
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void p(){
        cout<<"PADRE: ";
        for (int i = 0; i <parent.size() ; ++i) {
            cout<<parent[i]<<" ";
        }cout<<endl;
    }
    void r(){
        cout<<"RANK:  ";
        for (int i = 0; i <rank.size() ; ++i) {
            cout<<rank[i]<<" ";
        }cout<<endl;
    }

    void Union(int x, int y) {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if (xRoot == yRoot) {
            return;
        }
        if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        }
        else if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        }
        else {
            parent[xRoot] = yRoot;
            rank[yRoot]++;
        }
    };

    int sets(){
        int tam=0;
        for (int i = 0; i <parent.size() ; ++i) {
            if (parent[i] == i) tam+=1;
        }
        return tam;
    };

    bool is_connected(int x, int y){
        if (Find(x)== Find(y)){ return true; }
        else{ return false;}
    };
};

int main(){
    vector<char> data = {'a','b','c','d','e','f','g','h'};
    //                    0   1   2   3   4   5   6   7
    DisjoinSet<char>* ds = new DisjoinSet<char>(data);
    ds->Union(0, 2);//{0,2} 1,3,4,5,6,7
    ds->Union(5, 6);//{0,2} 1,3,4,{5,6},7
    ds->Union(1, 6);//{0,2} {1,5,6}, 3,4,7
    ds->Union(7, 0);//{0,2,7} {1,5,6}, 3, 4
    ds->Union(4, 3);//{0,2,7} {1,5,6}, {3,4}
    cout<<"Conjuntos: "<<ds->sets()<<endl;// 3
    cout<<"1 y 5 estan conectados?: "<<ds->is_connected(1, 5)<<endl; // 1
    cout<<"2 y 4 estan conectados?: "<<ds->is_connected(2, 4)<<endl; // 0
    ds->Union(2, 5);//{0,2,7,1,5,6}, {3,4}
    ds->Union(3, 1);//{0,2,7,1,5,6,3,4}
    cout<<"Conjuntos: "<<ds->sets()<<endl;// 1


    return 0;
}