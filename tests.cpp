#include "tsp2.cpp"

class Test{
    private:
        int n;
        int **adj;

    void init(vector<vector<int>> vec){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                adj[i][j] = vec[i][j];
            }
        }
    }
    void test1(){
        
    }
    void test2(){
        auto pair = getData("nodos.txt",10);
        vector<string> names = pair.first;
        vector<vector<int>> data = pair.second; 
        int final_path[n+1];
        bool visited[n];
        int final_res = INT_MAX;
        TSP(adj,n,visited,final_res,final_path);
    }
    public:
    Test(){
        adj = new int*[n];
        for(int i=0;i<n;i++){
            adj[i] = new int[n];
        }
    }

    void runTests(){
        
    }
    
    void runMaps(){
        
    }

    void runAll(){
        
    }
};