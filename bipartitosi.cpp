#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
using namespace std;



//paso 1, separo en 2 grupos el grafo bipartito.
void separo(vector<vector<long long int>>& B,vector<long long int>& grupo1,vector<long long int>& grupo2, vector<bool>& visitados, int nodo, int grupo){
    visitados[nodo] = true;
        if (grupo == 1){
                grupo2.push_back(nodo);
                grupo = 2;
            }
        else {
                grupo1.push_back(nodo);
                grupo = 1;
            }
        for (long long int j= 0; j< B[nodo].size(); j++){
            if (visitados[B[nodo][j]] == false)
                separo(B,grupo1,grupo2,visitados,B[nodo][j], grupo);
        }
        
}

//paso 2, agrego todas las aristas que pueda. 
int main(){
    long long int n;
    cin >> n;
    if (n == 1){
        cout << 0 << endl;
        return 0;}
    vector<vector<long long int>> B(n);
    for (long long int i = 0; i < n - 1; i++) {
        long long int u, v;
        cin >> u >> v;
        B[u - 1].push_back(v - 1);
        B[v - 1].push_back(u - 1);}
    if (n <= 3){
        cout << 0 << endl;
        return 0;}
    vector<long long int> grupo1;
    vector<long long int> grupo2;
    vector<bool> visitados(B.size(), false);
    int nodo = 0;
    separo(B,grupo1,grupo2, visitados, nodo, 2);
    long long int aristas = (grupo1.size()*grupo2.size());
    cout << (aristas-(n-1)) << endl;
    return 0;
}