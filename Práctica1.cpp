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
        return t2;
    if (suma2 > suma1)
        return t1;
    else 
        if (billetes1 >= billetes2)
            return t2;
        else 
            return t1;

}
std::tuple<int, int> CC(std::vector<int>& B, int c) {
    int ultimo = B.back();
    if (c <= 0)
        return std::make_tuple(0, 0);
    if (B.empty())
        return std::make_tuple(INF,INF);
    else {
        std::vector<int> B_copy = B;
         B_copy.pop_back();
        return min_prioridades(sumTuples(CC(B_copy,c-ultimo), make_tuple(ultimo, 1)), CC(B_copy,c)); 
    }
}


int main() {
    vector<int> B = {2, 3, 5, 10, 20, 20};
    int c = 14;
    
    // Imprimir el resultado
    auto result = CC(B, c);
    cout << "La mínima suma es: " << get<0>(result) << endl;
    cout << "Número de billetes: " << get<1>(result) << endl;

    return 0;
}


//   if (suma1 > suma2)
  //      return t1;
   // if (suma1 < suma2)
     //   return t2;
   // return (billetes1 <= billetes2) ? t1 : t2;
    
