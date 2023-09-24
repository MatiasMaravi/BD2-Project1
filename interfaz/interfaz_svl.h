//
// Created by JLeandroJM on 24/09/23.
//

#ifndef BD2_PROJECT1_INTERFAZ_SVL_H
#define BD2_PROJECT1_INTERFAZ_SVL_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "../AVLFile/avl_file.hpp"

void insertar_avl(const char* nombre_archivo){
    std::ifstream archivo(nombre_archivo);

    if (!archivo.is_open()) throw std::runtime_error("No se pudo abrir el archivo.");
    std::string primeraLinea;
    std::getline(archivo, primeraLinea);


    std::string linea;
    AVLFile<Record_avl,string> avl("data.dat",
                                []( Record_avl const&a, Record_avl const&b) { return a.player_id < b.player_id;}, //less
                                []( Record_avl const&a, Record_avl const&b) { return a.player_id > b.player_id;}, //greater
                                []( Record_avl const&a, int const&b) { return a.player_id == b;}, //equal_key
                                []( Record_avl const&a, int const&b) { return a.player_id < b;}, //less_key
                                []( Record_avl const&a, int const&b) { return a.player_id > b;}, //greater_key
                                []( Record_avl const&a) { return a.player_id;} //get_key
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

        Record_avl r1;

        player_id=stoi(fila[0]);

        strcpy(short_name, fila[1].c_str());
        value_eur=stoi(fila[2]);
        age= stoi(fila[3]);
        strcpy(club_name, fila[4].c_str());
        strcpy(nationality_name, fila[5].c_str());

        r1.setData(player_id,short_name,value_eur,age,club_name,nationality_name);

        avl.insert(r1);


    }

    archivo.close();


}


#endif //BD2_PROJECT1_INTERFAZ_SVL_H
