/*Проверить граф на двудольность*/

/*Алгоритм решения:
	1)В каждой вершине храним тип доли, которой принадлежит вершина
	2)Запускаем bfs
	3)Если в процессе обхода мы встречаем уже обработанную вершину, которая принадлежит той же доле,
	  что и вершина, из которой мы пришли в нее, то граф не двудольный
*/
#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::queue;


class Graph {
public:
    Graph(int n);

    void add(int a, int b);
    void GetNextVertices(int vertex, vector<int> & vertices) const;
    int VerticesCount()const;

private:
    int NumberOfVertices; 
    vector<vector <int>> array; 
};

bool BFS(Graph * graph, vector<bool> & visited, vector<int> & type) {
    int NumberOfVertices = graph->VerticesCount();
    queue<int> processingQueue; 
    vector<int> verticesData(NumberOfVertices); 

    processingQueue.push(0); 
    visited[0] = true;

    while (!processingQueue.empty()) { 
        int currentVertex = processingQueue.front();
        processingQueue.pop();
        vector<int> nextVertices; 
        graph->GetNextVertices(currentVertex, nextVertices);

        for (int i : nextVertices) { 
            if (!visited[i]) {
                processingQueue.push(i); 
                visited[i] = true;
                type[i] = (type[currentVertex] + 1) % 2;
            }
            else if (type[i] == type[currentVertex]) {
                return false; 
            }
        }
    }
    return true;
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
    vector<bool> visited;
    vector<int> type;
    visited.assign(n, false);
    type.assign(n, 0);

    if (BFS(&graph, visited, type))
        cout << "YES";
    else
        cout << "NO";

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

