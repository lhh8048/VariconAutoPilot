#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph(int vn):vn(vn) {
    matrix = new int *[vn];

    for(int i = 0; i < vn; i++) {
        matrix[i] = new int[vn];
        memset(matrix[i], 0, sizeof(int) * vn);
    }
}

Graph::~Graph() {
    for(int i = 0; i < vn; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int Graph::getVN() {
        return this->vn;
}

int Graph::getDistance(int start, int goal) {
    if(matrix[start][goal] > 0) {
        cout << "(" << start << "<->" << goal << ")의 길이: " <<
        matrix[start][goal] << endl; 

        return matrix[start][goal];
    }
    else {
        cout << "road not found" << endl;
        return 0;
    }
}

void Graph::addEdge(int start, int goal, int distance) {
    matrix[start][goal] = distance;
    matrix[goal][start] = distance;
}

void Graph::viewAllNeighbor() const {
    cout << "=== 모든 이웃 접점==" << endl;

    for(int i = 0; i < vn; i++) {
        cout << i << "의 이웃: ";
        viewNeighbor(i);
    }
    
    cout << endl;
}

void Graph::viewNeighbor(int vt) const {
    for(int i = 0; i < vn; i++) {
        if(matrix[vt][i] > 0) {
            cout << i << " ";
        }
    }

    cout << endl;
}

void Graph::drawMap(Graph *graph) {
    graph->addEdge(0, 1, 4);
    graph->addEdge(0, 3, 7);
    graph->addEdge(0, 4, 4);

    graph->addEdge(1, 2, 4);
    graph->addEdge(1, 5, 4);

    graph->addEdge(2, 2, 12);
    graph->addEdge(2, 6, 4);

    graph->addEdge(3, 4, 4);
    graph->addEdge(3, 7, 7);

    graph->addEdge(4, 5, 4);
    graph->addEdge(4, 7, 4);

    graph->addEdge(5, 8, 4);

    graph->addEdge(6, 8, 7);

    graph->addEdge(7, 8, 4);
}

Neighbors Graph::findNeighbors(int vt) {
    Neighbors neighbors;

    for(int i = 0; i < vn; i++) {
        if(matrix[vt][i] > 0) {
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

