#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cstring>
#include "../Record.h"
#include "sequential_file.hpp"



int main() {

    SequentialFile<Record, int> secuential_file("datos2.dat", "auxiliar2.dat",
                                     []( Record const&a, Record const&b) { return a.age < b.age;},
                                     []( Record const&a,  Record const&b) { return a.age > b.age;},
                                     []( Record const&a,  Record const&b) { return a.age == b.age;},
                                     []( Record const&a,  int const&b) { return a.age == b;},
                                     []( Record const&a,  int const&b) { return a.age < b;},
                                     []( Record const&a,  int const&b) { return a.age > b;}
    );

    std::ifstream file("../CSV/datos_10000.csv");

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo CSV." << std::endl;
        return 1;
    }

    std::string line;
    Record record;
    std::getline(file, line);






    while (std::getline(file, line)) {
        std::istringstream iss(line);


        std::string part;


        if (std::getline(iss, part, ',')) {

            record.player_id = std::stoi(part);

        }


        if (std::getline(iss, part, ',')) {
            std::strncpy(record.short_name, part.c_str(), sizeof(record.short_name));
            record.short_name[sizeof(record.short_name) - 1] = '\0';

        }


        if (std::getline(iss, part, ',')) {
            record.value_eur = std::stoi(part);
        }


        if (std::getline(iss, part, ',')) {
            record.age = std::stoi(part);
        }


        if (std::getline(iss, part, ',')) {
            std::strncpy(record.club_name, part.c_str(), sizeof(record.club_name));
            record.club_name[sizeof(record.club_name) - 1] = '\0';
        }

        if (std::getline(iss, part, ',')) {
            std::strncpy(record.nationality_name, part.c_str(), sizeof(record.nationality_name));
            record.nationality_name[sizeof(record.nationality_name) - 1] = '\0';
        }


        secuential_file.insert(record);
       // cout<<secuential_file.size_datos()<<endl;
       // cout<<line<<endl;
        record.showData();
    }

    cout << "Reorganizar\n:";
   // vector<Record> registrosOrdenados = secuential_file.reorganizar();
//    for ( Record& registro : registrosOrdenados) {
//        registro.showData();
//    }
cout<<secuential_file.size_datos();

    file.close();


    return 0;
}
