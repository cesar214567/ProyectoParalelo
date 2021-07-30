#include<bits/stdc++.h>

using namespace std;
#define pi 3.14159265358979323846

double toRad(double degree) {
    return degree/180 * pi;
}

double calculateDistance(double lat1, double long1, double lat2, double long2){
    double dist;
    dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(long1 - long2));
    dist = acos(dist);
    dist = 6371 * dist;
    return dist;
}


void createdb(){
    fstream file;
    vector<pair<double_t,double_t>> datos;
    vector <string> names;
    file.open("data/nodos.txt", ios::in);
    string name, lng ,lat;
    while (!file.eof()){
        file >> name;
        file >> lng;
        file >> lat;
        names.push_back(name);
        cout << lng << endl;
        cout << lat << endl;
        auto pr = pair<double_t,double_t>(stod(lng),stod(lat));
        datos.push_back(pr);
    }
    file.close();
    ofstream output("matrix_tiempo.txt");
    for(int i=0; i< datos.size(); i++){
        output << names[i];
        for(int j = 0; j < datos.size(); j++){
            output << " ";
            auto s = calculateDistance(datos[i].first, datos[i].second, datos[j].first, datos[j].second);
            cout << s << endl;
            output << to_string(s);
        }
        output << '\n';
    }
    output.close();
}


pair<vector<string>,vector<vector<double_t>>> getData(string filename, string filename2,int n){
    fstream file_distance(filename);
    fstream file_time(filename2);
    string name;
    double_t temp;
    double_t temp2;   
    vector<string> names;
    vector<vector<double_t>>data; 
    
    for(int i=0;i<n;i++){
        file_distance>>name;
        file_time >> name;
        vector<double_t> sub_data;
        for(int j=0;j<n;j++){
            file_distance >>temp;
            file_time >> temp2;
            sub_data.push_back((temp+temp2)/2.0);
        }    
        data.push_back(sub_data);
        names.push_back(name);
    }
    return {names,data};
}

vector<vector<double>> inputData(int n){
    double lat, lng;
    vector<vector<double>> matrix;
    for(int i = 0; i < n; i++)
        matrix.emplace_back(vector<double>(n));

    vector<pair<double,double>> datos; 
    double time_per_km = 60;
    cout << "Ingrese velocidad(Km/h): ";
    cin >> time_per_km;

    for(int i = 0; i < n; i++){
        cout << "Ubicacion " << i+1 << endl;
        cout << "Ingrese Longitud: "; 
        cin >> lng;
        cout << "Ingrese Latitud: "; 
        cin >> lat;
        datos.push_back(pair<double_t,double_t>(lng,lat));
    }

    const double km_minute= time_per_km/60;
    for(int i=0; i< datos.size(); i++){
        for(int j = 0; j < datos.size(); j++){
            auto dist = calculateDistance(datos[i].first, datos[i].second, datos[j].first, datos[j].second);
            matrix[i][j] = (dist + dist/km_minute)/2;
        }
    }
    
    return matrix;
}

