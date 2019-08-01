#include "../include/Graph.h"

Graph::Graph(int verticesNumber) :
        verticesNumber(verticesNumber),
        matrix(verticesNumber, vector<double>(verticesNumber, 0.0)) {}

Graph::~Graph(){
    for(int i = 0; i < verticesNumber; ++i)
        matrix[i].clear();

    matrix.clear();
}

void Graph::AddEdge(int from, int to, double weight) {
    matrix[from][to] = weight;
    matrix[to][from] = weight;
}

void Graph::GetRelated(int vertex, vector<pair_id> &vertices) const {
    vertices.clear();
    for(int i = 0; i < verticesNumber; i++){
        if(matrix[vertex][i] != 0)
            vertices.emplace_back(make_pair(i, matrix[vertex][i]));
    }
}

int Graph::VerticesCount() const{
    return verticesNumber;
}

double Graph::getWeight(int from, int to) const {
    return matrix[from][to];
}

void Graph::print() {
    for(int i = 0; i < verticesNumber; ++i){
        for(int j = 0; j < verticesNumber; ++j){
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}