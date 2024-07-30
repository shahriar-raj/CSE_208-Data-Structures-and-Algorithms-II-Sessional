#include <bits/stdc++.h>
#include "heap.h"
#include "fibonacci_heap.h"

using namespace std;

class Graph{
    int vertices, edges;
    vector<vector<pair<int,double>>> adjacen_l;

public:
    Graph(int v);
    Graph(){};
    void addEdge(int so , int d, double w);
    void addVertices();
    int n_vertices();
    int n_edges();
    double Dijkstra(int, int);
    double Dijkstra_f(int , int );
};

Graph::Graph(int v){
    vertices = v;
    edges=0;
    for(int j=0; j<vertices; j++){
        vector<pair<int,double>> v1;
        adjacen_l.push_back(v1);
    }
}

void Graph::addEdge(int so, int d, double w){
    pair <int, double> p;
    p.first = d;
    p.second = w;
    adjacen_l[so].push_back(p);
    edges++;
}

void Graph::addVertices(){
    vertices++;
    vector<pair<int, double>> v1;
    adjacen_l.push_back(v1);
}

int Graph::n_vertices(){
    return vertices;
}

int Graph::n_edges(){
    return edges;
}

void show_parent(int *parents, int m){
    if(parents[m]==-1){
        return;
    }
    show_parent(parents, parents[m]);
    cout << parents[m] << "->";
    return;
}

double Graph::Dijkstra(int single_s, int dest){
    int * parents = new int[vertices];
    bool *visited = new bool[vertices];
    vector<Node> dis;
    //INITIALIZE
    for(int i=0; i<vertices;i++){
        parents[i] = -1;
        visited[i] = false;
        Node p;
        p.v = i;
        p.key = DBL_MAX;
        dis.push_back(p);
    }
    dis[single_s].key = 0;
    Heap pq(dis);
    int gl = 0;
    while(pq.size()!=0&&gl!=vertices){
        Node p = pq.getMin();
        int k = p.v;
        pq.deleteKey();
        for(int j= 0; (j<adjacen_l[k].size()&&!visited[k]); j++){
            pair <int, double> r = adjacen_l[k][j];
           // cout << r.first << endl;
            if(dis[r.first].key > dis[k].key + r.second){         // RELAXATION
                dis[r.first].key = dis[k].key + r.second;
                //cout << dis[r.first].second  << endl;
                parents[r.first] = k;
                pq.insert(dis[r.first]);
            }
        }
        visited[k] = true;
        gl++;
    }
    int fi = dest;
    int path =0;
    while(parents[fi]!=-1){
        path++;
        fi = parents[fi];
    }
    cout << path <<" \t\t "<< dis[dest].key<<" \t\t ";
    delete parents;
    delete visited;
    return dis[dest].key;
}

double Graph::Dijkstra_f(int single_s, int dest){
    int * parents = new int[vertices];
    bool *visited = new bool[vertices];
    vector<pair<int,double>> dis;
    fibonacci_heap pq;
    //INITIALIZE
    for(int i=0; i<vertices;i++){
        visited[i] = false;
        parents[i] = -1;
        pair<int, double> p;
        p.first = i;
        p.second = DBL_MAX;
        dis.push_back(p);
    }
    dis[single_s].second = 0;
    for(int i=0; i<vertices; i++){
        node *et = new node;
        et->ver = dis[i].first;
        et->key = dis[i].second;
        //cout << "Enter "<< et->ver << " " << et->key <<endl;
        pq.fib_heap_insert(et);
    }

    int gl = 0;
    while(pq.getmin()!=nullptr&&gl!=vertices){
        double p = pq.getmin()->key;
        int k = pq.getmin()->ver;
        node* reer = new node;
        reer = pq.fib_heap_extract_min();
        //cout << reer->ver << " " << reer->key << " MIN" << endl;
        for(int j= 0; (j<adjacen_l[k].size()&&!visited[reer->ver]); j++){
            pair <int, double> r = adjacen_l[k][j];
           // cout << r.first << endl;
            if(dis[r.first].second > dis[k].second + r.second){         // RELAXATION
                dis[r.first].second = dis[k].second + r.second;
                //cout << dis[r.first].second  << endl;
                parents[r.first] = k;
                node *et = new node;
                et->key = dis[r.first].second;
                et->ver = dis[r.first].first;
                //cout << et->key <<" " << et->ver <<endl;
                pq.fib_heap_insert(et);
            }
        }
        visited[reer->ver] = true;
        gl++;
    }
    delete pq.getmin();
    /*int fi = dest;
    int path =0;
    while(parents[fi]!=-1){
        path++;
        fi = parents[fi];
    }
    cout << path <<" "<< dis[dest].second<<" ";*/
    delete parents;
    delete visited;
    return dis[dest].second;
}

int main()
{
    cout << "Path Length  \tPath Cost  \t Binary_Heap_time \tfibonacci_heap_time" << endl;
    int v,e, single_source, destination, test_c;
    freopen("heap_1.txt", "r", stdin);
    cin >> v >> e;
    Graph g1(v);
    for(int i=0; i<e; i++){
        int so, d;
        double w;
        cin >> so >> d >> w;
        g1.addEdge(so, d, w);
        g1.addEdge(d, so, w);
    }
    freopen("heap_2.txt", "r", stdin);
    cin >> test_c;
    for(int n_c = 0; n_c<test_c; n_c++){
        cin >> single_source >> destination;
        clock_t time_o1 = clock();
        double  result = g1.Dijkstra(single_source,destination);
        cout << float(clock() - time_o1)/CLOCKS_PER_SEC  << "\t\t\t\t ";
        //cout << endl;
        clock_t time_o2 = clock();
        result = g1.Dijkstra_f(single_source,destination);
        cout << float(clock() - time_o2)/CLOCKS_PER_SEC  << endl;
    }
    return 0;
}
