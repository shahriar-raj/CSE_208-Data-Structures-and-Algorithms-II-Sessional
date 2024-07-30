#include <bits/stdc++.h>

using namespace std;

class Graph{
    int edges, vertices;
    vector<vector<int>> adjacen_m;
public:
    Graph(int v);
    void addEdge(int so , int d, int w);
    int n_vertices();
    int n_edges();
    bool Edmonds_Karp(int s, int t);
    bool BFS(int s, int t, int*parent);
};

Graph::Graph(int v){
    vertices = v;
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
    for(int i=7; i<vertices-1; i++){
        if(adjacen_m[i][vertices-1]!=0){
            result = false;
            break;
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

int main(){
    int t;
    cin >> t;
    for(int k=0; k<t; k++){
        int n,m;
        cin >> n >> m;
        int v = 8 + m;
        Graph g(v);
        for(int i=0; i<6; i++)
            g.addEdge(0,i+1,n);
        string s1,s2;
        for(int i=1; i<=m; i++){
            cin >> s1 >> s2;
            if(s1 == "XXL")
                g.addEdge(1,6+i,10000);
            else if(s1 == "XL")
                g.addEdge(2,6+i,10000);
            else if(s1 == "L")
                g.addEdge(3,6+i,10000);
            else if(s1 == "M")
                g.addEdge(4,6+i,10000);
            else if(s1 == "S")
                g.addEdge(5,6+i,10000);
            else if(s1 == "XS")
                g.addEdge(6,6+i,10000);
            if(s2 == "XXL")
                g.addEdge(1,6+i,10000);
            else if(s2 == "XL")
                g.addEdge(2,6+i,10000);
            else if(s2 == "L")
                g.addEdge(3,6+i,10000);
            else if(s2 == "M")
                g.addEdge(4,6+i,10000);
            else if(s2 == "S")
                g.addEdge(5,6+i,10000);
            else if(s2 == "XS")
                g.addEdge(6,6+i,10000);
        }
        for(int i=7;i<v-1;i++)
            g.addEdge(i,v-1,1);

        cout << "CASE "<<k+1<<":";
        if(g.Edmonds_Karp(0,v-1))
            cout << "YES" <<endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
