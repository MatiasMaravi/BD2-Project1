#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "extendible_hashing.h"



void cargar_hash(){
    std::ifstream archivo("dataset.csv"); // Abre el archivo CSV
    if (!archivo.is_open()) throw std::runtime_error("No se pudo abrir el archivo.");

    std::string primeraLinea;
    std::getline(archivo, primeraLinea);


    std::string linea;

    DynamicHash dh("buckets.dat","indices.dat");
    
    
    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string token;
        std::vector<std::string> fila;
        

            while (std::getline(ss, token, ',')) {
                // Verificar si el token está vacío o contiene solo comas
                    fila.push_back(token);
            }

                Record r1;
                r1.codigo=stoi(fila[0]);
                r1.name=fila[1];
                r1.value=stoi(fila[2]);
                r1.age=stoi(fila[3]);
                dh.add(r1);
        
    }

    // Cerrar el archivo
    archivo.close();


}

int main() {
    std::ifstream archivo("dataset.csv"); // Abre el archivo CSV
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

    DynamicHash dh("buckets.dat","indices.dat");
    
    
    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string token;
        std::vector<std::string> fila;
        
        if(num_linea%2!=0){
            while (std::getline(ss, token, ',')) {
                // Verificar si el token está vacío o contiene solo comas
                    fila.push_back(token);
            }

            // Agregar la fila solo si contiene al menos un campo no vacío

                datos.push_back(fila);
                contador++;

                Record r1;
                r1.codigo=stoi(fila[0]);
                r1.name=fila[1];
                r1.value=stoi(fila[2]);
                r1.age=stoi(fila[3]);
                dh.add(r1);


            if (contador == 10) {
                break;
            }
        }
        num_linea++;
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

    cout<<"---------------------"<<endl;

    Record r100= dh.search(192985);
    r100.print();

    

    
    return 0;
}
