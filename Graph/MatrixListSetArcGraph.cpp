#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

using std::unordered_set;
using std::list;
using std::vector;

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual void GetNextVertices(int vertex, vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, vector<int>& vertices) const = 0;
};

/**************************CArcGraph****************************************/
class CArcGraph : public IGraph {
public:
    explicit CArcGraph(size_t verticesNumber);
    explicit CArcGraph(const IGraph * graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;
    virtual void GetNextVertices(int vertex, vector<int> & vertices) const override;
    virtual void GetPrevVertices(int vertex, vector<int> & vertices) const override;

private:
    struct Edge {
        int from;
        int to;

        Edge(int from, int to);
    };

    size_t NumberOfVertices;
    vector<Edge> edges;
};

CArcGraph::CArcGraph(size_t verticesNumber) : NumberOfVertices(verticesNumber) {}

CArcGraph::CArcGraph(const IGraph * graph) : NumberOfVertices(graph->VerticesCount()) {
    for (int i = 0; i < NumberOfVertices; i++) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

void CArcGraph::AddEdge(int from, int to) {
    for (const Edge & i : edges) 
        if (i.from == from && i.to == to)
            return;

    Edge edge(from, to);
    edges.push_back(edge);
}

int CArcGraph::VerticesCount() const {
    return NumberOfVertices;
}

void CArcGraph::GetNextVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (const Edge & i : edges)
        if (i.from == vertex)
            vertices.push_back(i.to);
}

void CArcGraph::GetPrevVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (const Edge & i : edges)
        if (i.to == vertex)
            vertices.push_back(i.from);
}

CArcGraph::Edge::Edge(int from, int to) : from(from), to(to) {}

/***************************CSetGraph***************************************/

class CSetGraph : public IGraph {
public:
    explicit CSetGraph(size_t verticesNumber);
    explicit CSetGraph(const IGraph * graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;
    virtual void GetNextVertices(int vertex, vector<int> & vertices) const override;
    virtual void GetPrevVertices(int vertex, vector<int> & vertices) const override;

private:
    size_t NumberOfVertices;
    vector<unordered_set<int>> out;
    vector<unordered_set<int>> in;
};

CSetGraph::CSetGraph(size_t verticesNumber) : NumberOfVertices(verticesNumber), 
    out(NumberOfVertices),  in(NumberOfVertices) {}

CSetGraph::CSetGraph(const IGraph * graph) :
    NumberOfVertices(graph->VerticesCount()),
    out(NumberOfVertices),
    in(NumberOfVertices)
{
    for (size_t i = 0; i < NumberOfVertices; i++) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

void CSetGraph::AddEdge(int from, int to) {
    out[from].insert(to);
    in[to].insert(from);
}

int CSetGraph::VerticesCount() const {
    return NumberOfVertices;
}

void CSetGraph::GetNextVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (int i : out[vertex])
        vertices.push_back(i);
}

void CSetGraph::GetPrevVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (int i : in[vertex])
        vertices.push_back(i);
}

/****************************CMatrixGraph**************************************/

class CMatrixGraph : public IGraph {
public:
    explicit CMatrixGraph(size_t verticesNumber);
    explicit CMatrixGraph(const IGraph * graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;
    virtual void GetNextVertices(int vertex, vector<int> & vertices) const override;
    virtual void GetPrevVertices(int vertex, vector<int> & vertices) const override;

private:
    size_t NumberOfVertices;
    vector<vector<bool>> edges;
};

CMatrixGraph::CMatrixGraph(size_t verticesNumber) : NumberOfVertices(verticesNumber), edges(NumberOfVertices) {
    for (vector<bool> & i : edges)
        i.assign(NumberOfVertices, false);
}

CMatrixGraph::CMatrixGraph(const IGraph * graph) :
    NumberOfVertices(graph->VerticesCount()),
    edges(NumberOfVertices)
{
    for (vector<bool> & i : edges)
        i.assign(NumberOfVertices, false);

    for (size_t i = 0; i < NumberOfVertices; i++) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

void CMatrixGraph::AddEdge(int from, int to) {
    edges[from][to] = true;
}

int CMatrixGraph::VerticesCount() const {
    return NumberOfVertices;
}

void CMatrixGraph::GetNextVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (size_t i = 0; i < NumberOfVertices; i++)
        if (edges[vertex][i])
            vertices.push_back(i);
}

void CMatrixGraph::GetPrevVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (size_t i = 0; i < NumberOfVertices; i++)
        if (edges[i][vertex])
            vertices.push_back(i);
}

