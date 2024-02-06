#include <iostream>
#include <vector>
#include <map>

using namespace std;
template <typename T>
class DS
{
    int *rank, *parent;
    T data;

public:
    DS(vector<T> &data)
    {
        int n = data.size(); // tamaño para contar conjuntos
        this->data = n;
        rank = new int[n];
        parent = new int[n];
        for (int i = 0; i < this->data; i++)
        {
            MakeSet(i);
        }
    }

    void MakeSet(int x)
    {
        parent[x] = x;
        rank[x] = 0;
    }

    int Find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if (xRoot == yRoot)
            return;
        if (rank[xRoot] > rank[yRoot])
        {
            parent[yRoot] = xRoot;
        }
        else if (rank[xRoot] < rank[yRoot])
        {
            parent[xRoot] = yRoot;
        }
        else
        {
            parent[xRoot] = yRoot;
            rank[yRoot]++;
        }
    }

    bool is_connected(int x, int y)
    {
        if (Find(x) == Find(y))
        {
            return true;
        }
        else
        {
            return false;
        }
    };
};

class Solution
{
public:
    int swimInWater(vector<vector<int>> &grid){
        map<DS<int> *, int> map;

        int index = 0;
        int max;
        for (auto outer = grid.begin(); outer != grid.end(); ++outer){
            for (auto inner = outer->begin(); inner != outer->end(); ++inner){
                
                int t = index;
                vector<int> ele;
                ele.push_back(*inner);
                DS<int> *ds = new DS<int>(ele);
                map.insert(pair<DS<int>*,int>(ds, t));
                index++;

                if (ds->is_connected(0, 1)){
                    max = t;
                }
                if (ds->is_connected(0, 2)){
                    max = t;
                }
                if (ds->is_connected(0, 3)){
                    max = t;
                }
            }
        }
        return max; 
    }
};
int main()
{
    vector<vector<int>> grid = {{0, 1},
                                {2, 3}};
    Solution s;

    int max = s.swimInWater(grid);
    cout << max << endl;


    

    return 0;
}
