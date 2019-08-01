/*Дан ориентированный граф. Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным. В графе возможны петли.*/

/*Алгоритм решения:
	1)Ищем компоненты сильной связности алгоритмом Косарайю
	2)Добавляем все найденные компоненты в вектор all_component
	3)Если рассматривать компоненты, как вершины графа, то в результате мы получим ациклический орграф
	4)Найдем кол-во вершин не имеющих входящие ребра(корни) и не имеющих исходящие ребра(листья)
	5)Ответом будет являтся наибольшее из найденных чисел, т.к. если рассматривать граф, как дерево, то чтобы добраться из листа в корень нам необходимо добавить ребро из листа в корень
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using std::cin;
using std::cout;
using std::vector;
using std::unordered_set

class Graph {
public:
    Graph(int n);

    void add(int from, int to);
    void get_number_edges();

private:
    void DFS1(int vertex); 
    void DFS2(int vertex); 
    void check_type() const;
    bool is_type1(int id) const; 
    bool is_type2(int id) const;

    vector<unordered_set<int>> array; 
    vector<unordered_set<int>> tr_array;
    vector<bool> visited;
    vector<int> order; 
    unordered_set<int> component;
    vector<unordered_set<int>> all_component;
    int NumberVertices; 
};

int main() {
    int n, k;
    cin >> n >> k;
    Graph graph(n);

    for (int i = 0; i < k; ++i) {
        int from, to;
        cin >> from >> to;
        if (from != to)
            graph.add(from - 1, to - 1);
    }
    graph.get_number_edges();
    return 0;
}

Graph::Graph(int n) : NumberVertices(n), array(n), tr_array(n) {}

void Graph::get_number_edges() { //Косарайю
    int NumberComponent = 0;
    visited.assign(NumberVertices, false);
    for (int i = 0; i < NumberVertices; ++i) {
        if (!visited[i])
            DFS1(i);
    }

    visited.assign(NumberVertices, false);
    for (int i = 0; i < NumberVertices; ++i) {
        int v = order[NumberVertices - 1 - i];
        //cout << v << endl;
        if (!visited[v]) {
            DFS2(v);
            all_component.push_back(component);
            component.clear();
        }
    }
    check_type();
}

void Graph::DFS1(int vertex) {
    visited[vertex] = true;
    for (int i : tr_array[vertex])
        if (!visited[i])
            DFS1(i);
    order.push_back(vertex);
}

void Graph::DFS2(int vertex) {
    visited[vertex] = true;
    component.insert(vertex);
    for (int i : array[vertex])
        if (!visited[i])
            DFS2(i);
}

void Graph::check_type() const{ 
    int type1 = 0; 
    int type2 = 0; 
    if(all_component.size() != 1) 
        for (int i = 0; i < all_component.size(); ++i) {
            if (is_type1(i)) 
                type1++;
            if (is_type2(i)) 
                type2++;
        }


    (type1 > type2 ? cout << type1 : cout << type2);
}

bool Graph::is_type1(int id) const{ 
    for (int j : all_component[id])
        for (int k : array[j])
            if ((all_component[id]).count(k) == 0) 
                return false;

    return true;
}

bool Graph::is_type2(int id) const{ 
    for (int j : all_component[id])
        for (int k : tr_array[j])
            if ((all_component[id]).count(k) == 0)  
                return false;

    return true;
}


void Graph::add(int from, int to) {
    array[from].insert(to);
    tr_array[to].insert(from);
}