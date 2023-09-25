#include "../src/Sequential_file.hpp"
#include "../src/Avl_file.hpp"
#include "../src/DynamicHash_file.hpp"
#include "sstream"
#include "Scanner.hpp"
#include <vector>
template<typename T>
void leer_record(string line, T &record){
    stringstream ss(line);
    string campo;
    getline(ss, campo, ',');
    int id = stoi(campo);
    getline(ss, campo, ',');
    string name = campo;
    getline(ss, campo, ',');
    int value = stoi(campo);
    getline(ss, campo, ',');
    int age = stoi(campo);
    getline(ss, campo, ',');
    string fecha = campo;
    getline(ss, campo, ',');
    int tamaño = stoi(campo);
    getline(ss, campo, ',');
    getline(ss, campo, ',');
    string club = campo;
    getline(ss, campo, ',');
    getline(ss, campo, ',');
    string nacionalidad = campo;
    getline(ss, campo, ',');
    getline(ss, campo, ',');
    getline(ss, campo, ',');
    record.setData(id,name,value,age,fecha,tamaño,club,nacionalidad);
}
//Sequential
void create_sequential(string key_table, string table_name, ifstream &file_){
    cout<<"Creando indice secuencial con key "<<key_table<<endl;
    Record_sequential record;
    
    if(key_table == "id"){
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return a.id < b.id ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.id > b.id ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.id == b.id ;},
                []( Record_sequential const&a,  int const&b) { return a.id == b ;},
                []( Record_sequential const&a,  int const&b) { return a.id < b ;},
                []( Record_sequential const&a,  int const&b) { return a.id > b ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "name"){
        SequentialFile<Record_sequential, string> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return strcmp(a.name,b.name) < 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.name,b.name) > 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.name,b.name) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) < 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) > 0 ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "value"){
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return a.value < b.value ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.value > b.value ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.value == b.value ;},
                []( Record_sequential const&a,  int const&b) { return a.value == b ;},
                []( Record_sequential const&a,  int const&b) { return a.value < b ;},
                []( Record_sequential const&a,  int const&b) { return a.value > b ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "age"){
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return a.age < b.age ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.age > b.age ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.age == b.age ;},
                []( Record_sequential const&a,  int const&b) { return a.age == b ;},
                []( Record_sequential const&a,  int const&b) { return a.age < b ;},
                []( Record_sequential const&a,  int const&b) { return a.age > b ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "fecha"){
        SequentialFile<Record_sequential, string> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return strcmp(a.fecha,b.fecha) < 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.fecha,b.fecha) > 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.fecha,b.fecha) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) < 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) > 0 ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "tamaño"){
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return a.tamaño < b.tamaño ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.tamaño > b.tamaño ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.tamaño == b.tamaño ;},
                []( Record_sequential const&a,  int const&b) { return a.tamaño == b ;},
                []( Record_sequential const&a,  int const&b) { return a.tamaño < b ;},
                []( Record_sequential const&a,  int const&b) { return a.tamaño > b ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "club"){
        SequentialFile<Record_sequential, string> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return strcmp(a.club,b.club) < 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.club,b.club) > 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.club,b.club) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) < 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) > 0 ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "nacionalidad"){
        SequentialFile<Record_sequential, string> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) < 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) > 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) < 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) > 0 ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }else{
        cout<<"Key no encontrado, id por defecto"<<endl;
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return a.id < b.id ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.id > b.id ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.id == b.id ;},
                []( Record_sequential const&a,  int const&b) { return a.id == b ;},
                []( Record_sequential const&a,  int const&b) { return a.id < b ;},
                []( Record_sequential const&a,  int const&b) { return a.id > b ;}
                );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_sequential>(line, record);
            file.insert(record);
        }
        file_.close();
    }

}
void search_sequential(string key_table, string table_name, string cadena){
    cout<<"Buscando en la tabla "<<table_name<<" con key "<<key_table<< " donde "<<key_table<<" = "<<cadena<<endl;
    Record_sequential* record;
    if(key_table == "id"){
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.id < b.id ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.id > b.id ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.id == b.id ;},
                [](Record_sequential const&a,  int const&b) { return a.id == b ;},
                [](Record_sequential const&a,  int const&b) { return a.id < b ;},
                [](Record_sequential const&a,  int const&b) { return a.id > b ;}
                );
                record = file.search(stoi(cadena));
    }else if(key_table == "name"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.name,b.name) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.name,b.name) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.name,b.name) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) > 0 ;}
                );
                record = file.search(cadena);
    }else if(key_table == "value"){
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.value < b.value ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.value > b.value ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.value == b.value ;},
                [](Record_sequential const&a,  int const&b) { return a.value == b ;},
                [](Record_sequential const&a,  int const&b) { return a.value < b ;},
                [](Record_sequential const&a,  int const&b) { return a.value > b ;}
                );
                record = file.search(stoi(cadena));
    }else if(key_table == "age"){
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.age < b.age ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.age > b.age ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.age == b.age ;},
                [](Record_sequential const&a,  int const&b) { return a.age == b ;},
                [](Record_sequential const&a,  int const&b) { return a.age < b ;},
                [](Record_sequential const&a,  int const&b) { return a.age > b ;}
                );
                record = file.search(stoi(cadena));
    }else if(key_table == "fecha"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.fecha,b.fecha) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.fecha,b.fecha) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.fecha,b.fecha) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) > 0 ;}
                );
                record = file.search(cadena);
    }else if(key_table == "tamaño"){
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.tamaño < b.tamaño ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.tamaño > b.tamaño ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.tamaño == b.tamaño ;},
                [](Record_sequential const&a,  int const&b) { return a.tamaño == b ;},
                [](Record_sequential const&a,  int const&b) { return a.tamaño < b ;},
                [](Record_sequential const&a,  int const&b) { return a.tamaño > b ;}
                );
                record = file.search(stoi(cadena));
    }else if(key_table == "club"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.club,b.club) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.club,b.club) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.club,b.club) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) > 0 ;}
                );
                record = file.search(cadena);
    }else if(key_table == "nacionalidad"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) > 0 ;}
                );
                record = file.search(cadena);
    }else{
        cout<<"Key no encontrado, Error"<<endl;
        return;
    }
    if(record) record->print();
    else
        cout<<"No existe este registro"<<endl;
}
void search_sequential_range(string key_table, string table_name, string cadena, string cadena_2){
    cout<<"Buscando en la tabla "<<table_name<<" con key "<<key_table<< " desde "<<cadena<<" hasta "<<cadena_2<<endl;
    vector<Record_sequential> records;
    if(key_table == "id"){
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.id < b.id ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.id > b.id ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.id == b.id ;},
                [](Record_sequential const&a,  int const&b) { return a.id == b ;},
                [](Record_sequential const&a,  int const&b) { return a.id < b ;},
                [](Record_sequential const&a,  int const&b) { return a.id > b ;}
                );
                records = file.range_search(stoi(cadena), stoi(cadena_2));
    }else if(key_table == "name"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.name,b.name) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.name,b.name) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.name,b.name) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.name,b.c_str()) > 0 ;}
                );
                records = file.range_search(cadena, cadena_2);
    }else if(key_table == "value"){
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.value < b.value ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.value > b.value ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.value == b.value ;},
                [](Record_sequential const&a,  int const&b) { return a.value == b ;},
                [](Record_sequential const&a,  int const&b) { return a.value < b ;},
                [](Record_sequential const&a,  int const&b) { return a.value > b ;}
                );
                records = file.range_search(stoi(cadena), stoi(cadena_2));
    }else if(key_table == "age"){
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.age < b.age ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.age > b.age ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.age == b.age ;},
                [](Record_sequential const&a,  int const&b) { return a.age == b ;},
                [](Record_sequential const&a,  int const&b) { return a.age < b ;},
                [](Record_sequential const&a,  int const&b) { return a.age > b ;}
                );
                records = file.range_search(stoi(cadena), stoi(cadena_2));
    }else if(key_table == "fecha"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.fecha,b.fecha) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.fecha,b.fecha) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.fecha,b.fecha) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.fecha,b.c_str()) > 0 ;}
                );
                records = file.range_search(cadena, cadena_2);
    }else if(key_table == "tamaño"){
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.tamaño < b.tamaño ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.tamaño > b.tamaño ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.tamaño == b.tamaño ;},
                [](Record_sequential const&a,  int const&b) { return a.tamaño == b ;},
                [](Record_sequential const&a,  int const&b) { return a.tamaño < b ;},
                [](Record_sequential const&a,  int const&b) { return a.tamaño > b ;}
                );
                records = file.range_search(stoi(cadena), stoi(cadena_2));
    }else if(key_table == "club"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.club,b.club) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.club,b.club) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.club,b.club) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.club,b.c_str()) > 0 ;}
                );
                records = file.range_search(cadena, cadena_2);
    }else if(key_table == "nacionalidad"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.nacionalidad,b.nacionalidad) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.nacionalidad,b.c_str()) > 0 ;}
                );
                records = file.range_search(cadena, cadena_2);
    }else{
        cout<<"Key no encontrado, Error"<<endl;
        return;
    }
    for(auto i:records){
        i.print();
    }
}
//AVL
/*
void create_AVL(string key_table, string table_name, ifstream &file_){
    cout<<"Creando indice avl con key "<<key_table<<endl;
    Record_avl record;
    if(key_table == "id"){
        AVLFile<Record_avl,int> file(table_name+"_avl.dat",
                            []( Record_avl const&a, Record_avl const&b) { return a.id < b.id;}, //less
                            []( Record_avl const&a, Record_avl const&b) { return a.id > b.id;}, //greater
                            []( Record_avl const&a, int const&b) { return a.id == b;}, //equal_key
                            []( Record_avl const&a, int const&b) { return a.id < b;}, //less_key
                            []( Record_avl const&a, int const&b) { return a.id > b;}, //greater_key
                            []( Record_avl const&a) { return a.id;} //get_key
                            );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_avl>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "ciclo"){
        AVLFile<Record_avl,int> file(table_name+"_avl.dat",
                            []( Record_avl const&a, Record_avl const&b) { return a.ciclo < b.ciclo;}, //less
                            []( Record_avl const&a, Record_avl const&b) { return a.ciclo > b.ciclo;}, //greater
                            []( Record_avl const&a, int const&b) { return a.ciclo == b;}, //equal_key
                            []( Record_avl const&a, int const&b) { return a.ciclo < b;}, //less_key
                            []( Record_avl const&a, int const&b) { return a.ciclo > b;}, //greater_key
                            []( Record_avl const&a) { return a.ciclo;} //get_key
                            );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_avl>(line, record);
            file.insert(record);
        }
        file_.close();
    }else if(key_table == "name"){
        AVLFile<Record_avl,string> file(table_name+"_avl.dat",
                            []( Record_avl const&a, Record_avl const&b) { return strcmp(a.name,b.name) < 0;}, //less
                            []( Record_avl const&a, Record_avl const&b) { return strcmp(a.name,b.name) > 0;}, //greater
                            []( Record_avl const&a, string const&b) { return strcmp(a.name,b.c_str()) == 0;}, //equal_key
                            []( Record_avl const&a, string const&b) { return strcmp(a.name,b.c_str()) < 0;}, //less_key
                            []( Record_avl const&a, string const&b) { return strcmp(a.name,b.c_str()) > 0;}, //greater_key
                            []( Record_avl const&a) { return a.name;} //get_key
                            );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_avl>(line, record);
            file.insert(record);
        }
        file_.close();
    }
    else if(key_table == "surname"){
        AVLFile<Record_avl,string> file(table_name+"_avl.dat",
                            []( Record_avl const&a, Record_avl const&b) { return strcmp(a.surname,b.surname) < 0;}, //less
                            []( Record_avl const&a, Record_avl const&b) { return strcmp(a.surname,b.surname) > 0;}, //greater
                            []( Record_avl const&a, string const&b) { return strcmp(a.surname,b.c_str()) == 0;}, //equal_key
                            []( Record_avl const&a, string const&b) { return strcmp(a.surname,b.c_str()) < 0;}, //less_key
                            []( Record_avl const&a, string const&b) { return strcmp(a.surname,b.c_str()) > 0;}, //greater_key
                            []( Record_avl const&a) { return a.surname;} //get_key
                            );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_avl>(line, record);
            file.insert(record);
        }
        file_.close();
    }else{
        cout<<"Key no encontrado, id por defecto"<<endl;
        AVLFile<Record_avl,int> file(table_name+"_avl.dat",
                            []( Record_avl const&a, Record_avl const&b) { return a.id < b.id;}, //less
                            []( Record_avl const&a, Record_avl const&b) { return a.id > b.id;}, //greater
                            []( Record_avl const&a, int const&b) { return a.id == b;}, //equal_key
                            []( Record_avl const&a, int const&b) { return a.id < b;}, //less_key
                            []( Record_avl const&a, int const&b) { return a.id > b;}, //greater_key
                            []( Record_avl const&a) { return a.id;} //get_key
                            );
        string campo, line;
        while(getline(file_, line)){
            leer_record<Record_avl>(line, record);
            file.insert(record);
        }
        file_.close();
    }
}
//Hash
void create_hash(string key_table, string table_name, ifstream &file_){
    cout<<"Creando indice avl con key "<<key_table<<endl;
    Record_avl record;
}

*/