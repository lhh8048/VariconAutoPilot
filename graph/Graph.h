#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <string.h>

typedef std::vector<int> Neighbors;

class Graph {
private:
    const int vn;
    int **matrix;

public:
    Graph(int vn);
    ~Graph();
    int getVN();
    int getDistance(int start, int goal);
    void addEdge(int start, int goal, int distance);
    void viewAllNeighbor() const;
    void viewNeighbor(int vt) const;
    void drawMap(Graph *graph);
    Neighbors findNeighbors(int vt);
};

#endif
