#include "graph.hpp"

//Constrói o grafo a partir do tabuleiro do jogo
Graph::Graph(int vertexCount, int edgeCount){
    _vertexCount = vertexCount;
    _edgeCount = edgeCount;
    _graph.resize(_vertexCount);
    // _edges.resize(_edgeCount);

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

//Reseta as cores de todos os vértices. Fundamental para a função do BFS.
void Graph::resetGraph(){
    for(int i = 0; i < _vertexCount; i++) {
        _graph[i]._distance = INT_MAX;
        _graph[i]._predecessor = -1;
    }
}

void flip(vector<int> &v){
    int size = v.size();
    int j = size-1;
    for(int i = 0; i < j; i++) {
        swap(v[i], v[j]);
        j--;
    }
}

vector<int> Graph::bellmanFord(int current, int target){
    _graph[current]._distance = 0;

    // Relaxing:
    for(int i = 0; i < _vertexCount-1; i++) {
        for(int j = 0; j < _edgeCount; j++) {
            int u = _edges[j]._source;
            int v = _edges[j]._destination;
            int w = _edges[j]._cost;
            
            // cout << "u: " << u << ", " << _graph[u]._distance << "|" << " v: " << v << ", " << _graph[v]._distance << endl;
            if(_graph[u]._distance != INT_MAX && _graph[u]._distance + w < _graph[v]._distance){
                _graph[v]._distance = _graph[u]._distance + w;
                _graph[v]._predecessor = u;
                // cout << "Mudou: " << u << "->" << v << endl;
            }
        }
    }

    // Guarda caminho
    vector<int> path;
    int predecessor = _graph[target]._predecessor;
    while (predecessor > -1){
        path.push_back(predecessor);
        predecessor = _graph[predecessor]._predecessor;
    }
    
    flip(path);

    path.push_back(target);

    return path;
}

int Graph::VIP(int target){
    vector<int> bestPath = this->bellmanFord(0, target);
    int totalCost = 0;
    int nonVisited = _vertexCount - bestPath.size();

    for (int i = 0; i < bestPath.size()-1; i++){
        totalCost += this->getCost(bestPath[i], bestPath[i+1]);
    }

    return totalCost*nonVisited;
}

// vector<int> Graph::DFS(int current, vector<int> path, int target){
   
//     _graph[current]._color = 1;

//     for(int i = 0; i < sizeof(_graph[current]._near); i++){
//         int neighbour = _graph[current]._near[i]._next;
//         if(path.end() != target && _graph[neighbour]._color == 0){
//             path.push_back(neighbour);
//             DFS(neighbour, path);
//             path.pop();
//         }
//     }

//     // 0, 1, 3, P, 4, 2
    
// }

//Função de busca em largura
// vector<int> Graph::BreadthFirstSearch(int pacmanPosition, int ghostPosition){
//     int tamPath = 0;
//     int current;
//     bool end = false;
//     position posAux;
//     vector<position> path; //Vetor para guardar todos os vertices percorridos
//     queue<int> nextVertex;

//     //Verifica se o fantasma passou pelo pacman
//     // if(ghostPosition == pacmanPosition) {
//     //     end = true;
//     //     foundByGhost = true;
//     // }

//     //Pinta o vertice atual de cinza
//     _graph[pacmanPosition]._color = 1;

//     //Seta a distancia como 0 (posicao do Pacman)
//     _graph[pacmanPosition]._distance = 0;
    
//     //Insere na fila o vértice atual
//     nextVertex.push(pacmanPosition);

//     // Enquanto não achar o fantasma e enquanto a fila não estiver vazia
//     while(!end && !nextVertex.empty()){
        
//         //Retira um vértice da fila
//         current = nextVertex.front();
//         nextVertex.pop();
        
//         //Pinta o vértice de preto
//         _graph[current]._color = 2;

//         //Verifica cada vizinho do vertice preto
//         for(int i = 0; i < _graph[current]._near.size(); i++){
            
//             // Guarda o numero do vertice do vizinho
//             int neighbor = _graph[current]._near[i]._next;

//             //Se vizinho eh branco
//             if (_graph[neighbor]._color == 0){

//                 //Atualiza a distancia do vizinho que vai ser visitado:
//                 // int neighborPredecessor = _graph[neighbor]._predecessor;
//                 // _graph[neighbor]._distance = _graph[neighborPredecessor]._distance + _graph[neighborPredecessor]._near[i]._cost;
//                 _graph[neighbor]._distance = _graph[current]._distance + _graph[current]._near[i]._cost;

//                 //Insere no vetor de caminhos
//                 path.push_back(_graph[current]._near[i]);
//                 tamPath++;
                
//                 //Pinta o vizinho de cinza
//                 _graph[neighbor]._color = 1;

//                 //Verifica se o Pacman chegou no fantasma
//                 if(neighbor == ghostPosition) {
//                     end = true;
//                     break;
//                 }

//                 //Insere vizinho na fila
//                 nextVertex.push(neighbor);

//             }
//         }

//     }

//     //Melhor caminho
//     vector<int> bestPath;

//     // if(end) {
//     //     // Guarda a menor distancia (a que chegou no fantasma)
//     //     int distance = _graph[ghostPosition]._distance;
//     //     bestPath.resize(distance);

//     //     // Indice para bestPath
//     //     int j = distance - 1;

//     //     //Guarda predecessor do fantasma
//     //     int predecessor = path[tamPath - 1]._predecessor;
        
//     //     //Insere movimento ao chegar no fantasma
//     //     bestPath[j] = path[tamPath - 1]._direction;

//     //     j--;

//     //     //Insere os movimentos para chegar no fantasma (vetor de frente para tras):
//     //     for(int i = tamPath - 2; i >= 0; i--) {
//     //         if(path[i]._next == predecessor) {
//     //             bestPath[j] = path[i]._direction;
//     //             predecessor = path[i]._predecessor;
//     //             j--;
//     //         }
//     //     }
//     // }

//     //Reseta as cores dos vértices para a próxima busca
//     resetGraph();

//     return bestPath;
// }