#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
std::vector<std::vector<std::vector<int>>> M;
int BOW( const std::vector<int>& numeros, int black = 0, int white = 0, int i = 0) {
    int indice = i;
    if (i == numeros.size())
        return 0;
    if (i == 0) {
        return min(BOW(numeros,indice,white,i+1),min(BOW(numeros,black,indice,i+1),BOW(numeros,black,white,i+1)+1)); }
    if (M[i][black][white] != -1) {
        return M[i][black][white];
    }
    else {
        if (numeros[black] < numeros[indice]) {
            if ((numeros[indice] >= numeros[white]) && white != 0) {
                M[i][black][white]= min(BOW(numeros,indice,white,i+1),BOW(numeros,black,white,i+1)+1);
                return  M[i][black][white];}
            else {
                M[i][black][white] = min(BOW(numeros,indice,white,i+1),min(BOW(numeros,black,indice,i+1),BOW(numeros,black,white,i+1)+1));
                return M[i][black][white];}}
        else { 
            if ((numeros[indice] < numeros[white])||white == 0) {
                M[i][black][white] = min(BOW(numeros,black,indice,i+1),BOW(numeros,black,white,i+1)+1);
                return M[i][black][white];}
            else {
                M[i][black][white] = BOW(numeros,black,white,i+1)+1;
                return M[i][black][white];}}
}}
         
         
int main() {
    int n;
    while (cin >> n && n != -1) {
        vector<int> numeros(n+1);
        numeros[0] = 0;
        for (int i = 0; i < n; ++i) {
            cin >> numeros[i+1];
        }
        int maximo = *std::max_element(numeros.begin(), numeros.end());
        M.assign(n+1, std::vector<std::vector<int>>(n+1, std::vector<int>(n+1, -1))) ;

        int resultado = BOW(numeros);
        cout << resultado << endl;
    }
    return 0;
}
     