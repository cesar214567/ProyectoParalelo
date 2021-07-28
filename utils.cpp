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
    file.open("nodos.txt", ios::in);
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
    ofstream output("matrix.txt");
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