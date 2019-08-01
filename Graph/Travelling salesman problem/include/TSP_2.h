/*Нахождение оптимального решения путем перебора всех возможных вариантов*/
#ifndef UNTITLED2_TSP_2_H
#define UNTITLED2_TSP_2_H

#include "Graph.h"

using std::swap;

class TSP_2 {
public:
    double operator()(const Graph & graph);

private:
    void permutations(int depth);
    double getTourLen();

    Graph const * graph_;
    int n_;
    vector<int> tour_;
    double minTour_;
};


#endif //UNTITLED2_TSP_2_H
