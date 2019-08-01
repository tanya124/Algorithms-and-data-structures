/*Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).*/

/*Алгоритм решения:
	1)В каждой вершине будем хранить глубину вершины относительно начальной вершины
	2)Запускаем bfs от заданной вершины
	BFS
	 1)Создаем вектор хранящий кол-во кратчайших путей до начальной вершины paths
	 2)Если в процессе обхода мы встречаем еще не обработанную вершину (i), то в  paths[i] записываем значение paths от вершины, из корой мы пришли
	 3)Если встречаем уже обработанную вершину (i) и ее глубина равна её глубине относительно текущей ветки обхода, то paths[i] = paths[i] + paths[x], где x - вершина, из которой мы пришли
	 4)Возвращаем paths от 2-ой заданной вершины
*/

#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::min;

class Graph {
public:
    Graph(int n);

    void add(int a, int b);
    void GetNextVertices(int vertex, vector<int> & vertices) const;
    int VerticesCount() const;

private:
    int NumberOfVertices; 
    vector<vector <int>> array; 
};

int BFS(Graph * graph, int vertex1, int vertex2, vector<bool> & visited, vector<int> & depth) {
    int NumberOfVertices = graph->VerticesCount();
    queue<int> processingQueue; 
    vector<int> verticesData(NumberOfVertices); 
    vector<int> paths(NumberOfVertices);
	
    processingQueue.push(vertex1); 
    visited[vertex1] = true;
    paths[vertex1] = 1;

    while (!processingQueue.empty()) { 
        int currentVertex = processingQueue.front();
        processingQueue.pop();
        vector<int> nextVertices; 
        graph->GetNextVertices(currentVertex, nextVertices);

        for (int i : nextVertices) { 
            if (!visited[i]) { 
                processingQueue.push(i); 
                visited[i] = true;
                depth[i] = depth[currentVertex] + 1; 
                paths[i] = paths[currentVertex]; 
            }
            else if (depth[i] == depth[currentVertex] + 1) { 
                paths[i] += paths[currentVertex]; 
            }
        }
    }
    return paths[vertex2];
}

int main() {
    int n, k, vertex1, vertex2;
    cin >> n >> k;
    Graph graph(n);

    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        graph.add(a, b);
    }

    cin >> vertex1 >> vertex2;
    vector<bool> visited;
    vector<int> depth;
    visited.assign(graph.VerticesCount(), false);
    depth.assign(graph.VerticesCount(), 0);

    cout << BFS(&graph, vertex1, vertex2, visited, depth);
}

Graph::Graph(int n) : NumberOfVertices(n), array(n) {}

void Graph::add(int a, int b) {
    array[a].push_back(b);
    array[b].push_back(a);
}

void Graph::GetNextVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (int i : array[vertex])
        vertices.push_back(i);
}

int Graph::VerticesCount() const{
    return NumberOfVertices;
}
