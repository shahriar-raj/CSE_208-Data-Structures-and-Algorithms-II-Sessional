#include <bits/stdc++.h>

using namespace std;

class Graph{
    int vertices, edges;
    double** adjacen_m;

public:
    Graph(int v);
    Graph(){};
    void addEdge(int so , int d, double w);
    int n_vertices();
    int n_edges();
    double **Floyd_Warshall();
    double **Matrix_Multiplication();
    double **Extend_Shortest_Paths(double** L, double** W);
};

Graph::Graph(int v){
    vertices = v;
    edges=0;
    adjacen_m = new double*[vertices];
    for(int j=0; j<vertices; j++){
        adjacen_m[j] = new double[vertices];
        for(int k=0;k<vertices;k++){
            if(j==k)
                adjacen_m[j][k] = 0;
            else
                adjacen_m[j][k] = DBL_MAX;
        }
    }
}

void Graph::addEdge(int so, int d, double w){
    adjacen_m[so-1][d-1] = w;
    edges++;
}

int Graph::n_vertices(){
    return vertices;
}

int Graph::n_edges(){
    return edges;
}

double ** Graph::Floyd_Warshall(){
    double **distance = new double* [vertices];
    for(int i=0; i<vertices; i++){
        distance[i] = new double[vertices];
        for(int j=0; j<vertices; j++){
            if(i==j)
                distance[i][j] = 0;
            else if(adjacen_m[i][j]!=0)
                distance[i][j] = adjacen_m[i][j];
            else
                distance[i][j] = DBL_MAX;
        }
    }

    for(int m=0; m<vertices; m++){
        for(int i=0; i<vertices; i++){
            for(int j=0; j<vertices; j++){
                distance[i][j] = min(distance[i][j],distance[i][m]+distance[m][j]);
            }
        }
    }
    return distance;
}

double** Graph::Extend_Shortest_Paths(double** L, double** W){
    double **L_new_2 = new double*[vertices];
    for(int l=0; l<vertices; l++)
            L_new_2[l] = new double[vertices];
    for(int i=0; i<vertices; i++){
        for(int j=0; j<vertices; j++){
            L_new_2[i][j] = DBL_MAX;
            for(int k=0; k<vertices; k++){
                L_new_2[i][j] = min(L_new_2[i][j], (L[i][k]+W[k][j]));
            }
        }
    }
    return L_new_2;
}

double** Graph::Matrix_Multiplication(){
    //cout << "YES!!!!" << endl;
    double **L = new double*[vertices];
    for(int i=0; i<vertices; i++){
        L[i] = new double[vertices];
        for(int j=0; j<vertices; j++){
            L[i][j] = adjacen_m[i][j] ;
        }
    }

    double **L_new = new double*[vertices];

    for(int m=1; m<vertices-1; m++){
        for(int l=0; l<vertices; l++)
            L_new[l] = new double[vertices];
        L_new = Extend_Shortest_Paths(L, adjacen_m);
        for(int i=0; i<vertices; i++){
            for(int j=0; j<vertices; j++){
                L[i][j]=L_new[i][j];
            }
        }
    }
    return L_new;
}

int main(){
    freopen("all_pair_shortest_path.txt", "r", stdin);
    int v,e, single_source, destination;
    cin >> v >> e;
    Graph g1(v);
    for(int i=0; i<e; i++){
        int so, d;
        double w;
        cin >> so >> d >> w;
        g1.addEdge(so, d, w);
    }
    //double ** distance = g1.Floyd_Warshall();
    double ** distance = g1.Matrix_Multiplication();

    cout << "Shortest Distance Matrix: "<<endl;
    for(int i=0; i<v; i++){
        for(int j=0; j<v; j++){
            if(distance[i][j]==DBL_MAX)
                cout <<"INF ";
            else
                cout<<distance[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
