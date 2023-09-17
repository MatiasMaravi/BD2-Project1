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

void print_range_sequential(){
    cout << "Busqueda por rango:" << endl;
    SequentialFile<string> file("Customer.dat", "auxiliar.dat");

    vector<Record> result = file.range_search("Carlos", "Saulo");
    for (auto i : result) i.showData();

    cout << "Busqueda por llave:\n";
    Record* recordP = file.search("Abel");
    
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

    // print_datos_sequential("Customer.dat");

    // string s;
    // cin>>s;
    Scanner scanner("create table Customer from file \"archive/alumnos.csv\" using index sequential(name)");
    // // Scanner scanner("select * from Customer where DNI = 72790028");
    // // Scanner scanner("select * from Customer where NAME = Juan");
    // // Scanner scanner("select * from Customer where ALTURA between 75 and 100");
    // // Scanner scanner("insert into Customer values (72790028, Juan, 123456789)");
    // // Scanner scanner("create table Customer from file \"data.csv\" using index avl(NAME)");

    // Parser parser(&scanner);
    // if(!parser.parse()) cout << "Parse error" << endl;

    return 0;
}