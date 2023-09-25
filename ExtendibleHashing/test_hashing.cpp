
#include "extendible_hashing.hpp"
#include<fstream> 
#include <iostream>
#include <sstream>
using namespace std;

unsigned long hash_int(int key){
    return key%(1ULL<<D);
}

unsigned long hash_string(const std::string& str) {
    unsigned long hash = 5381;
    
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    
    return hash_int(hash);
}



int main() {
    std::ifstream archivo("../CSV/datos_10.csv"); // Abre el archivo CSV
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    std::string primeraLinea;
    std::getline(archivo, primeraLinea);


    std::string linea;
    std::vector<std::vector<std::string>> datos; // Matriz para almacenar los datos CSV

    int contador=0;
    int num_linea=0;
    //Key = ID
    // DynamicHash<Record,int> dh1("buckets.dat","indices.dat",
    //                             [](const Record& r){return r.id;},
    //                             [](const int& value){return hash_int(value);},
    //                             [](const Record& r, const int& value){return r.id==value;},
    //                             226);
    //Key = name
    DynamicHash<Record,string> dh("buckets.dat","indices.dat",
                                [](const Record& r){return r.name;},
                                [](const string& value){return hash_string(value);},
                                [](const Record& r, const string& value){return r.name==value;},
                                226);
    
    
    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string token;
        std::vector<std::string> fila;
        
            while (std::getline(ss, token, ',')) {
                // Verificar si el token está vacío o contiene solo comas
                    fila.push_back(token);
            }

            // Agregar la fila solo si contiene al menos un campo no vacío

                datos.push_back(fila);


                Record r1;
                r1.id=stoi(fila[0]);
                strcpy(r1.name,fila[1].c_str());
                r1.value=stoi(fila[2]);
                r1.age=stoi(fila[3]);
                strcpy(r1.fecha,fila[4].c_str());
                strcpy(r1.nacionalidad,fila[9].c_str());
                dh.add(r1);

    }

    // Cerrar el archivo
    archivo.close();

    // Imprimir los datos leídos
    for (const auto& fila : datos) {
        for (const auto& elemento : fila) {
            std::cout << elemento << "\t";
        }
        std::cout << std::endl;
    }

    // cout<<"---------------------"<<endl;
    // cout<<"Search"<<endl;
    // Record r100= dh.search("Poland");
    // r100.print();

    // cout<<"---------------------"<<endl;
    // cout<<"insert: "<<endl;    
    // Record r1(1,"Juan",1,1,"01/01/2001",170,"Peru");
    // dh.add(r1);
    cout<<"---------------------"<<endl;
    cout<<"Search"<<endl;
    Record r100= dh.search("S. Camara");
    r100.print();
    return 0;
}
