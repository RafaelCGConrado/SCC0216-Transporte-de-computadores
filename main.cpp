#include <iostream>
#include <vector>
#include "graph.hpp"

/*
    Trabalho 4 de Modelagem Computacional em Grafos
    Alunos:
        João Pedro Buzzo Silva
        Rafael Comitre Garcia Conrado
        Victor Hugo Trigolo Amaral
*/

int main(){
    int m, n;
    int a, b, w;
    int target;

    cin >> m >> n;

    Graph graph = Graph(m, n);

    //Leitura dos vértices, arestas e seus respectivos pesos
    for(int i = 0; i < n; i++){
        cin >> a;
        cin >> b;
        cin >> w;
        
        graph.addEdge(a, b, w);
    }

    cin >> target;

    //Calcula o custo para a entrega VIP
    int costVip = graph.VIP(target);

    //Calcula o custo para a entrega padrão
    int costStd = graph.Standard();

    if(costVip == costStd){
        cout << "NDA" << endl << costVip << endl;
    }

    else if(costVip < costStd){
        cout << "VIP" << endl << costVip << endl;
    }

    else{
        cout << "PADRAO" << endl <<costStd << endl;
    }


}
