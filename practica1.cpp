#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>


using namespace std;
int INF = 1e9;
int suma = 0, billetes = 0;  // producto de costo c
 //vector<int> B;  // B es el conjunto

#include <tuple>

// Función para sumar dos tuplas
std::tuple<int, int> sumTuples(const std::tuple<int, int>& t1, const std::tuple<int, int>& t2) {
    return std::make_tuple(
        std::get<0>(t1) + std::get<0>(t2),  // Suma del primer elemento
        std::get<1>(t1) + std::get<1>(t2)   // Suma del segundo elemento
    );
}

std::tuple<int, int> min_prioridades(const std::tuple<int, int>& t1, const std::tuple<int, int>& t2) {
    int suma1 = std::get<0>(t1);
    int suma2 = std::get<0>(t2);
    int billetes1 = std::get<1>(t1);
    int billetes2 = std::get<1>(t2);
    if (suma1 > suma2)
        return t1;
    if (suma2 < suma1)
        return t2;
    else 
        if (billetes1 >= billetes2)
            return t2;
        else 
            return t1;

}
std::tuple<int, int> CC(std::vector<int>& B, int c) {
    int ultimo = B.back();
    if (c <= 0)
        return std::make_tuple(suma, billetes);
    if (B.empty())
        return std::make_tuple(INF,INF);
    else {
        B.pop_back();
        return min_prioridades(sumTuples(CC(B,c-ultimo), make_tuple(ultimo, 1)), CC(B,c)); 
    }
}


//ejercicio 8
vector<int> C;
std::vector<std::vector<int>> M;
int madera(int i, int j){
    if (i > j)
        return INF;
    if (i == j)
        return 0;
    if (M[i][j] != -1) 
        return M[i][j];
    else {
        M[i][j] = INF;
        for (int n= 0; n < C.size();++n){
            if (C[n] > i && C[n] < j) {
                  int resultado = j - i + madera(i,C[n]) + madera(C[n],j);
                if (resultado < M[i][j]) 
                    M[i][j] = resultado;}}}
    return M[i][j];

}


int main() {
    // Inicializar el vector de posiciones de cortes y la vara
    C = {2, 4, 7}; // Posiciones de los cortes
    int length = 10; // Longitud de la vara de madera

    // Inicializar la matriz de memoización
    M.assign(length + 1, vector<int>(length + 1, -1));

    
    // Imprimir el resultado
    cout << "Costo mínimo para cortar una vara de " << length << " metros con cortes en las posiciones ";
    for (int i = 0; i < C.size(); ++i) {
        cout << C[i] << (i < C.size() - 1 ? ", " : "");
    }
    int resultado = madera(0,length);
    cout << " es: " << resultado << endl;

    return 0;}