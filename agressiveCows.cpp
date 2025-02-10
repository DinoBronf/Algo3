#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
int INF = 1e9;
bool entranVacas(vector<int> establos, int distancia, int vacas){
    int vacasUbicar = vacas;
    int i = 0;
    for (int j = 0; j < establos.size(); ++j){
        if (establos[j] - establos[i] >= distancia){
            vacasUbicar--;
            if (vacasUbicar == 1){
                return true;}
            i=j;}
                }
        return false;
            }
int agressiveCows(vector<int> establos, int vacas, int cantEstablos){
    sort(establos.begin(), establos.end());
    int minimo = 1;
    int maximo = establos[establos.size()-1]-establos[0];
    vector<int> distancias_probadas;
    int i = 0;
    int distancia_valida_max = 0;
    while(maximo >= minimo){
        int distanciaMax = (maximo+minimo)/2;
        if (entranVacas(establos,distanciaMax,vacas)){
            distancias_probadas.push_back(distanciaMax);
            minimo = distanciaMax+1;
            if(std::find(distancias_probadas.begin(), distancias_probadas.end(), (maximo+minimo)/2)!=distancias_probadas.end()){
                if (entranVacas(establos,(maximo+minimo)/2,vacas))
                    return (maximo+minimo)/2;}}
        else {
            distancias_probadas.push_back(distanciaMax);
            maximo = distanciaMax -1;
            if(std::find(distancias_probadas.begin(), distancias_probadas.end(), (maximo+minimo)/2)!=distancias_probadas.end()){
                    return (maximo+minimo)/2;}}
        
}}

    

int main(){
    int T;
    cin >> T;
    while(T>0) {
    int N;
    cin >> N;
    int vacas;
    cin >> vacas;
    vector<int> establos(N);
    for (int i = 0; i < N; ++i) {
        cin >> establos[i];
         }
    int resultado = agressiveCows(establos,vacas,N);
    cout << resultado << endl;
    T -= 1;}
    return 0;
}
    
   