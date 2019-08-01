#include "../include/Generator.h"

void generator_dots(Graph & graph){
    static std::mt19937 generator;
    std::normal_distribution<double> distribution(0, 10);
    std::vector<dot> dots;

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        dots.emplace_back(make_pair(distribution(generator), distribution(generator)));
    }

    for (int i = 0; i < graph.VerticesCount(); ++i){
        for(int j = 0; j < graph.VerticesCount(); ++j){
            double weight = sqrt(pow(dots[i].first - dots[j].first, 2.0) + pow(dots[i].second - dots[j].second, 2.0));
            graph.AddEdge(i, j, weight);
        }
    }
}