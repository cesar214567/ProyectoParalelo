
//#include "tests.cpp"
#include "test_random.cpp"

void exec_optimization(){
    cout << "Ingrese numero de ciudades: ";
    int n;
    cin >> n;
    auto adj = inputData(n);
    auto graph= adj;

    for(int i=0;i<n;i++){
        for(int j = 0;j<n;j++){
            graph[i][j] = adj[i][j];
        }
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

    
    for(int i=0;i<n;i++){
        for(int j = 0;j<n;j++){
            graph[i][j] = adj[i][j];
        }
    }


    cout << "*Our algorithm: \n";

    int final_path[n+1];
    bool visited[n];
    double_t final_res = INT_MAX;
    TSP(adj,n,visited,final_res,final_path);
    

    double_t costo_real=0;
    printf("Minimum cost : %f\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=n; i++){
        printf("%d ", final_path[i]);
        if (i>0)costo_real+=graph[final_path[i-1]][final_path[i]] ;
    }
        
    cout<<"\nReal cost: "<<costo_real<<endl;
}

int main(){
    exec_optimization();
}