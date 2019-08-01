/*Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.

Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.*/

#include <iostream>
#include <vector>
#include <set>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::set;
using std::make_pair;
using std::list;

const long long infinity = 5000000000;

class CListGraph {
public:
    CListGraph(size_t verticesNumber);

    void AddEdge(int from, int to, int weight);
    size_t VerticesCount() const;
    void GetNextVertices(int vertex, vector<pair<int, int>> & vertices) const;

private:
    size_t NumberOfVertices;
    vector<list<pair<int, int>>> edges; 
};

int Dijkstra(CListGraph &graph, int from, int to) {
    vector<bool> visited(graph.VerticesCount(), false);
    vector<long long> path(graph.VerticesCount(), infinity);
    path[from] = 0;
    set<pair<long long, int>> queue;
    queue.emplace(make_pair(0, from));

    while (!queue.empty()) {
        int vertex = (queue.begin())->second; 
        queue.erase(queue.begin()); 
        visited[vertex] = true; 

        vector<pair<int, int>> paths; 
        graph.GetNextVertices(vertex, paths);
        for (pair<int, int> j : paths) { 
            if (path[j.first] > path[vertex] + j.second){ 
                if (path[j.first] != infinity) 
                    queue.erase(make_pair(path[j.first], j.first)); 

                path[j.first] = path[vertex] + j.second; 
                queue.emplace(pair<long long, int>(path[j.first], j.first));
            }
        }
    }

    return static_cast<int>(path[to]);
}


int main() {
    size_t n, m;
    cin >> n >> m;
    CListGraph graph(n);
    for (size_t i = 0; i < m; ++i) {
        int x, y, time;
        cin >> x >> y >> time;
        graph.AddEdge(x, y, time);
    }
    int from, to;
    cin >> from >> to;
    cout << Dijkstra(graph, from, to);

    return 0;
}

CListGraph::CListGraph(size_t verticesNumber) :
        NumberOfVertices(verticesNumber),
        edges(NumberOfVertices, list<pair<int, int>>())
{}


void CListGraph::AddEdge(int from, int to, int weight) {
    edges[from].emplace_back(make_pair(to, weight));
    edges[to].emplace_back(make_pair(from, weight));
}

size_t CListGraph::VerticesCount() const{
    return NumberOfVertices;
}

void CListGraph::GetNextVertices(int vertex, vector<pair<int, int>> & vertices) const{
    vertices.clear();
    for (pair<int, int> &i : edges[vertex])
        vertices.push_back(i);
}
