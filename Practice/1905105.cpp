#include <iostream>

using namespace std;

vector<vector<int>> adjacency_list;
int n_1;

vector<bool> visited;

void dfs(int v) {
    visited[v] = true;
    for (int u : adjacency_list[v]) {
        if (!visited[u])
            dfs(u);
    }
}

int main(){
    int n, s, f1, f2;
    cin >> n ;
    cin >> s;
    int **p = new int*[n];
    int **q = new int*[n];
    for(int i=0; i<n; i++){
        p[i] = new int[n];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            p[i][j]=0;
        }
    }

    for(int i=0; i<s; i++){
        cin >> f1 >> f2;
        p[f1-1][f2-1] = 1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if( p[i][j]=1 ){
                q[j][i] = 1;
            }
        }
    }

    return 0;
}
