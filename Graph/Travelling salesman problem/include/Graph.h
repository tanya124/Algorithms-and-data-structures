#ifndef UNTITLED2_GRAPH_H
#define UNTITLED2_GRAPH_H

#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::make_pair;

typedef pair<int, double> pair_id;

class Graph {
public:
    Graph(int verticesNumber);

    ~Graph();

    void AddEdge(int from, int to, double weight);

    void GetRelated(int vertex, vector<pair_id> &vertices) const;

    int VerticesCount() const;

    double getWeight(int from, int to) const;

    void print();

private:
    int verticesNumber;
    vector<vector<double>> matrix;
};


#endif //UNTITLED2_GRAPH_H