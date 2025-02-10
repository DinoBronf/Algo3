#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

vector<vector<int>> red;
vector<vector<int>> capacidad;
vector<vector<int>> mFinal;
int bfs(int s, int t, vector<int>& parent, vector<vector<int>>& capacidad, vector<vector<int>>& red) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : red[cur]) {
            if (parent[next] == -1 && capacidad[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacidad[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, vector<vector<int>>& capacidad, vector<vector<int>>& red, int n) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, capacidad, red)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacidad[prev][cur] -= new_flow;
            capacidad[cur][prev] += new_flow;
            cur = prev;
        
        }
    }

    return flow;
}

int main() {
    int aulas;
    int paresdeaulas;
    cin >> aulas;
    cin >> paresdeaulas;

    vector<int> actual(aulas);
    vector<int> cupo(aulas);
    int alumnos = 0;

    for (int i = 0; i < aulas; i++) {
        int ai;
        cin >> ai;
        actual[i] = ai;
        alumnos += ai;
    }
    int cupos = 0;
    for (int j = 0; j < aulas; j++) {
        int bi;
        cin >> bi;
        cupo[j] = bi;
        cupos += bi;
    }

    int nodos = 2*aulas + 2; 
    

    vector<vector<int>> red(nodos,vector<int>());
    vector<vector<int>> capacidad(nodos,vector<int>(nodos,0));
   // pongo consigo mismo y con fuente.
    for (int i = 1; i <= aulas; i++) {
        capacidad[0][i] = actual[i-1];
        red[0].push_back(i);
        red[i].push_back(0);
        red[i].push_back(aulas+i);
        red[aulas +i].push_back(i);
        capacidad[i][aulas + i] = cupo[i-1];
    }
    //pongo red de paso de alumnos.
    for (int i = 0; i < paresdeaulas; i++) {
        int aula1; 
        int aula2;
        cin >> aula1 >> aula2;
        int peso1 = cupo[aula2-1];
        int peso2 = cupo[aula1-1];
        capacidad[aula1][aulas + aula2] = peso1;
        capacidad[aula2][aulas + aula1] = peso2;
        red[aula1].push_back(aulas + aula2);
        red[aula2].push_back(aulas + aula1);
        red[aulas + aula2].push_back(aula1);
        red[aulas + aula1].push_back(aula2);
    }
    //pongo con el sumidero.
    for (int i = 1; i <= aulas; i++) {
        capacidad[aulas + i][nodos - 1] = cupo[i-1];
        red[aulas + i].push_back(nodos - 1); 
        red[nodos-1].push_back(aulas +i);
    }

    vector<vector<int>> matrizOriginal = capacidad;
    
    int flujo_maximo = maxflow(0, nodos - 1, capacidad,red,nodos);
   
    if (flujo_maximo == alumnos && flujo_maximo == cupos){
        cout << "YES" << endl;
        for (int i = 1; i < aulas+1; i++){
            for (int j = 1; j < aulas+1; j++){
                cout << matrizOriginal[i][aulas + j] - capacidad[i][aulas+j] << " ";
            }
            cout << endl;
        }
    }
    else {
        cout << "NO" << endl;
    }
    


    return 0;
}