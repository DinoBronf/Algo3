#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <utility>
using namespace std;
int INF = 1e9;

//con la misma estructura que en el PPT de todos a todos, slide 15.
vector<long long int> floyd(long long int esquinas, const vector<long long int>& orden, vector<vector<long long int>>& matriz){

            vector<long long int> sumas(esquinas,0);
            vector<long long int> visitados;
            vector<vector<long long int>> nuevaM(esquinas+1, vector<long long int>(esquinas+1,INF));
            
            //voy agregando de a poco.
            for (long long int i = 1; i <= esquinas; i++){
                long long int nodoaMirar = orden[esquinas-i];
                visitados.push_back(nodoaMirar);
                nuevaM[nodoaMirar][nodoaMirar] = 0;
                for (long long int s = 0; s <= esquinas; s++){
                    if (nuevaM[s][nodoaMirar] > matriz[s][nodoaMirar]){
                        nuevaM[s][nodoaMirar] = matriz[s][nodoaMirar];}
                    else {
                        matriz[s][nodoaMirar] = nuevaM[s][nodoaMirar];}
                    
                    if (nuevaM[nodoaMirar][s] > matriz[nodoaMirar][s]){
                        nuevaM[nodoaMirar][s] = matriz[nodoaMirar][s];}
                    else {
                        matriz[nodoaMirar][s] = nuevaM[nodoaMirar][s];}}
                for (long long int l = 0; l < esquinas; l++) {
                        for (long long int j = 0; j < esquinas; j++) {
                                if (nuevaM[l][j] > (nuevaM[l][nodoaMirar] + nuevaM[nodoaMirar][j])){
                                    nuevaM[l][j] = nuevaM[l][nodoaMirar] + nuevaM[nodoaMirar][j];
                                }}
                            }

                for (long long int m : visitados){
                    for (long long int q : visitados){
                        if (nuevaM[m][q] < INF){
                            sumas[esquinas-i] += nuevaM[m][q];}}
                } }
            return sumas;

}


int main(){
    long long int esquinas;
    cin >> esquinas;
    vector<vector<long long int>> grafo(esquinas+1, vector<long long int>(esquinas+1));
    for (long long int i = 0; i < esquinas; i++){
        for (long long int j = 0; j < esquinas; j++){
            long long int a;
            cin >> a;
            grafo[i][j] = a;
        }
    }
    vector<long long int> orden;
    for (long long int i = 0; i < esquinas; i ++){
        long long int nodo;
        cin >> nodo;
        orden.push_back(nodo-1);
    }
    vector<long long int> resultado = floyd(esquinas, orden, grafo);
    for (long long int i = 0; i < esquinas; i ++){
        cout << resultado[i] << endl;
    }

    return 0;
}