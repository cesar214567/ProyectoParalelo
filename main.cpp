#include "tsp2.cpp"

void test(vector<vector<double>> adj){ 
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
    auto data = getData("matrix.txt",10);
    vector<string> names = data.first;
    auto adj = data.second;
    test(adj);
    
    
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
    test(adj);
    double adj3[4][4] = { 
                    {0, 10, 15, 20},
                    {5, 0, 9, 10},
                    {6, 13, 0, 12},
                    {8, 8, 9, 0}
    };
    copy_matrix(adj,adj3);
    test(adj);
    double adj4[4][4] = { 
                    {0, 10, 17, 15},
                    {20, 0, 19, 18},
                    {50, 44, 0, 25},
                    {45, 40, 20, 0}
    };
    copy_matrix(adj,adj4);
    test(adj);
    ///////////////////////////
    
    
    return 0;
}
