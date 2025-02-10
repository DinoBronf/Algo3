#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

vector<long long int> generadorDeNiveles(vector<vector<long long int>> l){
    vector<long long int> nivel(l.size(),-1);
    queue<tuple<long long int,long long int>> cola;
    nivel[0] = 0;
    cola.push(std::make_tuple(0, 0));
    while (!cola.empty()){
       tuple<long long int,long long int> nodo = cola.front();
       cola.pop();
       for (long long int vecino : l[std::get<0>(nodo)]){
            if (nivel[vecino] == -1 || nivel[vecino] > std::get<1>(nodo)+1){
                nivel[vecino] = std::get<1>(nodo)+1;
                cola.push(std::make_tuple(vecino, nivel[vecino]));}}}
    return nivel;
}

int main(){
    long long int n;
    cin >> n;
    vector<vector<long long int>> l(n);
    //construyo l
    if (n == 1){
        long long int v;
        cin >> v;
        cout << 0 << endl;
        return 0;
    }
    for (long long int i = 0; i < n ; i++) {
        long long int v;
        cin >> v;
        l[i].push_back(v - 1);
        if (i + 1 < n) {
            l[i].push_back(i + 1); 
        }
        if (i-1 > 0){
            l[i].push_back(i-1);
        }}
        
    vector<long long int> niveles = generadorDeNiveles(l);
     for (long long int i = 0; i < niveles.size(); i++) {
        cout << niveles[i] << " ";
    }
    cout << endl;
    return 0;
}


