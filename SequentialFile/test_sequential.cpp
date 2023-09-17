#include <iostream>
#include "sequential_file.hpp"


int main() {
    SequentialFile<string> file("datos.dat", "auxiliar.dat");
    // Record record;
    // record.setData(1, "Andres", "Perez", 1);
    // file.insert(record);
    // record.setData(2, "Carlos", "Perez", 1);
    // file.insert(record);
    // record.setData(3, "Cintia", "Perez", 1);
    // file.insert(record);
    // record.setData(4, "Jorge", "Perez", 1);
    // file.insert(record);
    // record.setData(5, "Josimar", "Perez", 1);
    // file.insert(record);
    // record.setData(6, "Mabel", "Perez", 1);
    // file.insert(record);
    // record.setData(7, "Saulo", "Perez", 1);
    // file.insert(record);
    // record.setData(8, "Gabriel", "Perez", 1);
    // file.insert(record);
    // record.setData(9, "Gonzalo", "Perez", 1);
    // file.insert(record);
    // record.setData(10, "Maria", "Perez", 1);
    // file.insert(record);
    // record.setData(11, "Abel", "Perez", 1);
    // file.insert(record);

    cout << "Datos.dat" << endl;
    fstream file1("datos.dat", ios::app | ios::in | ios::binary);
    Record cabecera;
    file1.seekg(0, ios::beg);
    file1.read((char *)&cabecera, sizeof(cabecera));
    cout << cabecera.next << " " << cabecera.archivo << endl;
    Record current;
    file1.read((char *)&current, sizeof(current));
    while (!file1.eof()) {
        cout << current.id << " " << current.name << " " << current.surname << " " << current.ciclo << " " << current.next << " " << current.archivo << endl;
        file1.read((char *)&current, sizeof(current));
    }

    cout << endl;

    cout << "Auxiliar.dat" << endl;
    fstream file2("auxiliar.dat", ios::app | ios::in | ios::binary);
    file2.seekg(0, ios::beg);
    file2.read((char *)&current, sizeof(current));
    while (!file2.eof()) {
        cout << current.id << " " << current.name << " " << current.surname << " " << current.ciclo << " " << current.next << " " << current.archivo << endl;
        file2.read((char *)&current, sizeof(current));
    }

    cout << endl;
    // cout << "Busqueda por rango:" << endl;

    // vector<Record> result = file.range_search("Carlos", "Saulo");
    // for (auto i : result) i.showData();

    // cout << "Busqueda por llave:\n";
    // Record* recordP = file.search("Abel");
    
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

    cout << "Remove:\n";
    // if (file.remove("Abel")) cout << "Se elimino Abel\n";
    // else cout << "No se elimino Abel\n";

    // if (file.remove("Jorge")) cout << "Se elimino Jorge\n";
    // else cout << "No se elimino Jorge\n";
    // cout << "Reorganizar\n:";
    // file.reorganizar();
    return 0;
}
