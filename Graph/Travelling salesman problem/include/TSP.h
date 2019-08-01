#ifndef UNTITLED2_TSP_H
#define UNTITLED2_TSP_H

#include "Graph.h"
#include "MST.h"
#include <stack>
#include <limits>

using namespace std;

class TSP {
public:
    TSP(Graph& graph);
    double operator()();

private:
    Graph graph_; //Исходное дерево
    Graph mstree; //Минимальное остовное дерево

    vector<int> odds; //Список вершин в остовном дереве с нечетной степенью
    int n; //Число вершин в исходном графе

    //Поиск лучшего паросочетания на подграфе из нечетных вершин
    void perfectMatching();

    //Поиск Элерова пути
    void euler_tour(int start, vector<int> &path);

    //Преобразование Эйлерова пути в гамильтонов цикл
    void make_hamiltonian(vector<int> &path, double &pathCost);

    //Поиск остовного дерева(алгоритмом Крускала)
    void findMST();

    double findBestPath(int start);

    //Поиск вершин нечетной степени в мин. остовном дереве
    void findOdds();

};


#endif //UNTITLED2_TSP_H
