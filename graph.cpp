#include "graph.hpp"

//Constrói o grafo
Graph::Graph(int vertexCount, int edgeCount){
    _vertexCount = vertexCount;
    _edgeCount = edgeCount;
    _graph.resize(_vertexCount);
    
    //Define os antecessores como -1
    //e define as distâncias iniciais com o máximo valor possível
    for (int i = 0; i < _vertexCount; i++){
        _graph[i]._distance = INT_MAX;
        _graph[i]._predecessor = -1;
    }
}

//Adiciona uma aresta entre dois vértices do grafo
void Graph::addEdge(int originVertex, int destinyVertex, int cost){
    position pos1;
    pos1._next = destinyVertex;
    pos1._cost = cost;

    position pos2;
    pos2._next = originVertex;
    pos2._cost = cost;
    
    _graph[originVertex]._near.push_back(pos1);
    _graph[destinyVertex]._near.push_back(pos2);

    edge e;
    e._source = originVertex;
    e._destination = destinyVertex;
    e._cost = cost;

    _edges.push_back(e);
}      

//Retorna a quantidade de vértices do grafo
int Graph::getVertexes(){
    return _vertexCount;
}

//Retorna a quantidade de arestas do grafo
int Graph::getEdges(){
    return _edgeCount;
}

//Retorna o custo/peso de uma determinada aresta
int Graph::getCost(int source, int destination){
    for (int i = 0; i < _edgeCount; i++){
        if (source == _edges[i]._source && destination == _edges[i]._destination)
            return _edges[i]._cost;
    }
    return 0;
}

//Retorna o nó do grafo
vertex Graph::getNode(int position){
   return _graph[position];  
}


//Printa o gráfico, mostrando cada vértice e suas adjacências
//(Usado meramente para testes)
void Graph::printGraph(){
    for (int i = 0; i < _vertexCount; i++){
        int actualEdges = _graph[i]._near.size();
        
        cout << i;
        for (int j = 0; j < actualEdges; j++){
            cout << " -> {" << _graph[i]._near[j]._next << "|" << _graph[i]._near[j]._cost << "}";
        }

        cout << endl;
    }
}

//Inverte os elementos de um vector
void flip(vector<int> &v){
    int size = v.size();
    int j = size-1;
    for(int i = 0; i < j; i++) {
        swap(v[i], v[j]);
        j--;
    }
}

//Algoritmo de Bellman Ford utilizado para determinar
//os caminhos de menor custo a partir do vértice atual
//e do vértice de destino
vector<int> Graph::bellmanFord(int current, int target){
    _graph[current]._distance = 0;

    //Promove o relaxamento das arestas:
    for(int i = 0; i < _vertexCount-1; i++) {
        for(int j = 0; j < _edgeCount; j++) {
            int u = _edges[j]._source;
            int v = _edges[j]._destination;
            int w = _edges[j]._cost;
            

            if(_graph[u]._distance != INT_MAX && _graph[u]._distance + w <= _graph[v]._distance){
                _graph[v]._distance = _graph[u]._distance + w;
                _graph[v]._predecessor = u;
                
            }
        }
    }

    // Guarda o caminho obtido em um vector
    vector<int> path;
    int predecessor = _graph[target]._predecessor;
    while (predecessor > -1){
        path.push_back(predecessor);
        predecessor = _graph[predecessor]._predecessor;
    }
    
    //Inverte o caminho (que foi armazenado de trás para frente)
    flip(path);
    path.push_back(target);

    return path;
}

//Algoritmo para determinar o custo total de uma entrega do tipo Standard
int Graph::Standard(){
    int cost = 0;
    vector<bool> visited;

    //Inicia o vector de visitados
    for (int i = 0; i < _vertexCount; i++){
        visited.push_back(false);
    }

    visited[0] = true;

    for (int i = 1; i < _vertexCount; i++){
        vector<int> path = this->bellmanFord(0, i);

        for (int j = 0; j < path.size()-1; j++){
            if (!visited[path[j+1]]){
                cost += this->getCost(path[j], path[j+1]);
                visited[path[j+1]] = true;
            }
        }
    }

    return cost;
}

//Algoritmo para determinar o custo total de uma entrega do tipo VIP
int Graph::VIP(int target){
    vector<int> bestPath = this->bellmanFord(0, target);
    int totalCost = 0;
    int nonVisited = _vertexCount - bestPath.size();

    for (int i = 0; i < bestPath.size()-1; i++){
        totalCost += this->getCost(bestPath[i], bestPath[i+1]);
    }

    return totalCost*nonVisited;
}

