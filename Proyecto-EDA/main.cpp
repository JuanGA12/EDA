#include <iostream>
#include "Rtree/Rtree.h"
#include <chrono>
#include <ctime>
#include <numeric>
#include <string>
#include <functional>
int main() {
    using namespace std::chrono;

// After function call

    csvReader Lectura;

    auto contenedor = Lectura.leer_Barrios("Barrios.csv",2);

    Rtree Arbol;

    for(int i=0; i < contenedor.size(); i++) Arbol.insert(contenedor[i],i);

//-73.924911499023400	40.768489837646500
    vector<double> sdd;
    for(int i = 0; i < 10000;i++){
        auto start = high_resolution_clock::now();
        auto searchResult = Arbol.search({-73.924911499023400, 40.768489837646500});
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        sdd.push_back(duration.count()/1e6);
    }
    double acc=0;
    for(auto i:sdd) acc+=i;
    //cout<<acc/sdd.size();

    auto start = high_resolution_clock::now();
    auto searchResult = Arbol.search({-73.98626270358606, 40.6862135260153});
/*
    for(int i = 0; i < Barrios.size();i++){
        cout << i << " " << Barrios[i].Nombre_Barrio << endl;
    }
*/

    //40.6862135260153, -73.98626270358606
   if(!searchResult.Nombre_Barrio.empty()){
        cout<<"El punto -73.98626270358606, 40.6862135260153 se encuentra en "<<searchResult.Nombre_Barrio;
   }else cout<<"No se encontró barrio";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << duration.count()/1e6<<" Seconds" << endl;


    return 0;
}
