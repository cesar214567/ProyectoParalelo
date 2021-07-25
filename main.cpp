#include <bits/stdc++.h>
#include "tsp.cpp"

using namespace std;
#define V 10
 
// implementation of traveling Salesman Problem
vector<int> travllingSalesmanProblem(double graph[][V], int s)
{
    // store all vertex apart from source vertex
    vector<int> vertex;
    vector<int> shortest_path;
    for (int i = 0; i < V; i++)
        if (i != s)
            vertex.push_back(i);
 
    // store minimum weight Hamiltonian Cycle.
    double min_path = INT_MAX;
    do {
 
        // store current Path weight(cost)
        double current_pathweight = 0;
 
        // compute current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];
 
        // update minimum   
        if(min(min_path,current_pathweight)==current_pathweight){
            shortest_path=vertex;
        }
        min_path = min(min_path, current_pathweight);
    
    } while (
        next_permutation(vertex.begin(), vertex.end()));
 
    return shortest_path;
}
 



// Driver Code
int main()
{
    // matrix representation of graph
    double graph[V][V] ;
    auto data = getData("matrix.txt",10);
    vector<string> names = data.first;
    auto adj = data.second;
    for(int i=0;i<V;i++){
        for(int j = 0;j<V;j++){
            graph[i][j] = adj[i][j];
            cout<<graph[i][j]<<" ";
        }cout<<endl;
    }
    
    int s = 0;
    //cout << travllingSalesmanProblem(graph, s) << endl;
    auto shortest = travllingSalesmanProblem(graph, s);
    int temp = 0;
    double costo = 0;
    for(int i=0;i<shortest.size();i++ ){
        int it = shortest[i];
        costo+=graph[temp][it];
        temp = it;
        cout<< it<<" ";
    }
    cout<<endl; 
    costo+= graph[temp][0];
    cout<<"suposed minimum cost:"<<costo<<endl;

    int final_path[V+1];
    bool visited[V];
    double final_res = INT_MAX;
    TSP(adj,V,visited,final_res,final_path);

    double costo_real=0;
    printf("Minimum cost : %f\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=V; i++){
        printf("%d ", final_path[i]);
        //if (i>0)cout<<graph[final_path[i-1]][final_path[i]]<<" " ;
        if (i>0)costo_real+=graph[final_path[i-1]][final_path[i]] ;
    }
        
    cout<<"real cost: "<<costo_real<<endl;

    return 0;
}
