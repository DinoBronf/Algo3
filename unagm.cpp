
//fija las estructuras del dfs directo con 1e5.
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
class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n, 0);
        parent.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
 
    int find(int node){
 
        // En caso que nodo sea el representante
        if (node == parent[node]) return node;
 
        // Hago path compression
        return parent[node] = find(parent[node]);
    }
 
    void unite(int u, int v) {
        int uRepresentative = find(u);
        int vRepresentative = find(v);
 
        // Si tienen el mismo representante, entonces pertenece al
        // mismo conjunto
        if (uRepresentative == vRepresentative) return;
 
        // Actualizamos el representante segun el caso del rank
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};
 
 
int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;
vector<int> estado(1e5,NO_LO_VI);
vector<int> memo(1e5,-1);
vector<pair<int,int>> padre(1e5,std::make_pair(-1,-1));
vector<vector<pair<int,int>>> tree_edges(1e5);
vector<int> back_edges_con_extremo_inferior_en(1e5,0);
vector<int> back_edges_con_extremo_superior_en(1e5,0);
vector<int> lugar(1e5,-1);
vector<bool> nodosvisitados(1e5,false);
int vengode;
vector<string> estan;
queue<pair<int,int>> ausar;
vector<int> aborrar;
unordered_map<int,list<pair<int,int>>> grafoGP;
int nuevitos;
void dfs(pair<int,int> v, int p , DisjointSet& dsu, const unordered_map<int,list<pair<int,int>>>& ady, vector<bool>& visitados, int& nuevos ) {
    estado[v.first] = EMPECE_A_VER;
    
    lugar[v.first]=v.second;
    if (nodosvisitados[v.first] == false){
        nodosvisitados[v.first] = true;
        nuevitos ++;
        }
    if (visitados[v.first] == false){
                nuevos ++;
                visitados[v.first] = true;
                
            }
     for (const std::pair<int, int>& u_pair : ady.at(v.first)) { 
        int u = u_pair.first;
          if (nodosvisitados[u] == false){
            nodosvisitados[u] = true;
            nuevitos ++;
            }
        
        if (visitados[u] == false){
            visitados[u] = true;
            nuevos++;
        }
        if (dsu.find(v.first) != dsu.find(u)){
            dsu.unite(v.first,u);
        }
        if (estado[u] == NO_LO_VI) {
            
            tree_edges[v.first].emplace_back(u, u_pair.second);
            padre[u]=v;
            vengode = v.first;
           
            dfs(u_pair, v.first, dsu, ady, visitados,nuevos);
            
        }
        
        else if (u_pair.second != v.second && (vengode != u || vengode < v.first)) {
            estan[u_pair.second] = "at least one";
            
            
            if (estado[u] == EMPECE_A_VER) {
                back_edges_con_extremo_superior_en[v.first]++;
                vengode= v.first;
             
                 if (visitados[u] == false){
                    
                    visitados[u] = true;}
            }
            else 
                back_edges_con_extremo_inferior_en[v.first]++;
                
                
        }
        vengode = v.first;
    }
    estado[v.first] = TERMINE_DE_VER;
}
 
int cubren(int v, int p=-1){
    int res=0;
    if (memo[v] != -1) 
        return memo[v];
    for (const pair<int,int>& par : tree_edges[v]) {
        int hijo =  par.first;
        
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    }
    res = res + back_edges_con_extremo_superior_en[v] - back_edges_con_extremo_inferior_en[v];
   
    memo[v] = res;
    return res;}
 
std::pair<int,int> cubrenpos(const int& v, int p=-1) {
    int res = 0;
    int posicion = lugar[v];
    res = cubren(v);
    return (std::make_pair(res,posicion));
}
 
 
 
bool comp(const tuple<int, int, int,  int>& t1, const tuple<int, int,  int,  int>& t2) {
    return std::get<2>(t1) < std::get<2>(t2);  
}
 
