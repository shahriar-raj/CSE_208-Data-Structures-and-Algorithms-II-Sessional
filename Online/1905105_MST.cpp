 #include< bits/stdc++.h>

 using namespace std;

class Graph{
    int vertices, edges;
    list<int>* adjacen_l;
    bool* visited;
    int roads = 0;

public:
    Graph(int v);
    Graph(){};
    void addEdge(int so , int d);
    void addVertices();
    void BFS(int s);
    int n_vertices();
    int n_edges();
};

Graph::Graph(int v){
    vertices = v;
    edges=0;
    visited = new bool[v];
    adjacen_l = new list<int>[v];
}

void Graph::addEdge(int so, int d){
    adjacen_l[so].push_back(d);
    adjacen_l[d].push_back(so);   // This is for undirected graph.
    edges++;
}

int Graph::n_vertices(){
    return vertices;
}

int Graph::n_edges(){
    return edges;
}

int Graph::BFS(int s){
    visited = new bool[vertices];
    for (int i = 0; i < vertices; i++)
        visited[i] = false;
    list<int> queue;
    visited[s] = true;
    roads ++ ;
    queue.push_back(s);
    list<int>:: iterator i;
    while(!queue.empty()){
        int cur = queue.front();
        visited[cur] = true;
        //cout << "Visited " << cur << endl;
        queue.pop_front();

        for(i = adjacen_l[cur].begin(); i != adjacen_l[cur].end(); ++i){
            int adj_V = *i;
            if(!visited[adj_V]){
                visited[adj_V] = true;
                roads++;
                queue.push_back(adj_V);
            }
        }
    }
    return roads;
}

int main()
{
    int m,n;
    Graph g_m(n),g_w(n);
    for(int i=0; i<m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        if(c == 1 || c == 3 ){
            g_m.addEdge(a,b);
        }
        if(c == 2 || c == 3 ){
            g_w.addEdge(a,b);
        }
    }

    return 0;
}
