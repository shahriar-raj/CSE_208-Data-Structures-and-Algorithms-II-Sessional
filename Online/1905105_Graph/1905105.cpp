#include <iostream>
#include <list>

using namespace std;

class Graph{
    int vertices, edges;
    list<int>* adjacen_l;
    bool* visited;
    int* dis;

public:
    Graph(int v);
    Graph(){};
    void addEdge(int so , int d);
    void addVertices();
    void BFS(int s);
    int n_vertices();
    int n_edges();
    int s_d();
};

Graph::Graph(int v){
    vertices = v;
    edges=0;
    visited = new bool[v];
    adjacen_l = new list<int>[v];
    dis = new int[v];
}

int Graph::s_d(){
    return dis[vertices-1];
}
void Graph::addEdge(int so, int d){
    adjacen_l[so].push_back(d);
    adjacen_l[d].push_back(so);   // This is for undirected graph.
    edges++;
}

void Graph::addVertices(){
    list<int>* adjacen_n = new list<int>[vertices+1];
    for(int i=0; i<vertices;i++){
        adjacen_n[i] = adjacen_l[i];
    }
    bool* n_visited = new bool[vertices+1];
    for(int i=0; i<vertices;i++){
        n_visited[i] = visited[i];
    }
    n_visited[vertices] = false;
    vertices++;
    adjacen_l = adjacen_n;
    visited = n_visited;
}

int Graph::n_vertices(){
    return vertices;
}

int Graph::n_edges(){
    return edges;
}

void Graph::BFS(int s){
    visited = new bool[vertices];
    for (int i = 0; i < vertices; i++)
        visited[i] = false;
    list<int> queue;
    visited[s] = true;
    dis[s] = 0;
    queue.push_back(s);
    list<int>:: iterator i;
    while(!queue.empty()){
        int cur = queue.front();
        visited[cur] = true;
        cout << "Visited " << cur << endl;
        queue.pop_front();

        for(i = adjacen_l[cur].begin(); i != adjacen_l[cur].end(); ++i){
            int adj_V = *i;
            if(!visited[adj_V]){
                visited[adj_V] = true;
                dis[*i] = dis[cur]+1;
                queue.push_back(adj_V);
            }
        }
    }
}

int main(){
    string S;
    cin >> S;
    Graph g1(S.length());
    for(int i=0; S[i]!='\0'; i++){
        if(i!=0)
            g1.addEdge(i,i-1);
        if(i!=S.length()-1)
            g1.addEdge(i,i+1);
        for(int j=0; S[j]!='\0'; j++){
            if((i!=j)&&S[i]==S[j])
                g1.addEdge(i,j);
        }
    }
    g1.BFS(0);
    cout<<g1.s_d()<<endl;
    return 0;
}