vector<string> kruskal(vector<tuple< int,  int,  int, int>>& orden, const int& vertices) {
    int yavisitados = 0;
    vector<bool> visite(vertices, false);
    std::sort(orden.begin(), orden.end(), comp);
    DisjointSet dsu(vertices);
    int i = 0;
    //primeros bloques andan bien.
    //lo más optimizados posible?
    while (yavisitados < vertices) {
        if (i +1 == orden.size()){
            estan[std::get<3>(orden[i])] = "any";
            yavisitados += 2;
        }
        else if (std::get<2>(orden[i]) != std::get<2>(orden[i+1])){
                int vertice1 = std::get<0>(orden[i]);
                int vertice2 = std::get<1>(orden[i]);
                if (dsu.find(vertice1) != dsu.find(vertice2)){
                    dsu.unite(vertice1,vertice2);
                    if (visite[vertice1] == false){
                        yavisitados++;
                        visite[vertice1] = true;
                        }
                    if (visite[vertice2] == false){
                        yavisitados++;
                        visite[vertice2] = true;}
                    estan[std::get<3>(orden[i])] = "any";
                }
                i ++;
            
            }
        else{
            
            // creo el grafo GP
            
            int vert1 = std::get<0>(orden[i]);
            int vert2 = std::get<1>(orden[i]);
            int lugar1 = std::get<3>(orden[i]);
            int identificador1 = dsu.find(vert1);
            int identificador2 = dsu.find(vert2);
            if (identificador1 != identificador2){
                grafoGP[identificador1].emplace_back(identificador2, lugar1);
                grafoGP[identificador2].emplace_back(identificador1, lugar1);
                ausar.push(std::make_pair(identificador1,lugar1));
                
                aborrar.push_back(identificador1);}
           
           
            while ( std::get<2>(orden[i]) == std::get<2>(orden[i + 1])){
                int v1 = std::get<0>(orden[i+1]);
                int v2 = std::get<1>(orden[i+1]);
                int lugar = std::get<3>(orden[i+1]);
                int id1 = dsu.find(v1);
                int id2 = dsu.find(v2);
                if (dsu.find(v1) != dsu.find(v2)){
                    grafoGP[id1].emplace_back(id2, lugar);
                    grafoGP[id2].emplace_back(id1, lugar);
                    ausar.push(std::make_pair(id1,lugar));
                    
                    aborrar.push_back(id1);
                    aborrar.push_back(id2);}
                
                i++;}
            
            
            i++;
            int nuevos = 0;
            nuevitos = 0;
           while(!ausar.empty()){
                if (nodosvisitados[ausar.front().first] == false){
                    //no estoy seguro de que haga falta. me parece que sí porque lo tengo que hacer cada vez que corro el dfs asi la raíz no es tomada en cuenta.
                    int hijodirecto = grafoGP[dsu.find(ausar.front().first)].front().first;
                    grafoGP[hijodirecto].pop_front();
                    dfs(ausar.front(), -1, dsu, grafoGP,visite,nuevos);
                    }
                ausar.pop();
            }
            
           
            //tengo que optimizar esto
            int n = 0;
            while (n < vertices && nuevitos > 0) {
                n = std::find_if(nodosvisitados.begin() + n, nodosvisitados.end(), [](bool v) { return v; }) - nodosvisitados.begin();
                if (n >= vertices) break;

                pair<int, int> devuelve = cubrenpos(n);

                if (devuelve.first == 0) {
                    estan[devuelve.second] = "any";
                } else {
                    estan[devuelve.second] = "at least one";
                }

                nodosvisitados[n] = false;
                nuevitos--;
                n++;  
            }

            for(int b = 0; b < aborrar.size(); b++){
                int nodo = aborrar[b];
                int identificador = dsu.find(nodo);
                grafoGP[nodo].clear();
                lugar[nodo] = -1;
                estado[identificador] = NO_LO_VI;
                back_edges_con_extremo_inferior_en[nodo] = 0;
                back_edges_con_extremo_inferior_en[identificador] = 0;
                back_edges_con_extremo_superior_en[nodo] = 0;
                back_edges_con_extremo_superior_en[identificador] = 0;
                memo[nodo] = -1;
                memo[identificador] = -1;
                tree_edges[identificador].clear(); 
                padre[identificador] = std::make_pair(-1,-1);
                
            }
            aborrar.clear();
            yavisitados += nuevos;
            
            }
    }
    for ( int quedan = i; quedan < orden.size(); quedan++){
        int nodo1 = std::get<0>(orden[quedan]);
        int nodo2 = std::get<1>(orden[quedan]);
        if (dsu.find(nodo1)!= dsu.find(nodo2)){
            estan[std::get<3>(orden[quedan])] = "any";
            dsu.unite(nodo1, nodo2);}
    }
    return estan;
            }
 
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int vertices, aristas1; 
    cin >> vertices >> aristas1;
    vector<tuple< int,  int,  int,  int>> aristas(aristas1);
    
    for ( int i = 0; i < aristas1; i++) {
        int v1, v2, peso;
        cin >> v1 >> v2 >> peso;
        if (v1 < v2) {
            aristas[i] = make_tuple(v1 - 1, v2 - 1, peso, i);
        } else {
            aristas[i] = make_tuple(v2 - 1, v1 - 1, peso, i);
        }
    }
    estan.assign(aristas.size(), "none");
    vector<string> resultado = kruskal(aristas, vertices);
    for( int i = 0; i < aristas.size(); i++) {
        cout << resultado[i] << endl;}
   return 0;
 }



