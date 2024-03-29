/*Полный ориентированный взвешенный граф задан матрицей смежности.
 * Постройте матрицу кратчайших путей между его вершинами.
 * Гарантируется, что в графе нет циклов отрицательного веса.*/

/*Алгоритм решения:
 *Последовательно вычисляем кратчайшие пути между всеми вершинами увеличивая k
 * k - номер фазы (на k-ой фазе путь между вершинами i и j может заходить в промежуточные вешины только с номерами меньшими k(не считая начала и конца пути)))
 * Пусть извесны значения на (k-1) фазе вычислим значения на k фазе.
 *1) Если кратчайший путь из вершины i в вешину j содержит вершину k-1, то этот путь разбивается на 2 части: i-(k-1) и (k-1)-j
 * Каждая из этих частей содержит промежуточные вершины только с номерами, меньшими k-1,
 * поэтому вес такого пути равен a[i][k-1]+a[k-1][j].
 * 2) Если кратчайший путь из вершины i в вешину j не содержит вершину k-1, то вес этого пути равен a[i][j] (вычисленному на k-1 шаге)
 * Выбираем минимум из a[i][k-1]+a[k-1][j] и a[i][j]*/
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;


void floyd(vector<vector<int>> & graph, size_t N) {
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                if (graph[i][j] > graph[i][k] + graph[k][j])
                    graph[i][j] = graph[i][k] + graph[k][j];
            }
}

int main() {
    size_t N;
    cin >> N;
    vector<vector<int>> Matrix(N);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            int x;
            cin >> x;
            Matrix[i].push_back(x);
        }
    }

    floyd(Matrix, N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j)
            cout << Matrix[i][j] << " ";
        cout << endl;
    }

    return 0;
}