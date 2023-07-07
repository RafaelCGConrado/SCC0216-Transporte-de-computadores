#include <iostream>
#include <vector>
#include "graph.hpp"


int main(){
    int m, n;
    int a, b, w;
    int target;

    cin >> m >> n;

    Graph graph = Graph(m, n);

    for(int i = 0; i < n; i++){
        cin >> a;
        cin >> b;
        cin >> w;
        
        graph.addEdge(a, b, w);
    }
    // graph.printGraph();

    cin >> target;

    vector<int> bestPath = graph.bellmanFord(0, target);

    for (int i = 0; i < bestPath.size(); i++){
        cout << bestPath[i] << " ";
    }
    cout << endl;

    int cost = graph.VIP(target);

    cout << "Custo do caminho VIP: " << cost << endl;

    cost = graph.Standard();

    cout << "Custo do caminho Padrão: " << cost << endl;

    // graph.printGraph();

    
// 6 7
// 0 1 1
// 0 2 2
// 0 3 3
// 1 4 3
// 2 4 2
// 3 4 3
// 4 5 4
// 5


}