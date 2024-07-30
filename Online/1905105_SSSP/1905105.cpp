#include <bits/stdc++.h>

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
    pair<bool, double> Bellman_ford(int, int);
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

class comp{
public:
    bool operator()(pair<int,double> p1, pair<int,double> p2){
        return p1.second < p2.second;
    }
};

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
    vector<pair<int,double>> dis;

    //INITIALIZE
    for(int i=0; i<vertices;i++){
        parents[i] = -1;
        pair<int, double> p;
        p.first = i;
        p.second = 0;
        dis.push_back(p);
    }
    dis[single_s].second = 1;

    priority_queue<pair<int,double>, vector<pair<int,double>>, comp> pq;
    for(int i=0; i<vertices; i++){
        pq.push(dis[i]);
    }
    int gl = 0;
    while(!pq.empty()&&gl!=vertices){
        pair<int, double> p = pq.top();
        int k = p.first;
       // cout << "HELLO" << k <<" " << adjacen_l[k].size()<<endl;
        pq.pop();
        for(int j= 0; j<adjacen_l[k].size(); j++){
            pair <int, double> r = adjacen_l[k][j];
           // cout << r.first << endl;
            if(dis[r.first].second < dis[k].second * r.second){         // RELAXATION
                dis[r.first].second = dis[k].second * r.second;
                //cout << dis[r.first].second  << endl;
                parents[r.first] = k;
                pq.push(dis[r.first]);
            }
        }
        gl++;
    }
    cout << "Most Reliable Path Score:" << dis[dest].second<<endl;
    show_parent(parents, dest);
    cout << dest << endl;
    return dis[dest].second;
}

pair<bool, double> Graph::Bellman_ford(int single_s, int dest){
    int *parents = new int[vertices];
    pair<bool, double> result_b;
    result_b.first = true;
    vector<pair<int,double>> dis;

    //INITIALIZE
    for(int i=0; i<vertices;i++){
        parents[i] = -1;
        pair<int, double> p;
        p.first = i;
        p.second = 0;
        dis.push_back(p);
    }
    dis[single_s].second = 1;

    for(int i=0; i< vertices-1; i++){
        for(int j=0; j<vertices; j++){
            for(int k=0; k<adjacen_l[j].size(); k++){
                pair <int, double> r = adjacen_l[j][k];
                if(dis[r.first].second < dis[j].second * r.second){         // RELAXATION
                    dis[r.first].second < dis[j].second * r.second;
                    parents[r.first] = j;
                }
            }
        }
    }

    for(int j=0; j<vertices; j++){
        for(int k=0; k<adjacen_l[j].size(); k++){
            pair <int, double> r = adjacen_l[j][k];
            if(dis[r.first].second < dis[j].second * r.second){         // Checking if there is a negative cycle
                result_b.first = false;
            }
        }
    }

    result_b.second = dis[dest].second;
    if(result_b.first == false)
        cout << "The graph contains a negative cycle" <<endl;
    else{
        cout << "The graph does not contain a negative cycle\nMost Reliable Path Cost:" << result_b.second <<endl;
        show_parent(parents, dest);
        cout << dest << endl;
    }
    return result_b;
}

int main()
{
    //cout << "Dijkstra:" << endl;
    int v,e, single_source, destination;
    freopen("dijkstra_si.txt", "r", stdin);
    cin >> v >> e;
    Graph g1(v);
    for(int i=0; i<e; i++){
        int so, d;
        double w;
        cin >> so >> d >> w;
        g1.addEdge(so, d, w);
    }
    cin >> single_source >> destination;
    int result = g1.Dijkstra(single_source,destination);

    /*cout << "\n===========================================================\n" <<endl;

    cout << "Bellman_Ford:" << endl;
    freopen("bellman_si.txt", "r", stdin);
    cin >> v >> e;
    Graph g2(v);
    for(int i=0; i<e; i++){
        int so, d;
        double w;
        cin >> so >> d >> w;
        g2.addEdge(so, d, w);
    }
    cin >> single_source >> destination;
    pair<bool , double> result_b = g2.Bellman_ford(single_source,destination);*/
    return 0;
}
