#include "tsp.cpp"

// implementation of traveling Salesman Problem
vector<int> travllingSalesmanProblem(double graph[][4], int s)
{
    // store all vertex apart from source vertex
    vector<int> vertex;
    vector<int> shortest_path;
    for (int i = 0; i < 4; i++)
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

void test(vector<vector<double>> adj, double adj2[][4]){ 
    int n = adj.size();
    int final_path[n+1];
    bool visited[n];
    double final_res = INT_MAX;
    TSP(adj,n,visited,final_res,final_path);

    printf("Minimum cost : %f\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=n; i++)
        printf("%d ", final_path[i]);
    printf("\n");

    auto shortest = travllingSalesmanProblem(adj2, 0);
    int temp = 0;
    double costo = 0;
    for(int i=0;i<shortest.size();i++){
        int it = shortest[i];
        costo+=adj2[temp][it];
        temp = it;
        cout<< it<<" ";
    }
    cout<<endl; 
    costo+= adj2[temp][0];
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
    // auto data = getData("matrix.txt",10);
    // vector<string> names = data.first;
    vector<vector<double>> adj;
    // test(adj);
    
    int n =4;
    
    adj.resize(n);
    for(int i=0;i<adj.size();i++){
        adj[i].resize(n);
    }

    double adj2[4][4] = { 
                    {0, 11, 14, 20},
                    {10, 0, 35, 25},
                    {15, 35, 0, 30},
                    {20, 25, 30, 0}
    };
    copy_matrix(adj,adj2);
    test(adj, adj2);
    




    double adj3[4][4] = { 
                    {0, 10, 15, 20},
                    {5, 0, 9, 10},
                    {6, 13, 0, 12},
                    {8, 8, 9, 0}
    };
    copy_matrix(adj,adj3);
    test(adj, adj3);



    
    double adj4[4][4] = { 
                    {0, 10, 17, 15},
                    {20, 0, 19, 18},
                    {50, 44, 0, 25},
                    {45, 40, 20, 0}
    };
    copy_matrix(adj,adj4);
    test(adj, adj4);
    ///////////////////////////
    
    
    return 0;
}
