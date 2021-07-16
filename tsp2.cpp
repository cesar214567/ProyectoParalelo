#include<bits/stdc++.h>
#include<omp.h>

// https://www.youtube.com/watch?v=1FEP_sNb62k&ab_channel=AbdulBari Branch and Bound



using namespace std;
const int N = 4;

// final_path[] stores the final solution ie, the
// path of the salesman.
int final_path[N+1];

// visited[] keeps track of the already visited nodes
// in a particular path
bool visited[N];

// Stores the final minimum weight of shortest tour.
int final_res = INT_MAX;

// Function to copy temporary solution to
// the final solution
void copyToFinal(int curr_path[])
{
    for (int i=0; i<N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

void TSPRec(int adj[N][N], int &curr_bound, int curr_weight,
            int level, int curr_path[])
{
    
    if (level==N)
    {
        if (adj[curr_path[level-1]][curr_path[0]] != 0)
        {
            int curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];
            if (curr_res < final_res)
            {
                copyToFinal(curr_path);
                final_res = curr_res;
                curr_bound = final_res;
            }
        }
        return;
    }
    vector<pair<int,int>> good_branches;
    #pragma omp parallel for num_threads(8)
    for (int i=0; i<N; i++)
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
            TSPRec(adj, curr_bound, curr_weight, level+1, curr_path);
        }
        curr_weight -= adj[curr_path[level-1]][i];
        curr_bound = temp;
        memset(visited, false, sizeof(visited));
        for (int j=0; j<=level-1; j++)
            visited[curr_path[j]] = true;

    }
}

void TSP(int adj[N][N])
{
    int curr_path[N+1];
    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));
    memset(visited, 0, sizeof(curr_path));
    curr_bound = INT_MAX;
    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

// Driver code
int main()
{
    //Adjacency matrix for the given graph
    int adj[N][N] = { 
                    {0, 11, 14, 20},
                    {10, 0, 35, 25},
                    {15, 35, 0, 30},
                    {20, 25, 30, 0}
    };
    TSP(adj);

    printf("Minimum cost : %d\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=N; i++)
        printf("%d ", final_path[i]);

    return 0;
}
