//
// Created by JLeandroJM on 24/09/23.
//

#ifndef BD2_PROJECT1_INTERFAZ_SEQUENTIAL_H
#define BD2_PROJECT1_INTERFAZ_SEQUENTIAL_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "../SequentialFile/sequential_file.hpp"

using namespace std;
void insertar_sequential(const char* nombre_archivo){
    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open()) throw std::runtime_error("No se pudo abrir el archivo.");
    std::string primeraLinea;
    std::getline(archivo, primeraLinea);


    std::string linea;

    SequentialFile<Record, int> secuential_file("buckets_seq.dat","indices_seq.dat",
                                                []( Record const&a, Record const&b) { return a.player_id < b.player_id;},
                                                []( Record const&a,  Record const&b) { return a.player_id > b.player_id;},
                                                []( Record const&a,  Record const&b) { return a.player_id == b.player_id;},
                                                []( Record const&a,  int const&b) { return a.player_id == b;},
                                                []( Record const&a,  int const&b) { return a.player_id < b;},
                                                []( Record const&a,  int const&b) { return a.player_id > b;}


    );


    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string token;
        std::vector<std::string> fila;
        int player_id;
        char short_name[50];
        int value_eur;
        int age;
        char club_name[50];
        char nationality_name[50];


        while (std::getline(ss, token, ',')) {
            // Verificar si el token está vacío o contiene solo comas
            fila.push_back(token);
        }

        Record r1;

        player_id=stoi(fila[0]);

        strcpy(short_name, fila[1].c_str());
        value_eur=stoi(fila[2]);
        age= stoi(fila[3]);
        strcpy(club_name, fila[4].c_str());
        strcpy(nationality_name, fila[5].c_str());

        r1.setData(player_id,short_name,value_eur,age,club_name,nationality_name);

        secuential_file.insert(r1);


    }

    archivo.close();
}

vector<Record> ordenar_sequential(){
    SequentialFile<Record, int>& instancia = SequentialFile<Record, int>::getInstance(
            "buckets_seq.dat","indices_seq.dat",
            []( Record const&a, Record const&b) { return a.player_id < b.player_id;},
            []( Record const&a,  Record const&b) { return a.player_id > b.player_id;},
            []( Record const&a,  Record const&b) { return a.player_id == b.player_id;},
            []( Record const&a,  int const&b) { return a.player_id == b;},
            []( Record const&a,  int const&b) { return a.player_id < b;},
            []( Record const&a,  int const&b) { return a.player_id > b;}

    );

    return instancia.reorganizar();

}

vector<Record> buscar_sequential(int key){
    SequentialFile<Record, int>& instancia = SequentialFile<Record, int>::getInstance(
            "buckets_seq.dat","indices_seq.dat",
            []( Record const&a, Record const&b) { return a.player_id < b.player_id;},
            []( Record const&a,  Record const&b) { return a.player_id > b.player_id;},
            []( Record const&a,  Record const&b) { return a.player_id == b.player_id;},
            []( Record const&a,  int const&b) { return a.player_id == b;},
            []( Record const&a,  int const&b) { return a.player_id < b;},
            []( Record const&a,  int const&b) { return a.player_id > b;}

    );

    return instancia.search(key);

}

vector<Record> buscar_range_sequential(int key1,int key2){
    SequentialFile<Record, int>& instancia = SequentialFile<Record, int>::getInstance(
            "buckets_seq.dat","indices_seq.dat",
            []( Record const&a, Record const&b) { return a.player_id < b.player_id;},
            []( Record const&a,  Record const&b) { return a.player_id > b.player_id;},
            []( Record const&a,  Record const&b) { return a.player_id == b.player_id;},
            []( Record const&a,  int const&b) { return a.player_id == b;},
            []( Record const&a,  int const&b) { return a.player_id < b;},
            []( Record const&a,  int const&b) { return a.player_id > b;}

    );

    return instancia.range_search(key1,key2);

}





#endif //BD2_PROJECT1_INTERFAZ_SEQUENTIAL_H
