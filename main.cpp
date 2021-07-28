#include <bits/stdc++.h>
#include "tsp.cpp"

using namespace std;
#define V 10
 
// implementation of traveling Salesman Problem
vector<int> travllingSalesmanProblem(double_t graph[][V], int s)
{
    // store all vertex apart from source vertex
    vector<int> vertex;
    vector<int> shortest_path;
    for (int i = 0; i < V; i++)
        if (i != s)
            vertex.push_back(i);
    // store minimum weight Hamiltonian Cycle.
    double_t min_path = INT_MAX;
    do {
        // store current Path weight(cost)
        double_t current_pathweight = 0;
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
    double_t graph[V][V] ;
    auto data = getData("matrix.txt",10);
    vector<string> names = data.first;
    auto adj = data.second;
    for(int i=0;i<V;i++){
        for(int j = 0;j<V;j++){
            graph[i][j] = adj[i][j];
            //cout<<graph[i][j]<<" ";
        }//cout<<endl;
    }
    int s = 0;
    auto shortest = travllingSalesmanProblem(graph, s);
    int temp = 0;
    double_t costo = 0;
    for(int i=0;i<shortest.size();i++ ){
        int it = shortest[i];
        costo+=graph[temp][it];
        temp = it;
        cout<< it<<" ";
    }
    cout<<endl; 
    costo+= graph[temp][0];
    cout<<"Reference minimum cost:"<<costo<<endl;
    cout << "*Our algorithm: \n";

    int final_path[V+1];
    bool visited[V];
    double_t final_res = INT_MAX;
    auto start = std::chrono::high_resolution_clock::now();
    TSP(adj,V,visited,final_res,final_path);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time taken for TSP: " << duration.count() << " microseconds" << endl;


    double_t costo_real=0;
    printf("Minimum cost : %f\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=V; i++){
        printf("%d ", final_path[i]);
        //if (i>0)costo_real+=graph[final_path[i-1]][final_path[i]] ;
    }
        
    //cout<<"\nReal cost: "<<costo_real<<endl;

    return 0;
}
