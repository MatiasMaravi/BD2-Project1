#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Record {
    int id;
    char name[20];
    char surname[20];
    int ciclo;
    int next;
    char archivo;

    void setData();
};

void Record::setData() {
    cout << "ID: ";
    cin >> id;
    cout << "Name: ";
    cin >> name;
    cout << "Surname: ";
    cin >> surname;
    cout << "Ciclo: ";
    cin >> ciclo;
    next = -1;
    archivo = 'd';
}



template <class T>
class SequentialFile{
    string datos;
    string auxiliar;
public:
    SequentialFile(string filename1,string filename2);
    int size_datos();
    int size_auxiliar();
    bool insert(Record record);
    bool remove(T key);
    vector<Record> search(T key);
    vector<Record> range_search(T key1, T key2);
};

template <class T>
SequentialFile<T>::SequentialFile(string filename1,string filename2) {
    this->datos = filename1;
    this->auxiliar = filename2;
}

template <class T>
int SequentialFile<T>::size_datos() {
    fstream file(this->datos, ios::in | ios::binary);
    if (!file.is_open()) throw ("No se pudo abrir el archivo");
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.close();
    return size / sizeof(Record);
}

template <class T>
int SequentialFile<T>::size_auxiliar() {
    fstream file(this->auxiliar, ios::in | ios::binary);
    if (!file.is_open()) throw ("No se pudo abrir el archivo");
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.close();
    return size / sizeof(Record);
}

template <class T>
bool SequentialFile<T>::insert(Record record) {

    fstream file(this->datos, ios::app | ios::binary | ios::in | ios::out);

    if(!file.is_open()) throw ("No se pudo abrir el archivo");
    
    if(size() == 0){
        // separar en caso no funcione
        file.seekp(0, ios::end);
        file.write((char*)&record, sizeof(record));
        file.close();
        return true;
    }
    else{
        file.seekg(-sizeof(record), ios::end);
        Record last;
        file.read((char*)&last, sizeof(last));
    
        if(record.name>last.name){
            last.next = size_datos();
            file.seekp(-sizeof(record), ios::end);
            file.write((char*)&last, sizeof(last));
            file.seekp(0,ios::cur);
            file.write((char*)&record, sizeof(record));
            file.close();
            return true;
        }
        else{
            fstream aux(this->auxiliar, ios::app | ios::binary | ios::in | ios::out);
            if(!aux.is_open()) throw ("No se pudo abrir el archivo");

            Record current;
            file.seekg(0, ios::beg);
            file.read((char*)&current, sizeof(current));
            int pos = 0;

            while (record.name>current.name)
            {
                file.read((char*)&current, sizeof(current));
                pos++;
            }

            file.seekg((pos-1)*sizeof(record), ios::beg);
            file.read((char*)&current, sizeof(current));
            int siguiente = current.next;
            char archivo = current.archivo;
            
            if(current.archivo == 'a'){
                Record auxiliar;
                aux.seekg(siguiente*sizeof(Record), ios::beg);
                aux.read((char*)&auxiliar, sizeof(auxiliar));
                int anterior = siguiente;
                while(record.name>auxiliar.name && auxiliar.archivo == 'a'){
                    aux.seekg(siguiente*sizeof(Record), ios::beg);
                    aux.read((char*)&auxiliar, sizeof(auxiliar));
                    anterior = siguiente;
                    siguiente = auxiliar.next;
                    archivo = auxiliar.archivo;
                }

                record.archivo = archivo;
                record.next = siguiente;
                auxiliar.next = size_auxiliar();
                aux.seekp(0, ios::end);
                aux.write((char*)&record, sizeof(record));
                aux.seekp(anterior*sizeof(Record), ios::beg);
                aux.write((char*)&auxiliar, sizeof(auxiliar));
                aux.close();
                file.close();
                return true;
            }
            else{
                    current.next = size_auxiliar();
                    current.archivo = 'a';
                    file.seekp((pos-1)*sizeof(record), ios::beg);
                    file.write((char*)&current, sizeof(current));
                    record.archivo = archivo;
                    record.next = siguiente; 
                    aux.seekp(0, ios::end);
                    aux.write((char*)&record, sizeof(record));
                    aux.close();
                    file.close();
                    return true;
            
            }
            fiel.close();
        }
    }

    
}

template <class T>
bool SequentialFile<T>::remove(T key) {
    /*
    fstream file;
    file.open(filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);
    int pos = 0;
    while (pos < size) {
        Record current;
        file.read((char*)&current, sizeof(current));
        if (current.id == key) {
            current.id = -1;
            file.seekg(pos, ios::beg);
            file.write((char*)&current, sizeof(current));
            file.close();
            return true;
        }
        pos += sizeof(current);
    }
    file.close();
    return false;
    */ // recomendacion de copilot
}

template <class T>
vector<Record> SequentialFile<T>::search(T key) {
    /*
    vector<Record> result;
    fstream file;
    file.open(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        return result;
    }
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);
    int pos = 0;
    while (pos < size) {
        Record current;
        file.read((char*)&current, sizeof(current));
        if (current.id == key) {
            result.push_back(current);
        }
        pos += sizeof(current);
    }
    file.close();
    return result;
    */ // recomendacion de copilot
}

template <class T>
vector<Record> SequentialFile<T>::range_search(T key1, T key2) {
    vector<Record> result;
    fstream file(this->datos, ios::in | ios::binary| ios::out);
    fstream aux(this->auxiliar, ios::in | ios::binary| ios::out);

    if (!file.is_open() || !aux.is_open()) {
        return result;
    }

    char archivo;
    int pos = 0;

    file.seekg(0, ios::beg);
    file.read((char*)&archivo, sizeof(archivo));
    file.read((char*)&pos, sizeof(pos));


   if(archivo=='d'){
        Record current;
        file.seekg(pos*sizeof(Record), ios::beg);
        file.read((char*)&current, sizeof(current));
        while (current.name<=key2)
        {
            if(current.name>=key1){
                result.push_back(current);
            }
            file.read((char*)&current, sizeof(current));
        }
        file.close();
        return result;
    }
    else{
        Record current;
        aux.seekg(pos*sizeof(Record), ios::beg);
        aux.read((char*)&current, sizeof(current));
        while (current.name<=key2)
        {
            if(current.name>=key1){
                result.push_back(current);
            }
            aux.read((char*)&current, sizeof(current));
        }
        aux.close();
        return result;
    }

}