/*
#include "extendible_hashing.h"
int main(){
    
    DynamicHash dh("buckets.dat","indices.dat");

    Record r1(1,"leo",3);
    Record r2(2,"juan",3);
    Record r3(3,"pedro",3);
    Record r4(4,"maria",3);
    Record r5(5,"jose",3);
    Record r6(6,"luis",3);
    Record r7(10,"luis",3);
    Record r8(15,"luis",3);
    Record r9(20,"luis",3);
    Record r10(25,"luis",3);
    Record r11(23,"luis",3);
    Record r12(24,"luis",3);
    Record r13(12,"luis",3);
    Record r14(13,"luis",3);
    Record r15(53,"luis",3);
    Record r16(54,"luis",3);
    Record r17(42,"luis",3);
    Record r18(102,"luis",3);
    Record r19(103,"luis",3);
    Record r20(1130,"luis",3);
    Record r21(2021,"luis",3);
    Record r22(2022,"luis",3);
    Record r23(2023,"luis",3);
    Record r24(3054,"luis",3);

    
    dh.add(r1);
    dh.add(r2);
    dh.add(r3);
    dh.add(r4);
    dh.add(r5);
    dh.add(r6);
    dh.add(r7);
    dh.add(r8);
    dh.add(r9);
    dh.add(r10);
    dh.add(r11);
    dh.add(r12);
    dh.add(r13);
    dh.add(r14);
    dh.add(r15);
    dh.add(r16);
    dh.add(r17);
    dh.add(r18);
    dh.add(r19);
    dh.add(r20);
    dh.add(r21);
    dh.add(r22);
    dh.add(r23);
    dh.add(r24);



    Record r100= dh.search(25);
    r100.print();
   
*/    
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
    Record_sequential cabecera;
    file1.seekg(0, ios::beg);
    file1.read((char *)&cabecera, sizeof(cabecera));
    cout << cabecera.next << " " << cabecera.archivo << endl;
    Record_sequential current;
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
// template <typename T>
// void print_range_sequential(T key = "name"){
//     if(key == "name"){
//         cout << "Busqueda por rango:" << endl;
//         SequentialFile<Record_sequential, string> file("datos.dat", "auxiliar.dat",
//                 []( Record_sequential const&a, Record_sequential const&b) { return strcmp(a.name,b.name) < 0 ;},
//                 []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.name,b.name) > 0 ;},
//                 []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.name,b.name) == 0 ;},
//                 []( Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) == 0 ;},
//                 []( Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) < 0 ;},
//                 []( Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) > 0 ;}
//                 );

//         vector<Record_sequential> result = file.range_search("Carlos", "Saulo");
//         for (auto i : result) i.showData();

//         cout << "Busqueda por llave:\n";
//         Record_sequential* recordP = file.search("Abel");
//         if (recordP) recordP->showData();
//         else cout << "No existe este registro\n";
        
//         cout << "Llave existente:\n";
//         recordP = file.search("Jorge");
//         if (recordP) recordP->showData();
//         else cout << "No existe este registro\n";

//         cout << "Llave inexistente:\n";
//         recordP = file.search("Alejo");
//         if (recordP) recordP->showData();
//         else cout << "No existe este registro\n\n";

//         cout << "ReadRecord:\n";
//         file.readRecord(1,'d').showData();
//     }else{
//         cout<<"No implementado"<<endl;
//     }
    

// }
int main(){
    Scanner scanner("create table Customer from file \"archive/alumnos.csv\" using index sequential(id)");
    // Scanner scanner("select * from Customer where name = Jorge");
    // // Scanner scanner("select * from Customer where NAME = Juan");
    // // Scanner scanner("select * from Customer where ALTURA between 75 and 100");
    // // Scanner scanner("insert into Customer values (72790028, Juan, 123456789)");
    // // Scanner scanner("create table Customer from file \"data.csv\" using index avl(NAME)");

    Parser parser(&scanner);
    if(!parser.parse()) cout << "Parse error" << endl;
    // print_datos_sequential("Customer.dat");
    Scanner scanner2("select * from Customer where id = 9");
    Parser parser2(&scanner2);
    if(!parser2.parse()) cout << "Parse error" << endl;
    return 0;
}