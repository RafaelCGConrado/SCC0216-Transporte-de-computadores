#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

typedef struct _position{
    int _next; // Vértice para onde o Pacman foi no movimento
    int _cost;
}position;

// Color: 0 = branco, 1 = cinza, 2 = preto
typedef struct _vertex{
    vector<position> _near;
    int _distance = INT_MAX;
    int _predecessor = -1;
}vertex;


class Graph{
    private:
        int _vertexes;
        int _edges;
        vector<vertex> _graph;
    public:
        Graph(int vertexes, int edges);
        // 0 1 1
        // 0 -> {1|1}
        // 1 -> {0|1}
        void addEdge(int originVertex, int destinyVertex, int cost);
        int getVertexes();
        int getEdges();
        vertex getNode(int position);
        void printGraph();
        void resetGraph();
        // vector<char> BreadthFirstSearch(int pacmanPosition, int ghostPosition, bool &foundByGhost);
};


#endif