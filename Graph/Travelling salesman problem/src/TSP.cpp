#include "../include/TSP.h"

double TSP::operator()(){

    findMST();
    perfectMatching();

    return findBestPath(0);
}

TSP::TSP(Graph& graph): graph_(graph), n(graph.VerticesCount()), mstree(graph){
    for(int i = 0; i < graph.VerticesCount(); ++i)
        for(int j = i + 1; j < graph.VerticesCount(); ++j)
            mstree.AddEdge(i, j, 0);
}

void TSP::findMST() {
    MST(graph_, mstree);
}

void TSP::findOdds() {
    for(int i = 0; i < n; ++i){
        int k = 0;

        for(int j = 0; j < n; ++j)
            if(mstree.getWeight(i, j) != 0)
                k += 1;


        if(k%2 != 0)
            odds.push_back(i);
    }
}

//Поиск лучшего паросочетания (Жадным алгоритмом)
void TSP::perfectMatching() {

    if (graph_.VerticesCount() == 2)
        return;

    int closest;
    double length;
    vector<int>::iterator tmp, first;

    findOdds();

    while(!odds.empty()) { //Перебираем все нечетные вершины
        first = odds.begin();
        vector<int>::iterator it = odds.begin() + 1;
        vector<int>::iterator end = odds.end();
        length = std::numeric_limits<int>::max();

        for (; it != end; ++it) {
            //Если вершина ближе к first, чем текущая ближайшая и first и эта вершина не соедененны ребром
            if (graph_.getWeight(*first, *it) < length && mstree.getWeight(*first, *it) == 0) {
                length = graph_.getWeight(*first, *it);
                closest = *it;
                tmp = it;
            }
        }

        mstree.AddEdge(closest, *first, length);
        odds.erase(tmp);
        odds.erase(first);
    }
}

void TSP::euler_tour(int start, vector<int> &path){
    Graph tmpMST = mstree; //Создаем копию исходного дерева

    stack<int> stack;
    int pos = start;

    vector<pair_id> related; //Соседи текущей вершины
    tmpMST.GetRelated(pos, related);

    while(!stack.empty() || !related.empty()){

        if(related.empty()){
            path.push_back(pos);
            pos = stack.top();
            stack.pop();
            tmpMST.GetRelated(pos, related);
        }
        else{
            stack.push(pos);
            int neighbor = related.back().first;
            tmpMST.AddEdge(pos, neighbor, 0); //Удаляем соседа
            pos = neighbor;
            tmpMST.GetRelated(pos, related);
        }
    }

    path.push_back(pos);
}


void TSP::make_hamiltonian(vector<int> &path, double &pathCost){
    if(graph_.VerticesCount() == 2){
        pathCost = graph_.getWeight(0, 1) * 2;
        return;
    }

    vector<bool> visited(n, false);

    pathCost = 0;

    int root = path.front();
    vector<int>::iterator cur = path.begin();
    vector<int>::iterator iter = path.begin()+1;
    visited[root] = true;

    while(iter != path.end()){ //Пока не придем в последнюю вершину
        if(!visited[*iter]){ //Если вершина не посещена
            pathCost += graph_.getWeight(*cur, *iter);
            cur = iter;
            visited[*cur] = true;
            iter = cur + 1;
        }
        else{ // Если уже посещена, удаляем ее из пути
            iter = path.erase(iter);
        }
    }

    pathCost += graph_.getWeight(*cur, *iter);
}

double TSP::findBestPath(int start){
    vector<int> path;
    euler_tour(start, path);

    double length;
    make_hamiltonian(path, length);

    return length;
}