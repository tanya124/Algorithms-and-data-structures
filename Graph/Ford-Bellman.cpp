/*Первая строка содержит число N – количество возможных валют (определяет размер таблицы котировок).
Далее следует построчное представление таблицы. Диагональные элементы (i, i) пропущены (подразумевается, что курс валюты к себе же 1.0).
В элементе таблицы (i, j) содержится обменный курс i->j.
Если обмен в данном направлении не производится, то -1.
 Выведите YES, если арбитраж есть, и NO, иначе.*/
/*Алгоритм решения:
 * Если в графе есть отрицательный цикл, то арбитраж существует.
 * Проверим наличие цикла алгоритмом Форда-Белмана
 * Описание алгоритма:
 * -рассматриваем все ребра графа. На каждой фазе рассмотрения ребра будем пытаться сделать релаксацию вдоль каждого ребра
 * -ограничим число фаз числом N-1
 * -если после N-1 фазы мы выполним ещё одну фазу, и на ней произойдёт хотя бы одна релаксация,
 * то граф содержит цикл отрицательного веса, достижимый из v; в противном случае, такого цикла нет.
 * */

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

class CMatrixGraph{
public:
    CMatrixGraph(size_t verticesNumber);

    void AddEdge(int from, int to, double weight);
    int VerticesCount() const;
    void GetPrevVertices(int vertex, vector<int> & vertices) const;
    double GetWeight(int x, int y) const;

private:
    size_t NumberOfVertices;
    vector<vector<double>> edges;
};

bool BellmanFord(CMatrixGraph &graph) {
    for (int k = 0; k < graph.VerticesCount(); k++) {
        vector<double> dist(graph.VerticesCount(), -1.0);
        dist[k] = 1.0;
        vector<int> vertices(graph.VerticesCount());

        for (int i = 0; i < graph.VerticesCount() - 1; i++) {
            for (int v = 0; v < graph.VerticesCount(); v++) {
                graph.GetPrevVertices(v, vertices);
                for (int u : vertices)
                    if (dist[u] != -1.0 && dist[v] < dist[u] * graph.GetWeight(u, v))
                        dist[v] = dist[u] * graph.GetWeight(u, v);
            }
        }

        for (int v = 0; v < graph.VerticesCount(); v++) {
            graph.GetPrevVertices(v, vertices);
            for (int u : vertices)
                if (dist[u] != -1.0 && dist[v] < dist[u] * graph.GetWeight(u, v))
                    return true;
        }
    }
    return false;
}

int main() {
    size_t n;
    cin >> n;
    CMatrixGraph graph(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i == j)
                continue;
            double weight;
            cin >> weight;
            graph.AddEdge(i, j, weight);
        }
    }
    cout << ((BellmanFord(graph))?"YES":"NO");
    return 0;
}

CMatrixGraph::CMatrixGraph(size_t verticesNumber) : 
		NumberOfVertices(verticesNumber), edges(NumberOfVertices, vector<double>(NumberOfVertices, 1)) {

}

void CMatrixGraph::AddEdge(int from, int to, double weight) {
    edges[from][to] = weight;
}

int CMatrixGraph::VerticesCount()const{
    return NumberOfVertices;
}

void CMatrixGraph::GetPrevVertices(int vertex, vector<int> & vertices) const{
    vertices.clear();
    for (size_t i = 0; i < NumberOfVertices; i++)
        if (edges[i][vertex] != -1)
            vertices.push_back(i);
}

double CMatrixGraph::GetWeight(int x, int y) const{
    return edges[x][y];
}