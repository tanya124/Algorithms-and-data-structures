/*Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
Вариант 2. С помощью алгоритма Крускала.*/
/*Алгоритм решения:
 * 0) Для решения используем систему непересекающихся множеств.
 * 1)Храним ребра в сете, где они хранятся в порядке возрастания веса.
 * 2)Поместим каждую вершину в своё дерево.
 * 3)Пребираем все ребра в порядке возрастания веса и определяем, принадлежат ли коны одному дереву.
 * 4)Если концы не принадлежат одному дереву, то объединяем их деревья.
 * */

#include <iostream>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;
using std::set;

class DSU{
public:
    DSU(int N): parent(N), rank(N){
        rank.assign(N, 0);
    }

    void Make_set(int x){
        parent[x] = x;
    }

    int Find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = Find(parent[x]);
    }

    void Unite(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (rank[x] < rank[y])
            parent[x] = y;
        else
        {
            parent[y] = x;
            if (rank[x] == rank[y])
                ++rank[x];
        }
    }

private:
    vector<int> parent; 
    vector<int> rank; 
};

int solver(int n, int m, set<pair<int, pair<int, int>>>& graph){
    DSU dsu(n);
    vector<pair<int, pair<int, int>>> result;
    int sum = 0;

    for (int i = 0; i < n; ++i)
        dsu.Make_set(i);

    for(int i = 0; i < m; ++i){ 
        pair<int, int> rib = (graph.begin())->second;
        int vertex1 = rib.first;
        int vertex2 = rib.second;
        if(dsu.Find(vertex1) != dsu.Find(vertex2)){
            sum += (graph.begin())->first;
            dsu.Unite(vertex1, vertex2);
        }
        graph.erase(graph.begin());
    }

    return sum;
}

int main(){
    int n, m;
    cin >> n >> m;
    set <pair<int, pair<int,int>>> graph;
    for (int i = 0; i < m; ++i){
        int x, y, weight;
        cin >> x >> y >> weight;
        graph.emplace(make_pair(weight, make_pair(x - 1, y - 1)));
    }

    cout << solver(n, m, graph);
}