/******************************CListGraph************************************/

class CListGraph : public IGraph {
public:
    explicit CListGraph(size_t verticesNumber);
    explicit CListGraph(const IGraph * graph);

    virtual void AddEdge(int from, int to) override;
    virtual int VerticesCount() const override;
    virtual void GetNextVertices(int vertex, vector<int> & vertices) const override;
    virtual void GetPrevVertices(int vertex, vector<int> & vertices) const override;

private:
    size_t NumberOfVertices;
    vector<list<int>> in;
    vector<list<int>> out;
};

CListGraph::CListGraph(size_t verticesNumber) :
    NumberOfVertices(verticesNumber),
    in(NumberOfVertices),
    out(NumberOfVertices)
{}

CListGraph::CListGraph(const IGraph * graph) :
    NumberOfVertices(graph->VerticesCount()),
    in(NumberOfVertices),
    out(NumberOfVertices)
{
    for (size_t i = 0; i < NumberOfVertices; i++) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

void CListGraph::AddEdge(int from, int to) {
    if (in.size() < out.size()) {
        for (int i : in[to])
            if (i == from)
                return;
    }
    else {
        for (int i : out[from])
            if (i == to)
                return;
    }

    in[to].push_back(from);
    out[from].push_back(to);
}

int CListGraph::VerticesCount() const {
    return NumberOfVertices;
}

void CListGraph::GetNextVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (int i : out[vertex])
        vertices.push_back(i);
}

void CListGraph::GetPrevVertices(int vertex, vector<int> & vertices) const {
    vertices.clear();
    for (int i : in[vertex])
        vertices.push_back(i);
}

/******************************************************************/

std::ostream& operator<<(std::ostream& os, IGraph& g) {
    vector<int> v;
    for (int i = 0; i < g.VerticesCount(); i++) {
        os << i << ": ";
        g.GetNextVertices(i, v);
        for (int j : v) {
            os << j << ", ";
        }
        os << std::endl;
    }
    return os;
}

void testGraph(IGraph& g) {
    g.AddEdge(0, 1);
    g.AddEdge(1, 2);
    g.AddEdge(2, 0);
    g.AddEdge(0, 4);
    g.AddEdge(4, 1);
    g.AddEdge(0, 3);
    g.AddEdge(3, 1);
    std::cout << g;
}

int main() {
    std::cout << "CMatrixGraph:\n";
    CMatrixGraph a(5);
    testGraph(a);

    std::cout << "CListGraph:\n";
    CListGraph b(5);
    testGraph(b);

    std::cout << "CSetGraph\n";
    CSetGraph w(5);
    testGraph(w);

    std::cout << "CArcGraph:\n";
    CArcGraph t(5);
    testGraph(t);

    CMatrixGraph mg(&t);
    std::cout << "CMatrixGraph:\n";
    std::cout << mg << std::endl;
    CListGraph lg(&a);
    std::cout << "CListGraph:\n";
    std::cout << lg << std::endl;
    CSetGraph sg(&b);
    std::cout << "CSetGraph\n";
    std::cout << sg << std::endl;
    CArcGraph ag(&w);
    std::cout << "CArcGraph:\n";
    std::cout << ag << std::endl;

    return 0;
}
