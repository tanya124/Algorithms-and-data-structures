/*Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером n.

 Алгоритм решения:
 1)Для каждого ребра сети зададим поток равный 0.
 2)Построим слоистую сеть по отношению к остаточной сети
 3)Найдём блокирующий поток в слоистой сети
 4)Дополним поток найденным блокирующим потоком и перейдём к шагу 2.
 */

#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::vector;
using std::queue;
using std::min;

bool bfs(vector<vector<int>> &graph, vector<int> &lvl) {
    int n = graph.size();
    lvl.resize(n);
    lvl.assign(n, -1);

    int v = 0;
    queue<int> q;
    q.push(v);
    lvl[v] = 0;

    while(!q.empty()) {
        int vertex = q.front();
        q.pop();

        if (vertex == n - 1)
            return true;

        for (int i = 0; i < n; ++i) {
            if (graph[vertex][i] && lvl[i] == -1) {
                q.push(i);
                lvl[i] = lvl[vertex] + 1;
            }
        }
    }
    return false;
}
int dfs(vector<vector<int>> &graph, vector<int> &lvl,int v, int flow, vector<int> &edges) {
    if (!flow)
        return 0;

    int n = graph.size();
    if (v == n - 1)
        return flow;

    for (int &i = edges[v]; i < n; i++)
        if (lvl[i] == lvl[v] + 1 && graph[v][i]) {
            int push = dfs(graph, lvl, i, min(flow, graph[v][i]), edges);
            if (push) {
                graph[v][i] -= push;
                graph[i][v] += push;
                return push;
            }
        }
    return 0;
}
int Dinic(vector<vector<int>> &g) {
    int flow = 0, t;
    int n = g.size();
    vector<int>lvl;
    vector<int> edges(n);

    while(bfs(g, lvl)) {
        t = 1;
        edges.assign(n, 0);
        while(t) {
            t = dfs(g, lvl, 0, INT32_MAX, edges);
            flow += t;
        }
    }
    return flow;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(n,0));

    for(int i = 0; i < m; ++i){
        int x, y, bandwidth;
        cin >> x >> y >> bandwidth;
        graph[x - 1][y - 1] = bandwidth;
    }

    cout << Dinic(graph);

    return 0;
}