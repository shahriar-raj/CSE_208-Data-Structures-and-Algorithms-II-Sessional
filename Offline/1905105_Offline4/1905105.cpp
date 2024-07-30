#include <bits/stdc++.h>

using namespace std;

int fact(int);

class Graph{
    int n, edges, vertices;
    vector<vector<int>> adjacen_m;
public:
    Graph(int v, int n);
    void addEdge(int so , int d, int w);
    int n_vertices();
    int n_edges();
    bool Edmonds_Karp(int s, int t);
    bool BFS(int s, int t, int*parent);
};

Graph::Graph(int v,int n){
    vertices = v;
    this->n = n;
    for(int i=0; i<v; i++){
        vector<int> row;
        adjacen_m.push_back(row);
        for(int j=0;j<v; j++){
            adjacen_m[i].push_back(0);
        }
    }
    edges = 0;
}

void Graph::addEdge(int so, int d, int w){
    adjacen_m[so][d] = w;
    edges++;
}

bool Graph::Edmonds_Karp(int s, int t){
    bool result = true;
    int *parent = new int[vertices];
    parent[s] = -1;
    while(BFS(s,t,parent)){
        int flow = 10000;
        for(int j=t; j!=s; j = parent[j])
            flow = min(flow, adjacen_m[parent[j]][j]);
        for(int j=t; j!=s; j = parent[j]){
            adjacen_m[parent[j]][j]-=flow;
            adjacen_m[j][parent[j]]+=flow;
        }
    }

    for(int ab =1; ab <=(((n-1)*(n-2))/2); ab++){
        if(adjacen_m[0][ab]!=0){
            result= false;
            break;
        }
    }

    if(result){
        for(int ab=vertices-n; ab<vertices-1; ab++){
            if(adjacen_m[ab][vertices-1]<0){
                result= false;
                break;
            }
        }
    }

    return result;
}

bool Graph::BFS(int s, int t, int* parent){
    bool* visited = new bool[vertices];
    for (int i = 0; i < vertices; i++)
        visited[i] = false;
    queue<int> q;
    visited[s] = true;
    q.push(s);
    while(!q.empty()){
        int cur = q.front();
        visited[cur] = true;
        q.pop();
        for(int i = 0; i < vertices; i++){
            if(!visited[i]&&adjacen_m[cur][i]>0){
                visited[i] = true;
                parent[i] = cur;
                if(i == t)
                    return true;
                q.push(i);
            }
        }
    }
    return false;
}

void MaxFlow(int n, int**gm, int *w, int *r, char **teams ){
    int inter = ((n-2)*(n-1))/2;
    int v = 2 + n-1 + inter;
    //cout << v << endl;
    for(int i =0; i<n; i++){
        Graph g(v,n);
        int cnt = 1;
        for(int j=0;j<n;j++){
            if(j!=i){
                for(int k=j+1; k<n; k++){
                    if(k!=i){
                        g.addEdge(0,cnt++,gm[j][k]);
                    }
                }
            }
        }
        int l = inter+1;
        int t = l+1;
        for(int j=1; j<=inter; j++){
            g.addEdge(j,l,10000);
            g.addEdge(j,t,10000);
            t++;
            if(t>inter+n-1){
                l++;
                t = l+1;
            }
        }
        int k=0;
        for(int j=v-n; j<v-1; j++){
            if(k==i)
                k++;
            g.addEdge(j,v-1,w[i]+r[i]-w[k]);
            k++;
        }
     bool result = g.Edmonds_Karp(0,v-1);
     if(!result)
        cout << teams[i] << " is eliminated." <<endl;
    }
}

int main(){
    int n,*w, *l, *left, **g;
    char **teams;
    cin >> n;
    teams = new char*[n];
    w = new int[n];
    l = new int[n];
    left = new int[n];
    g = new int*[n];
    for(int i=0; i<n; i++){
        teams[i] = new char[20];
        g[i] = new int[n];
        cin >> teams[i] >> w[i] >> l[i] >> left[i];
        for(int j=0; j<n; j++){
            cin >> g[i][j];
        }
    }
    MaxFlow(n, g, w, left, teams);
    return 0;
}
