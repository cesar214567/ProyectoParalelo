#include<bits/stdc++.h>
#include<omp.h>
// https://www.youtube.com/watch?v=1FEP_sNb62k&ab_channel=AbdulBari Branch and Bound

using namespace std;

// Function to copy temporary solution to
// the final solution
pair<vector<string>,vector<vector<int>>> getData(string filename,int n){
    fstream file(filename);
    string name;
    int temp;
    vector<string> names;
    vector<vector<int>>data; 
    file>>name;
    
    for(int i=0;i<n;i++){
        vector<int> sub_data;
        for(int j=0;j<n;j++){
            file>>temp;
            sub_data.push_back(temp);
        }    
        data.push_back(sub_data);
        names.push_back(name);
    }
    return {names,data};

}

void copyToFinal(int curr_path[],int final_path[],int n)
{
    for (int i=0; i<n; i++)
        final_path[i] = curr_path[i];
    final_path[n] = curr_path[0];
}

void TSPRec(vector<vector<int>> adj,int n, int &curr_bound, int curr_weight,
            int level, int curr_path[],bool visited[],int &final_res,int final_path[])
{
    
    if (level==n)
    {
        if (adj[curr_path[level-1]][curr_path[0]] != 0)
        {
            int curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];
            if (curr_res < final_res)
            {
                copyToFinal(curr_path,final_path,n);
                final_res = curr_res;
                curr_bound = final_res;
            }
        }
        return;
    }
    vector<pair<int,int>> good_branches;
    #pragma omp parallel for num_threads(8)
    for (int i=0; i<n; i++)
    {
        if (adj[curr_path[level-1]][i] != 0 && !visited[i])
        {
            if (curr_bound > curr_weight)
            {
                auto temp = make_pair(curr_weight+adj[curr_path[level-1]][i],i);
                #pragma omp critical
                good_branches.push_back(temp);
            }
        }
    }
    sort(good_branches.begin(),good_branches.end());
    for (auto it:good_branches){
        int temp = curr_bound;
        curr_weight = it.first;
        int i = it.second;
        if (curr_bound > curr_weight)
        {
            curr_path[level] = i;
            visited[i] = true;
            TSPRec(adj,n, curr_bound, curr_weight, level+1, curr_path,visited,final_res,final_path);
        }
        curr_weight -= adj[curr_path[level-1]][i];
        curr_bound = temp;
        memset(visited, false, n);
        for (int j=0; j<=level-1; j++)
            visited[curr_path[j]] = true;

    }
}

void TSP(vector<vector<int>> adj,int n,bool visited[],int &final_res,int final_path[])
{

    int curr_path[n+1];
    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));
    curr_bound = INT_MAX;
    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(adj,n, curr_bound, 0, 1, curr_path,visited,final_res,final_path);
}

// Driver code
int main()
{
    int n = 4;
    vector<vector<int>> adj;
    adj.resize(n);
    for(auto it:adj){
        it.resize(n);
    }
    int adj2[n][n] = { 
                    {0, 11, 14, 20},
                    {10, 0, 35, 25},
                    {15, 35, 0, 30},
                    {20, 25, 30, 0}
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j] = adj2[i][j];
        }
    }

    int final_path[n+1];
    bool visited[n];
    int final_res = INT_MAX;
    TSP(adj,n,visited,final_res,final_path);

    printf("Minimum cost : %d\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=n; i++)
        printf("%d ", final_path[i]);

    return 0;
}

void createdb(){
    fstream file("nodos.txt");

}