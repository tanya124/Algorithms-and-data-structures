#include "../include/TSP_2.h"

double TSP_2::operator()(const Graph & graph) {
    graph_ = &graph;
    n_ = graph_->VerticesCount();

    if(n_ <= 1)
        return 0;

    tour_.clear();

    for(int i = 1; i < n_; i++)
        tour_.push_back(i);

    minTour_ = getTourLen();

    permutations(1);

    return minTour_;
}


void TSP_2::permutations(int depth) {
    if(depth == tour_.size()){
        double tour = getTourLen();
        if(tour < minTour_)
            minTour_ = tour;
        return;
    }

    for(int i = 0; i <= depth; i++){
        swap(tour_[i], tour_[depth]);
        permutations(depth + 1);
        swap(tour_[i], tour_[depth]);
    }
}


double TSP_2::getTourLen(){
    double tour = graph_->getWeight(tour_[n_ - 2], 0) + graph_->getWeight(0, tour_[0]);

    for(int i = 1; i < n_ - 1; i++)
        tour += graph_->getWeight(tour_[i - 1], tour_[i]);

    return tour;
}