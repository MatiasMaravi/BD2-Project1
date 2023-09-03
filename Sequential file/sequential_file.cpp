#include <iostream>
#include <cstring>
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
    void setData(int id_, string name_, string surname_, int ciclo_) {
        this->id = id_;
        strcpy(this->name, name_.c_str());
        strcpy(this->surname, surname_.c_str());
        this->ciclo = ciclo_;
        next = -1;
        archivo = 'd';
    }
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
    void reorganizar();
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
    long long size = file.tellg();
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
void SequentialFile<T>::reorganizar() {
    fstream file(this->datos, ios::in | ios::binary);
    fstream aux(this->auxiliar, ios::in | ios::binary);
    if (!file.is_open() || !aux.is_open()) throw ("No se pudo abrir el archivo");
    
}



template <class T>
bool SequentialFile<T>::insert(Record record) {

    fstream file(this->datos, ios::app | ios::binary | ios::in | ios::out);

    if(!file.is_open()) throw ("No se pudo abrir el archivo");
    
    if(size_datos() == 0){
        // Se guarda un puntero al inicio de todos los datos
        Record cabecera;
        cabecera.setData(2,"nombre","apellido",1);
        cabecera.next=1;
        file.seekp(0, ios::end);
        file.write((char*)&cabecera, sizeof(record));

        file.seekp(0, ios::end);
        file.write((char*)&record, sizeof(record));
        file.close();
        return true;
    }
    else{
        fstream file(this->datos,ios::binary | ios::in | ios::out);
        int size = sizeof(record);
        file.seekg(-size, ios::end);
        Record last;
        file.read((char*)&last, sizeof(last));

        string a = record.name;
        string b = last.name;
  
        if(a>b){
            last.next = size_datos();
            file.seekp(-sizeof(record), ios::end);
            file.write((char*)&last, sizeof(last));
            file.seekp(0,ios::cur);
            file.write((char*)&record, sizeof(record));
            file.close();
            return true;
        }
        else{
            fstream file(this->datos, ios::binary | ios::in | ios::out);
            fstream aux(this->auxiliar, ios::app | ios::binary | ios::in | ios::out);
            if(!aux.is_open()) throw ("No se pudo abrir el archivo");

            Record current;
            file.seekg(sizeof(Record), ios::beg);
            file.read((char*)&current, sizeof(current));
            int pos = 0;

            string a = record.name;
            string b = current.name;

            while (a>b)
            {
                file.read((char*)&current, sizeof(current));
                b=current.name;
                pos++;
            }


            file.seekg((pos)*sizeof(record), ios::beg);
            file.read((char*)&current, sizeof(current));
            int siguiente = current.next;
            char archivo = current.archivo;
            //verificado
            if(current.archivo == 'a'){
                fstream aux(this->auxiliar, ios::binary | ios::in | ios::out);
                Record auxiliar;
                aux.seekg(siguiente*sizeof(Record), ios::beg);
                aux.read((char*)&auxiliar, sizeof(auxiliar));
                int anterior = siguiente;

                string a = record.name;
                string b = auxiliar.name;

                while(a>b && auxiliar.archivo == 'a' && auxiliar.next != -1){
                    aux.seekg(siguiente*sizeof(Record), ios::beg);
                    aux.read((char*)&auxiliar, sizeof(auxiliar));
                    anterior = siguiente;
                    siguiente = auxiliar.next;
                    archivo = auxiliar.archivo;
                }

                record.archivo = auxiliar.archivo;
                record.next = auxiliar.next;
                auxiliar.next = size_auxiliar();
                auxiliar.archivo = 'a';

                aux.seekp(anterior*sizeof(Record), ios::beg);
                aux.write((char*)&auxiliar, sizeof(auxiliar));
                aux.seekp(0, ios::end);
                aux.write((char*)&record, sizeof(record));
                aux.close();
                file.close();

                if(size_auxiliar() == 20){
                    reorganizar();
                }
                return true;
            }
            else{
                    current.next = size_auxiliar();
                    current.archivo = 'a';
                    file.seekp((pos)*sizeof(record), ios::beg);
                    file.write((char*)&current, sizeof(current));
                    record.archivo = archivo;
                    record.next = siguiente; 
                    aux.seekp(0, ios::end);
                    aux.write((char*)&record, sizeof(record));
                    aux.close();
                    file.close();

                    if(size_auxiliar() == 20){
                        reorganizar();
                    }

                    return true;
            
            }
            file.close();
            aux.close();
            return false;
        }
    }
    file.close();
    return false;
}



