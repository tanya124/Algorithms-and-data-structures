#include "../include/DSU.h"

DSU::DSU(int N): parent(N), rank(N) {
    rank.assign(N, 0);
}

DSU::~DSU(){
    parent.clear();
    rank.clear();
}

void DSU::Make_set(int x){
    parent[x] = x;
}

int DSU::Find(int x) {
    if (parent[x] == x)
        return x;
	
    return parent[x] = Find(parent[x]);
}

void DSU::Unite(int x, int y) {
    x = Find(x);
    y = Find(y);
	
    if (rank[x] < rank[y])
        parent[x] = y;
    else
    {
        parent[y] = x;
        if (rank[x] == rank[y])
            ++rank[x];
    }
}