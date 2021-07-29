
// implementation of traveling Salesman Problem
#include <bits/stdc++.h>
#include "tsp.cpp"

using namespace std;
 
// implementation of traveling Salesman Problem
vector<int> travllingSalesmanProblem(vector<vector<double_t>> &graph, int s)
{
    // store all vertex apart from source vertex
    auto t_start = std::chrono::high_resolution_clock::now();
    vector<int> vertex;
    vector<int> shortest_path;
    for (int i = 0; i < graph.size(); i++)
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
    auto t_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t_end-t_start);
    cout << "Time taken for real TSP: " << duration.count() << " microseconds" << endl;
    return shortest_path;
}
 
void genRandomNumbers(vector<vector<double_t>>& adj){
    for(int i =0;i<adj.size();i++){
        for(int j = 0;j< adj.size();j++){
            adj[i][j] = 10.0 + static_cast <double_t> (rand()) /( static_cast <double_t> (RAND_MAX/(25.0-10.0)));
        }
    }
}

void test(){ 
    int n = 13;
    int final_path[n+1];
    bool visited[n];
    double final_res = INT_MAX;
    vector<vector<double_t>> adj;
    adj.resize(n);
    for(int i=0;i<adj.size();i++) adj[i].resize(n);
    genRandomNumbers(adj);
    
    TSP(adj,n,visited,final_res,final_path);

    printf("Minimum cost : %f\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=n; i++)
        printf("%d ", final_path[i]);
    printf("\n");
    
    auto shortest = travllingSalesmanProblem(adj, 0);
    int temp = 0;
    double costo = 0;
    for(int i=0;i<shortest.size();i++){
        int it = shortest[i];
        costo+=adj[temp][it];
        temp = it;
        cout<< it<<" ";
    }
    cout<<endl; 
    costo+= adj[temp][0];
    cout<<"Real minimum cost: "<<costo<<endl;    
    cout << "---------------------------" << endl;
}


void copy_matrix(vector<vector<double>> &to,double from[][4]){ 
    int n = to.size();
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            to[i][j] = from[i][j]; 
        }
    }

}
int main()
{
    srand(time(NULL));
    test();
    
    return 0;
}
