#include<bits/stdc++.h>
#include<omp.h>
#include "utils.cpp"
// https://www.youtube.com/watch?v=1FEP_sNb62k&ab_channel=AbdulBari Branch and Bound

using namespace std;

// Function to copy temporary solution to
// the final solution
pair<vector<string>,vector<vector<double>>> getData(string filename,int n){
    fstream file(filename);
    string name;
    double temp;
    vector<string> names;
    vector<vector<double>>data; 
    
    for(int i=0;i<n;i++){
        file>>name;
        vector<double> sub_data;
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

void TSPRec(vector<vector<double>> adj,int n, double &curr_bound, double curr_weight,
            int level, int curr_path[],bool visited[],double &final_res,int final_path[])
{
    
    if (level==n)
    {
        if (adj[curr_path[level-1]][curr_path[0]] != 0)
        {
            double curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];
            if (curr_res < final_res)
            {
                copyToFinal(curr_path,final_path,n);
                final_res = curr_res;
                curr_bound = final_res;
            }
        }
        return;
    }
    vector<pair<double,int>> good_branches;
    #pragma omp parallel for num_threads(10)
    for (int i=0; i<n; ++i)
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
        double temp = curr_bound;
        curr_weight = it.first;
        int i = it.second;
        if (curr_bound > curr_weight)
        {
            curr_path[level] = i;
            visited[i] = true;
            TSPRec(adj,n, curr_bound, curr_weight, level+1, curr_path,visited,final_res,final_path);
        }
        curr_weight -= adj[curr_path[level-1]][i];
        memset(visited, false, n);
        for (int j=0; j<=level-1; j++)
            visited[curr_path[j]] = true;

    }
}

void TSP(vector<vector<double>> adj,int n,bool visited[],double &final_res,int final_path[])
{
    int curr_path[n+1];
    double curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));
    curr_bound = INT_MAX;
    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(adj,n, curr_bound, 0, 1, curr_path,visited,final_res,final_path);
}