template <class T>
bool SequentialFile<T>::remove(T key){
    return false;
}
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

template <class T>
vector<Record> SequentialFile<T>::search(T key){
    vector<Record> result;
    return result;
}
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

template <class T>
vector<Record> SequentialFile<T>::range_search(T key1, T key2) {
    vector<Record> result;
    fstream file(this->datos,ios::app| ios::in | ios::binary| ios::out);
    fstream aux(this->auxiliar, ios::app|ios::in | ios::binary| ios::out);

    if (!file.is_open() || !aux.is_open()) {
        return result;
    }

    Record cabecera;

    file.seekg(0, ios::beg);
    file.read((char*)&cabecera, sizeof(cabecera));

    int pos = cabecera.next;
    char archivo = cabecera.archivo;


   if(archivo=='d'){
        Record current;
        file.seekg(pos*sizeof(Record), ios::beg);
        file.read((char*)&current, sizeof(current));
        string a = current.name;
        while (a<=key2)
        {
            if(a>=key1){
                result.push_back(current);
            }
            if(current.next==-1){
                break;
            }
            if(current.archivo=='a'){
                aux.seekg(current.next*sizeof(Record), ios::beg);
                aux.read((char*)&current, sizeof(current));
                a=current.name;
            }
            else{
                file.seekg(current.next*sizeof(Record), ios::beg);
                file.read((char*)&current, sizeof(current));
                a=current.name;
            }
        }
        file.close();
        aux.close();
        return result;
    }
    else{
        Record current;
        aux.seekg(pos*sizeof(Record), ios::beg);
        aux.read((char*)&current, sizeof(current));
        string a = current.name;
        while (a<=key2)
        {
            if(a>=key1){
                result.push_back(current);
            }
            if(current.next==-1){
                break;
            }
            if(current.archivo=='a'){
                aux.seekg(current.next*sizeof(Record), ios::beg);
                aux.read((char*)&current, sizeof(current));
                a=current.name;
            }
            else{
                file.seekg(current.next*sizeof(Record), ios::beg);
                file.read((char*)&current, sizeof(current));
                a=current.name;
            }
        }
        file.close();
        aux.close();
        return result;
    }

}



int main() {

    SequentialFile<string> file("datos.dat","auxiliar.dat");
    Record record;
    record.setData(1, "Andres", "Perez", 1);
    file.insert(record);
    record.setData(2, "Carlos", "Perez", 1);
    file.insert(record);
    record.setData(3, "Cintia", "Perez", 1);
    file.insert(record);
    record.setData(4, "Jorge", "Perez", 1);
    file.insert(record);
    record.setData(5, "Josimar", "Perez", 1);
    file.insert(record);
    record.setData(6, "Mabel", "Perez", 1);
    file.insert(record);
    record.setData(7, "Saulo", "Perez", 1);
    file.insert(record);
    record.setData(8, "Gabriel", "Perez", 1);
    file.insert(record);
    record.setData(9, "Gonzalo", "Perez", 1);
    file.insert(record);
    record.setData(10, "Maria", "Perez", 1);
    file.insert(record);
    record.setData(11, "Abel", "Perez", 1);
    file.insert(record);

    cout << "Datos.dat" << endl;
    fstream file1("datos.dat",ios::app |ios::in | ios::binary);
    Record cabecera;
    file1.seekg(0, ios::beg);
    file1.read((char*)&cabecera, sizeof(cabecera));
    cout << cabecera.next << " " << cabecera.archivo << endl;
    Record current;
    file1.read((char*)&current, sizeof(current));
    while (!file1.eof())
    {
        cout << current.id << " " << current.name << " " << current.surname << " " << current.ciclo << " " << current.next << " " << current.archivo << endl;
        file1.read((char*)&current, sizeof(current));
    }

    cout << endl;

    cout << "Auxiliar.dat" << endl;
    fstream file2("auxiliar.dat",ios::app |ios::in | ios::binary);
    file2.seekg(0, ios::beg);
    file2.read((char*)&current, sizeof(current));
    while (!file2.eof())
    {
        cout << current.id << " " << current.name << " " << current.surname << " " << current.ciclo << " " << current.next << " " << current.archivo << endl;
        file2.read((char*)&current, sizeof(current));
    }

    cout << endl;
    cout << "Busqueda por rango:"<< endl;

    vector<Record> result = file.range_search("Carlos", "Saulo");
    for(auto i : result){
        cout << i.id << " " << i.name << " " << i.surname << " " << i.ciclo << " " << i.next << " " << i.archivo << endl;
    }
    return 0;
}
