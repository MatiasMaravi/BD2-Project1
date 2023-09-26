#include <iostream>
#include "sequential_file.hpp"

/*
template <class T, typename TK>
SequentialFile<T, TK>::SequentialFile(string filename1, string filename2, 
                    std::function<bool(const T &, const T &)> less, 
                    std::function<bool(const T &, const T &)> greater,
                    std::function<bool(const T &, const T & )> equal,
                    std::function<bool(const T &, const TK &)> equal_key,
                    std::function<bool(const T &, const TK &)> less_key,
                    std::function<bool(const T &, const TK &)> greater_key) {
    this->datos = filename1;
    this->auxiliar = filename2;
    this->less = less;
    this->greater = greater;
    this->equal = equal;
    this->equal_key = equal_key;
    this->less_key = less_key;
    this->greater_key = greater_key;
}
*/
int main() {

    //Key ciclo
    SequentialFile<Record, int> file("datos4.dat", "auxiliar4.dat",
                []( Record const&a, Record const&b) { return a.player_id < b.player_id;},
                []( Record const&a,  Record const&b) { return a.player_id > b.player_id;},
                []( Record const&a,  Record const&b) { return a.player_id == b.player_id;},
                []( Record const&a,  int const&b) { return a.player_id == b;},
                []( Record const&a,  int const&b) { return a.player_id < b;},
                []( Record const&a,  int const&b) { return a.player_id > b;}
                );


    Record record;
    record.setData(1, "Abel", 100, 20, "Barcelona", "Espana");
    file.insert(record);
    record.setData(2, "Beto", 200, 21, "Real Madrid", "Espana");
    file.insert(record);
    //seguir...
    
    cout << "Datos.dat" << endl;
    fstream file1("datos.dat", ios::app | ios::in | ios::binary);
    Record cabecera;
    file1.seekg(0, ios::beg);
    file1.read((char *)&cabecera, sizeof(cabecera));
    cout << cabecera.next << " " << cabecera.archivo << endl;
    Record current;
    file1.read((char *)&current, sizeof(current));
    while (!file1.eof()) {
        current.showData();
        file1.read((char *)&current, sizeof(current));
    }

    cout << endl;

    cout << "Auxiliar.dat" << endl;
    fstream file2("auxiliar.dat", ios::app | ios::in | ios::binary);
    file2.seekg(0, ios::beg);
    file2.read((char *)&current, sizeof(current));
    while (!file2.eof()) {
        current.showData();
        file2.read((char *)&current, sizeof(current));
    }

    // cout << endl;
    // cout << "Busqueda por rango:" << endl;

    // vector<Record> result = file.range_search(5, 6);
    // for (auto i : result) i.showData();

    // cout << "Busqueda por llave:\n";
    // Record* recordP = file.search("Abel");
    // recordP->showData();
    
    // cout << "Llave existente:\n";
    // recordP = file.search("Jorge");
    // if (recordP) recordP->showData();
    // else cout << "No existe este registro\n";

    // cout << "Llave inexistente:\n";
    // recordP = file.search("Alejo");
    // if (recordP) recordP->showData();
    // else cout << "No existe este registro\n\n";

    // cout << "ReadRecord:\n";
    // file.readRecord(1,'d').showData();

    // cout << "Remove:\n";
    // if (file.remove("Abel")) cout << "Se elimino Abel\n";
    // else cout << "No se elimino Abel\n";

    // if (file.remove("Jorge")) cout << "Se elimino Jorge\n";
    // else cout << "No se elimino Jorge\n";
    cout << "Reorganizar\n:";
//    vector<Record> registrosOrdenados = file.reorganizar();
//    for ( Record& registro : registrosOrdenados) {
//        registro.showData();
//    }
    file.reorganizar();
    return 0;
}
