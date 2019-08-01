/*Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.*/
/*Алгоритм решения:
	1)вызываем bfs от каждой вершины графа
	2)если в процессе обхода нашелся цикл, то bfs возвращает длинну цикла + длинну пути до цикла(в случае, если начальная вершина не входит в цикл)
	3)выбираем цикл наименьшей длинны
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

int BFS(int vertex, Graph * graph, vector<bool> & visited, vector<int> & depth, vector<int>& father) {
    queue<int> processingQueue; 
    vector<int> verticesData(graph->VerticesCount()); 

    processingQueue.push(vertex); 
    visited[vertex] = true;

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
                father[i] = currentVertex;
            }
            else if (i != father[currentVertex]) { 
                return depth[currentVertex] + depth[i] + 1; 
            }
        }
    }
    return graph->VerticesCount() + 1;
}

int minCycle(Graph * graph) {
    vector<bool> visited;
    vector<int> depth;
    vector<int> father;

    int minCycle = graph->VerticesCount() + 1;
    for (int i = 0; i < graph->VerticesCount(); i++) { 
        visited.assign(graph->VerticesCount(), false);
        depth.assign(graph->VerticesCount(), 0);
        father.assign(graph->VerticesCount(), -1);

        int x = BFS(i, graph, visited, depth, father); 

        minCycle = min(x, minCycle);
    }
    return minCycle;
}

int main() {
    int n, k;
    cin >> n >> k;
    Graph graph(n);

    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        graph.add(a, b);
    }

    int minCycl = minCycle(&graph);
    minCycl == n + 1 ? cout << -1 : cout << minCycl;
}


Graph::Graph(int n) : NumberOfVertices(n), array(n) {}

void Graph::add(int a, int b) {
    array[a].push_back(b);
    array[b].push_back(a);
}

void Graph::GetNextVertices(int vertex, vector<int> & vertices) const{
    vertices.clear();
    for (int i : array[vertex])
        vertices.push_back(i);
}

int Graph::VerticesCount() const{
    return NumberOfVertices;
}