#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser/Parser.hpp"
using namespace std;
//Solo valida si existe una key en la tabla
bool key_exist(string key, string line){
    int pos = line.find(key);
    if(pos == string::npos) return false;
    return true;
}
<<<<<<< HEAD
template <typename T>
void print_datos_sequential(string data_file){
    cout << data_file << endl;
    fstream file1(data_file, ios::app | ios::in | ios::binary);
    Record<T> cabecera;
    file1.seekg(0, ios::beg);
    file1.read((char *)&cabecera, sizeof(cabecera));
    cout << cabecera.next << " " << cabecera.archivo << endl;
    Record<T> current;
    file1.read((char *)&current, sizeof(current));
    while (!file1.eof()) {
        cout << current.id << " " << current.name << " " << current.surname << " " << current.ciclo << " " << current.next << " " << current.archivo << endl;
        file1.read((char *)&current, sizeof(current));
    }

=======

void print_datos_sequential(string data_file){
    cout << data_file << endl;
    fstream file1(data_file, ios::app | ios::in | ios::binary);
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

>>>>>>> 96a3ee9 (Todo arreglado, Create funcionando)
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
}
<<<<<<< HEAD
template <typename T>
=======

>>>>>>> 96a3ee9 (Todo arreglado, Create funcionando)
void print_range_sequential(){
    cout << "Busqueda por rango:" << endl;
    SequentialFile<string> file("Customer.dat", "auxiliar.dat");

<<<<<<< HEAD
    vector<Record<T>> result = file.range_search("Carlos", "Saulo");
    for (auto i : result) i.showData();

    cout << "Busqueda por llave:\n";
    Record<T>* recordP = file.search("Abel");
=======
    vector<Record> result = file.range_search("Carlos", "Saulo");
    for (auto i : result) i.showData();

    cout << "Busqueda por llave:\n";
    Record* recordP = file.search("Abel");
>>>>>>> 96a3ee9 (Todo arreglado, Create funcionando)
    if (recordP) recordP->showData();
    else cout << "No existe este registro\n";
    
    cout << "Llave existente:\n";
    recordP = file.search("Jorge");
    if (recordP) recordP->showData();
    else cout << "No existe este registro\n";

    cout << "Llave inexistente:\n";
    recordP = file.search("Alejo");
    if (recordP) recordP->showData();
    else cout << "No existe este registro\n\n";

    cout << "ReadRecord:\n";
    file.readRecord(1,'d').showData();

}
int main(){

<<<<<<< HEAD
    // print_datos_sequential("Customer.dat");
=======
    print_datos_sequential("Customer.dat");
>>>>>>> 96a3ee9 (Todo arreglado, Create funcionando)

    // string s;
    // cin>>s;
    // Scanner scanner("create table Customer from file \"archive/alumnos.csv\" using index sequential(name)");
<<<<<<< HEAD
    Scanner scanner("select * from Customer where name = Jorge");
=======
    // Scanner scanner("select * from Customer where name = Jorge");
>>>>>>> 96a3ee9 (Todo arreglado, Create funcionando)
    // // Scanner scanner("select * from Customer where NAME = Juan");
    // // Scanner scanner("select * from Customer where ALTURA between 75 and 100");
    // // Scanner scanner("insert into Customer values (72790028, Juan, 123456789)");
    // // Scanner scanner("create table Customer from file \"data.csv\" using index avl(NAME)");

<<<<<<< HEAD
    Parser parser(&scanner);
    if(!parser.parse()) cout << "Parse error" << endl;
=======
    // Parser parser(&scanner);
    // if(!parser.parse()) cout << "Parse error" << endl;
>>>>>>> 96a3ee9 (Todo arreglado, Create funcionando)

    return 0;
}