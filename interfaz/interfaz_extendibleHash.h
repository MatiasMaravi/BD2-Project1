//
// Created by JLeandroJM on 24/09/23.
//

#ifndef BD2_PROJECT1_INTERFAZ_EXTENDIBLEHASH_H
#define BD2_PROJECT1_INTERFAZ_EXTENDIBLEHASH_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "../ExtendibleHashing/extendible_hashing.hpp"

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

void insertar_hash(const char* nombre_archivo){
    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open()) throw std::runtime_error("No se pudo abrir el archivo.");
    std::string primeraLinea;
    std::getline(archivo, primeraLinea);


    std::string linea;
    DynamicHash<Record_hash,int> hash("buckets_hash.dat","indices_hash.dat",
                                      [](const Record_hash& r){return r.player_id;},
                                      [](const int& value){return hash_int(value);},
                                      [](const Record_hash& r, const int& value){return r.player_id==value;},
                                      226//get_key
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

        Record_hash r1;

        player_id=stoi(fila[0]);
        strcpy(short_name, fila[1].c_str());
        value_eur=stoi(fila[2]);
        age= stoi(fila[3]);
        strcpy(club_name, fila[4].c_str());
        strcpy(nationality_name, fila[5].c_str());

        r1.setData(player_id,short_name,value_eur,age,club_name,nationality_name);

        hash.add(r1);


    }

    archivo.close();


}

vector<Record_hash> buscar_hash(int key){
    DynamicHash<Record_hash, int>& instancia = DynamicHash<Record_hash, int>::getInstance(
            "buckets_hash.dat","indices_hash.dat",

            [](const Record_hash& r){return r.player_id;},
            [](const int& value){return hash_int(value);},
            [](const Record_hash& r, const int& value){return r.player_id==value;},
            226//get_key

    );

    return instancia.search(key);

}

#endif //BD2_PROJECT1_INTERFAZ_EXTENDIBLEHASH_H
