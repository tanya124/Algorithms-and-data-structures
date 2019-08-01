//
// Created by 1162244 on 20.04.2019.
//

#ifndef UNTITLED2_DSU_H
#define UNTITLED2_DSU_H

#include <vector>

class DSU {
public:
    DSU(int N);
    ~DSU();

    void Make_set(int x);

    int Find(int x);

    void Unite(int x, int y);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif //UNTITLED2_DSU_H
