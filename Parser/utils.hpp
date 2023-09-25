#include "../src/Sequential_file.hpp"
#include "../src/Avl_file.hpp"
#include "../src/DynamicHash_file.hpp"
#include "sstream"
#include "Scanner.hpp"
template<typename T>
void leer_record(string line, T &record){
    stringstream ss(line);
    string campo;
    getline(ss, campo, ',');
    int id = stoi(campo);
    getline(ss, campo, ',');
    string name = campo;
    getline(ss, campo, ',');
    string surname = campo;
    getline(ss, campo, ',');
    int ciclo = stoi(campo);
    record.setData(id, name, surname, ciclo);
    
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
    }else if(key_table == "ciclo"){
        SequentialFile<Record_sequential, int> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return a.ciclo < b.ciclo ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.ciclo > b.ciclo ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return a.ciclo == b.ciclo ;},
                []( Record_sequential const&a,  int const&b) { return a.ciclo == b ;},
                []( Record_sequential const&a,  int const&b) { return a.ciclo < b ;},
                []( Record_sequential const&a,  int const&b) { return a.ciclo > b ;}
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
    }else if(key_table == "surname"){
        SequentialFile<Record_sequential, string> file(table_name + ".dat", "auxiliar.dat",
                []( Record_sequential const&a, Record_sequential const&b) { return strcmp(a.surname,b.surname) < 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.surname,b.surname) > 0 ;},
                []( Record_sequential const&a,  Record_sequential const&b) { return strcmp(a.surname,b.surname) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.surname,b.c_str()) == 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.surname,b.c_str()) < 0 ;},
                []( Record_sequential const&a,  string const&b) { return strcmp(a.surname,b.c_str()) > 0 ;}
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
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.id < b.id ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.id > b.id ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.id == b.id ;},
                [](Record_sequential const&a,  int const&b) { return a.id == b ;},
                [](Record_sequential const&a,  int const&b) { return a.id < b ;},
                [](Record_sequential const&a,  int const&b) { return a.id > b ;}
                );
                record = file.search(stoi(cadena));

    }else if(key_table == "ciclo"){
        SequentialFile<Record_sequential, int> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return a.ciclo < b.ciclo ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.ciclo > b.ciclo ;},
                [](Record_sequential const&a, Record_sequential const&b) { return a.ciclo == b.ciclo ;},
                [](Record_sequential const&a,  int const&b) { return a.ciclo == b ;},
                [](Record_sequential const&a,  int const&b) { return a.ciclo < b ;},
                [](Record_sequential const&a,  int const&b) { return a.ciclo > b ;}
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
    }else if(key_table == "surname"){
        SequentialFile<Record_sequential, string> file(table_name + "_sq.dat", "auxiliar.dat",
                [](Record_sequential const&a,Record_sequential const&b) { return strcmp(a.surname,b.surname) < 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.surname,b.surname) > 0 ;},
                [](Record_sequential const&a, Record_sequential const&b) { return strcmp(a.surname,b.surname) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.surname,b.c_str()) == 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.surname,b.c_str()) < 0 ;},
                [](Record_sequential const&a,  string const&b) { return strcmp(a.surname,b.c_str()) > 0 ;}
                );
                record = file.search(cadena);
    }else{
        cout<<"Key no encontrado, Error"<<endl;
        return;
    }
    if(record) record->showData();
    else
        cout<<"No existe este registro"<<endl;
}
//AVL
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
    }

}
void leer_csv(string table_name, string filename, Token::Type index_type, string key_table){
    ifstream file_(filename);
    string line;
    getline(file_, line);

    if(index_type == Token::SEQUENTIAL){
        create_sequential(key_table, table_name, file_);
    }else if(index_type == Token::AVL){
        
    }
    // else if(index_type == Token::AVL){
    //     cout<<"Creando indice AVL con key "<<key_table<<endl;
    //     cout<<"Ruta: "<<filename<<endl;}
    // else if(index_type == Token::HASH)
    //     cout<<"Creando indice hash con key "<<key_table<<endl;
    else
        cout<<"Error"<<endl;


}
