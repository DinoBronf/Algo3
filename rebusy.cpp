#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
int INF = 1e9;
int VB( vector< tuple<int, int>> acts, int desde_siguiente_act = 0, int hasta_actual_actividad = INF){
    int original_desde = desde_siguiente_act;
    int desde_provisorio = desde_siguiente_act;
    for (int i = 0; i < acts.size(); ++i) {
        if (std::get<0>(acts[i]) != std::get<1>(acts[i])){
            if (std::get<0>(acts[i]) >= desde_siguiente_act){
                if (std::get<1>(acts[i]) <= hasta_actual_actividad){
                    hasta_actual_actividad = std::get<1>(acts[i]);
                    desde_provisorio = std::get<1>(acts[i]); }}}}
    desde_siguiente_act = desde_provisorio;
    if (original_desde == desde_siguiente_act)
        return 0;
    return VB(acts,desde_siguiente_act, INF) + 1;
}
int main(){
    int T;
    cin >> T;
    while(T>0) {
    int N;
    cin >> N;
    vector<tuple<int, int>> acts(N);
    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b; 
        acts[i] = make_tuple(a, b); 
         }
    int resultado = VB(acts);
    cout << resultado << endl;
    T -= 1;
    } 
    return 0;
}