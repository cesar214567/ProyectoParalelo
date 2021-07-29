#include<bits/stdc++.h>
#include<omp.h>
#include "utils.cpp"


// https://www.youtube.com/watch?v=1FEP_sNb62k&ab_channel=AbdulBari Branch and Bound

using namespace std;
int cont = 0;
// Function to copy temporary solution to
// the final solution


void copyToFinal(int curr_path[],int final_path[],int n)
{
    #pragma omp parallel for num_threads(4)
    for (int i=0; i<n; i++)
        final_path[i] = curr_path[i];
    final_path[n] = curr_path[0];
}

void TSPRec(vector<vector<double_t>> &adj,int n, double_t &curr_bound, double_t curr_weight,
            int level, int curr_path[],bool visited[],double_t &final_res,int final_path[])
{
    cont++;
    if (level==n)
    {
        
        if (adj[curr_path[level-1]][curr_path[0]] != 0)
        {
            double_t curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];
            if (curr_res < final_res)
            {
                copyToFinal(curr_path,final_path,n);
                final_res = curr_res;
                curr_bound = final_res;
            }
        }
        return;
    }
    //priority_queue<pair<double_t,int>> good_branches;
    vector<pair<double_t,int>> good_branches;    
    #pragma omp parallel for num_threads(4)
    for (int i=0; i<n; ++i)
    {
        if (adj[curr_path[level-1]][i] != 0 && !visited[i])
        {
            if (curr_bound > curr_weight)
            {
                auto temp = make_pair(curr_weight+adj[curr_path[level-1]][i],i);
                #pragma omp critical
                //good_branches.push(temp);
                good_branches.push_back(temp);
            }
        }
    } 
    sort(good_branches.begin(),good_branches.end());
    //while(!good_branches.empty()) {
    //    auto it = good_branches.top();
    //    good_branches.pop();
    for (auto it:good_branches){
        double_t temp = curr_bound;
        curr_weight = it.first;
        int i = it.second;
        if (curr_bound > curr_weight){
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

void TSP(vector<vector<double_t>> &adj,int n,bool visited[],double_t &final_res,int final_path[])
{
    int curr_path[n+1];
    double_t curr_bound = INT_MAX;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));
    curr_bound = INT_MAX;
    visited[0] = true;
    curr_path[0] = 0;
    auto start = std::chrono::high_resolution_clock::now();
    TSPRec(adj,n, curr_bound, 0, 1, curr_path,visited,final_res,final_path);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time taken for TSP: " << duration.count() << " microseconds" << endl;
    cout<<cont<<endl;
}

