
#include<bits/stdc++.h>
#include<omp.h>
#include <stack>
#include "utils.cpp"

int cont = 0;
#define V 10

void copyToFinal(int curr_path[],int final_path[],int n)
{
    #pragma omp parallel for num_threads(4)
    for (int i=0; i<n; i++)
        final_path[i] = curr_path[i];
    final_path[n] = curr_path[0];}

void TSPRec(vector<vector<double_t>> &adj,int n, double_t &curr_bound, double_t curr_weight,
            int level, int curr_path[],bool visited[],double_t &final_res,int final_path[])
{
    cont++;
    stack<int> camino; 
    stack<int> lvl;
    stack<double_t> c_b;
    stack<double_t> c_w;
    stack<double_t> f_res;
    f_res.push(final_res) ;
    c_w.push(curr_weight);
    lvl.push(level);
    c_b.push(curr_bound);
    camino.push(0);


    while(!camino.empty()){
        level = lvl.top();
        cout << " level: " << level << endl;
        curr_weight = c_w.top();
        //curr_bound = c_b.top();
        final_res = f_res.top();

        f_res.pop();
       // c_b.pop();
        c_w.pop();
        lvl.pop();
        camino.pop();
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
        }
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

        for (auto it:good_branches)
        {
            double_t temp = curr_bound;
            curr_weight = it.first;
            int i = it.second;
            if (curr_bound > curr_weight){
               // cout << "entro" << endl;
                curr_path[level] = i;
                cout << "curr path:" <<  curr_path[i] << endl;

                visited[i] = true;
                camino.push(i);
                lvl.push(level+1);
                //c_b.push(curr_bound);
                c_w.push(curr_weight);
                f_res.push(final_res);
                //TSPRec(adj,n, curr_bound, curr_weight, level+1, curr_path,visited,final_res,final_path);
            }
            curr_weight -= adj[curr_path[level-1]][i];
            memset(visited, false, n);
            for (int j=0; j<=level-1; j++)
                visited[curr_path[j]] = true;
        }


    }



    /*if (level==n)
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
    //sort(good_branches.begin(),good_branches.end());
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

    }*/
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

int main(){
    vector<vector<double>> adj;

    double_t graph[V][V] ;
    auto data = getData("data/matrix_distancia.txt","data/matrix_tiempo.txt",10);
    adj = data.second;
    //vector<string> names = data.first;
    //auto adj = data.second;
    //for(int i=0;i<V;i++){
    //    for(int j = 0;j<V;j++){
    //        graph[i][j] = adj[i][j];
    //        //cout<<graph[i][j]<<" ";
    //    }//cout<<endl;
    //}
    //int s = 0;
    //auto shortest = travllingSalesmanProblem(graph, s);
    //int temp = 0;
    //double_t costo = 0;
    //for(int i=0;i<shortest.size();i++ ){
    //    int it = shortest[i];
    //    costo+=graph[temp][it];
    //    temp = it;
    //    cout<< it<<" ";
    //}
    //cout<<endl; 
    //costo+= graph[temp][0];
    //cout<<"Reference minimum cost:"<<costo<<endl;
    cout << "*Our algorithm: \n";

    int final_path[V+1];
    bool visited[V];
    double_t final_res = INT_MAX;
    TSP(adj,V,visited,final_res,final_path);
    

    double_t costo_real=0;
    printf("Minimum cost : %f\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=V; i++){
        printf("%d ", final_path[i]);
        //if (i>0)costo_real+=graph[final_path[i-1]][final_path[i]] ;
    }
    cout << endl;
        
    //cout<<"\nReal cost: "<<costo_real<<endl;

    return 0;
}