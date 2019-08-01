#include "../include/MST.h"


void MST(const Graph &graph, Graph & result){ //Алгоритм Крускала
    DSU dsu(graph.VerticesCount());

    vector<pair<double, pair<int, int>>> edges;

    for(int i = 0; i < graph.VerticesCount(); ++i){
        for(int j = 0; j < graph.VerticesCount(); ++j){
            if (graph.getWeight(i, j) > 0)
                edges.emplace_back(make_pair(graph.getWeight(i, j), make_pair(i, j)));
        }
    }

    sort(edges.begin(), edges.end());

    for (int i = 0; i < graph.VerticesCount(); ++i)
        dsu.Make_set(i);

    for(pair<double, pair<int, int>> i : edges){
        pair<int, int> rib = i.second;
        int vertex1 = rib.first;
        int vertex2 = rib.second;
        if(dsu.Find(vertex1) != dsu.Find(vertex2)){
            result.AddEdge(vertex1, vertex2, i.first);
            dsu.Unite(vertex1, vertex2);
        }
    }

    edges.clear();
}