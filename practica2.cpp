#include <iostream>
#include <vector>
using namespace std;

// Función merge modificada para contar las inversiones
pair<vector<int>, int> merge(const pair<vector<int>, int> &A, const pair<vector<int>, int> &B) {
    vector<int> res;
    int i = 0, j = 0;
    int swaps = A.second + B.second;  // Sumar los swaps de los subarreglos
    int x = A.first.size(), y = B.first.size();
    
    while (i < x && j < y) {
        if (A.first[i] <= B.first[j]) {
            res.push_back(A.first[i++]);
        } else {
            res.push_back(B.first[j++]);
            // Incrementar el contador de swaps por los elementos restantes en A
            swaps += (x-i);  // Todos los elementos restantes en A[first] > B[j]
        }
    }

    // Agregar los elementos restantes de A y B
    while (i < x) res.push_back(A.first[i++]);
    while (j < y) res.push_back(B.first[j++]);

    return {res, swaps};
}

// Función de ordenación y conteo de desorden (inversiones), con acumulación de swaps
pair<vector<int>, int> desordenSort(const vector<int> &A, int x) {
    if (A.size() <= 1) {
        return {A, x};  // Caso base: un solo elemento no tiene swaps
    }

    int medio = A.size() / 2;

    // Crear los subarreglos izquierda y derecha
    vector<int> izquierda(A.begin(), A.begin() + medio);
    vector<int> derecha(A.begin() + medio, A.end());

    // Llamadas recursivas para las mitades izquierda y derecha
    pair<vector<int>, int> izq = desordenSort(izquierda, x);
    pair<vector<int>, int> der = desordenSort(derecha, x);

    // Unir las dos mitades y contar las inversiones
    pair<vector<int>, int> cant = merge(izq, der);

    // Retornar el arreglo ordenado y la cantidad de swaps acumulados
    return {cant.first, cant.second};
}

int main() {
    vector<int> A = {7, 5, 3, 1};  // Ejemplo de arreglo

    // Llamada inicial a desordenSort, con 0 swaps acumulados al inicio
    pair<vector<int>, int> resultado = desordenSort(A, 0);
    cout << "Cantidad de parejas en desorden: " << resultado.second << endl;

    return 0;
}
