#include <bits/stdc++.h>

using namespace std;

class Edges{
    double we;
    int st, en;
public:
    Edges(int ,int, double);
    int get_start();
    int get_end();
    double get_weight();
};

Edges::Edges(int s, int e, double w){
    st = s;
    en = e;
    we = w;
}

int Edges::get_start(){
    return st;
}

int Edges::get_end(){
    return en;
}

double Edges::get_weight(){
    return we;
}

class Graph{
    int v, e;
    vector<Edges> edges;
    int *parent;
    int *c_n;
    double** adj_m = new double*[v];
    bool *visited = new bool[v];

public:
    Graph(int, int);
    void addEdges(int, int, double);
    double Kruskal();
    double Prims(int);
    int find_parent(int);
    int get_min(bool *visited,double *mst, int cnt);
};

Graph::Graph(int ver, int ed){
    v = ver;
    e = ed;

    for(int i=0; i<v; i++){
        adj_m[i] = new double[v];
        visited[i] = false;
        for(int j= 0; j<v; j++){
            adj_m[i][j]= DBL_MAX;
        }
    }
}

int Graph::find_parent(int x){
    if(parent[x]==x)
        return x;
    else
        return find_parent(parent[x]);
}

void Graph::addEdges(int s, int e, double w){
    Edges edge(s,e,w);
    edges.push_back(edge);
    adj_m[s][e] = w;
    adj_m[e][s] = w;
}

int Graph::get_min(bool *visited, double *mst_, int cnt){
    int c = cnt;
    int min_i, min_j;
    double min_ = DBL_MAX;
    for(int i=0; i<v; i++){
        if(visited[i]){
            for(int j=0; j<v ; j++){
                if(!(visited[j])){
                    if((adj_m[i][j]<min_)){
                        min_i = i;
                        min_j = j;
                        min_ = adj_m[i][j];
                    }
                }
            }
        }
    }
    visited[min_j]= true;
    mst_[cnt-1] = min_;
    cout << "(" << min_i << "," << min_j <<"),";
    c+=1;
    return c;
}

double Graph::Kruskal(){
    double mst = 0;
    parent = new int[v];
    c_n = new int[v];
    vector <int> start_nodes;
    vector <int> end_nodes;
    int cnt =0;
    for(int i=0; i<v; i++){
        parent[i] = i;
        c_n[i] = 1;
    }
    sort(edges.begin(),edges.end(), [](Edges a, Edges b) { return a.get_weight() < b.get_weight(); });
    for(int i=0; i<e ; i++){
        int start_ = edges[i].get_start();
        int end_ = edges[i].get_end();
        int a = find_parent(start_);
        int b = find_parent(end_);
        if(a != b){
            mst += edges[i].get_weight();
            start_nodes.push_back(start_);
            end_nodes.push_back(end_);
            cnt++;
            if(c_n[a] >= c_n[b]){
                parent[b] = parent[a];
                c_n[a]+=c_n[b];
            }
            else
            {
                parent[a] = parent[b];
                c_n[b]+=c_n[a];            }
        }
    }
    cout << "Cost of the minimum spanning tree : " << fixed << setprecision(1) << mst <<endl;
    cout << "List of edges selected by Kruskal\'s : {" ;
    for(int i= 0; i<cnt; i++)
        cout << "(" << start_nodes[i] << "," << end_nodes[i] << "),";
    cout << "\b}" <<endl;
    return mst;
}

double Graph::Prims(int o){
    cout << "List of edges selected by Prim\'s : {" ;
    double *mst_ = new double[v-1];
    double cost = 0;
    visited[o] = true;
    int cnt = 1;
    while(cnt!=v){
       cnt = get_min(visited, mst_, cnt);
    }
    cout <<"\b}" << endl;
    for(int i=0; i<v-1; i++)
        cost += mst_[i];
    return cost;
}

int main()
{
    freopen("mst.in.txt", "r", stdin);
    int ver_,ed_,a,b;
    double we;
    cin >> ver_ >> ed_ ;
    Graph g1(ver_,ed_);

    for(int j=0; j<ed_; j++){
        cin >> a >> b >> we;
        g1.addEdges(a, b, we);
    }

    double mst = g1.Kruskal();
    mst = g1.Prims(0);
    return 0;
}
