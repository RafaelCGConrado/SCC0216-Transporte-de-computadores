#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

typedef struct _position{
    int _next; 
    int _cost;
}position;

typedef struct _edge{
    int _source;
    int _destination;
    int _cost;
}edge;

// Color: 0 = branco, 1 = cinza, 2 = preto
typedef struct _vertex{
    vector<position> _near;
    int _distance;
    int _predecessor;
    int _color;
}vertex;

// _graph[i]._near[j].next
class Graph{
    private:
        int _vertexCount;
        int _edgeCount;
        vector<vertex> _graph;
        vector<edge> _edges;
    public:
        Graph(int vertexes, int edges);
        void addEdge(int originVertex, int destinyVertex, int cost);
        int getVertexes();
        int getEdges();
        vertex getNode(int position);
        int getCost(int source, int destination);
        void printGraph();
        void resetGraph();
        vector<int> bellmanFord(int current, int target);
        int Standard();
        int VIP(int target);
        vector<int> DFS(int vertex, vector<int> path);
        vector<int> BreadthFirstSearch(int pacmanPosition, int ghostPosition);
};


#endif