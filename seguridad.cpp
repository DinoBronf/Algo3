#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <queue>
#include <unordered_map>
#include <utility>
#include <stack>
#include <deque>
#include <list>
#include <array>
using namespace std;
int INF = 1e9;

void dijkstra(vector<int>& distancias, const vector<vector<pair<int,int>>>& grafo, int fuente){
    distancias[fuente] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Cola;
    Cola.push({0,fuente});
    while (!Cola.empty()){
        int distancia = Cola.top().first;
        int nodo = Cola.top().second;
        Cola.pop();
        if (distancia <= distancias[nodo]){
            distancias[nodo] = distancia;
            for (const pair<int,int>& vecino : grafo[nodo]){
                int distanciavecino = vecino.second;
                int nodovecino = vecino.first;
                int nuevadistancia = distancia + distanciavecino;
                if (nuevadistancia < distancias[nodovecino]){
                    distancias[nodovecino] = nuevadistancia;
                    Cola.push({nuevadistancia, nodovecino});
                }
            }
        }
    } 



}


int seguridad(const vector<int>& distancias1, const vector<int>& distancias2, const vector<tuple<int,int,int>>& aristas, int distParametro){
    int longitud = 0;
    for (int i = 0; i<aristas.size(); i++){
        int nodo1 = get<0>(aristas[i]);
        int nodo2 = get<1>(aristas[i]);
        int peso = get<2>(aristas[i]);
        if (distancias1[nodo1] + peso + distancias2[nodo2] == distParametro){
            longitud += peso;
        }
        if (distancias1[nodo2] + peso + distancias2[nodo1] == distParametro){
            longitud += peso;
        }
    }
    return longitud*2;
}



int main(){
    int vertices;
    int cantaristas;
    cin >> vertices >> cantaristas;
    vector<vector<pair<int,int>>> grafo(vertices);
    vector<tuple<int,int,int>> aristas;
    for (int i = 0; i < cantaristas; i++) {
        int u, v,peso;
        cin >> u >> v >> peso;
        grafo[u].push_back(std::make_pair(v ,peso));
        grafo[v].push_back(std::make_pair(u , peso));
        aristas.push_back(std:: make_tuple(u,v,peso));}
    vector<int> distancias1(vertices,INF);
    vector<int> distancias2(vertices,INF);
    dijkstra(distancias1,grafo,0);
    dijkstra(distancias2, grafo, vertices-1);
    int resultado = seguridad(distancias1,distancias2,aristas,distancias1[vertices-1]);
    cout << resultado << endl;
    return 0;

}