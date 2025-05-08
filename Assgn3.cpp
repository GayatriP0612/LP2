#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge{
    int u, v, weight;
};

class Graph{
    private:
    int V, E;
    vector<Edge> edges;

    public:
    Graph(int V, int E){
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int weight){
        edges.push_back({u, v, weight});
    }

    // Prims Minimum Spanning Tree
    void PrimsMST(){
        vector<int> parent(V, -1);
        vector<int> key(V, INT_MAX);
        vector<bool> inMST(V, false);

        key[0] = 0;

        for(int i=0; i< V-1; i++){
            int u = -1;
            for(int v=0; v<V; v++){
                if(!inMST[v] && (u == -1 || key[v] < key[u])){
                    u = v;
                }
            }

            inMST[u] = true;

            for(const auto &edge: edges){
                if(edge.u == u || edge.v == u){
                    int v = (edge.u == u) ? edge.v : edge.u;
                    if(!inMST[v] && edge.weight < key[v]){
                        key[v] = edge.weight;
                        parent[v] = u;
                    }
                }
            }
        }

        // print values
        cout <<"Prims Minimum Spanning Tree\n";
        int t_weight = 0;
        for(int i=0; i<V; i++){
            cout << parent[i] << "-" << i << ":" << key[i] << endl;
            t_weight += key[i];
        }

        cout << "Total Cost: " << t_weight<< endl;
    }

    //helper functions for krushkal mst
    int FindParent(int i, vector<int> &parent){
        if(parent[i] == i)
            return i;
        return parent[i] = FindParent(parent[i], parent); // path compression   
    }

    void unionsets(int u, int v, vector<int> &parent, vector<int> &rank){
        int root_u = FindParent(u, parent);
        int root_v = FindParent(v, parent);

        if(root_u != root_v){
            if(rank[root_u] > rank[root_v]){
                parent[root_v] = root_u;
            }
            else if(rank[root_u] < rank[root_v]){
                parent[root_u] = root_v;
            }
            else{
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }

    // kruskal mst
    void KruskalMST(){
        vector<Edge> result;
        vector<int> parent(V);
        vector<int> rank(V, 0);

        for(int i=0; i<V; i++){
            parent[i] = i;
        }

        sort(edges.begin(), edges.end(), [](Edge a, Edge b){return a.weight < b.weight;});

        for(const auto &edge: edges){
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;

            int p_u = FindParent(u, parent);
            int p_v = FindParent(v, parent);

            if(p_u != p_v){
                result.push_back(edge);
                unionsets(u, v, parent, rank);
            }
        }

        cout << "Kruskal Minimum Spanning Tree"<< endl;
        int tot_weight = 0;
        for (auto &edge: result){
            cout << edge.u << "-" << edge.v << ":" << edge.weight<<endl;
            tot_weight += edge.weight;
        }

        cout<< "Total cost:" << tot_weight<< endl;

    }
};

int main(){
    int V, E, u, v, weight;
    

    cout<<"Enter no. of vertices:";
    cin>> V;

    cout << "No. of Edges:";
    cin >> E;
    Graph g(V, E);

    for(int i=0; i<E; i++){
        cout << "Edge" << i+1 << "(u,v,weight) ";
        cin >> u >> v >> weight;
        g.addEdge(u,v,weight);
    }

    g.PrimsMST();
    g.KruskalMST();

    return 0;
}