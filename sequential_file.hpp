#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;
template <class T>
struct Record {
    int id;
    char name[20];
    char surname[20];
    int ciclo;
    int next;
    char archivo;
    T key;

    void setData() {
        cout << "ID: "; cin >> id;
        cout << "Name: "; cin >> name;
        cout << "Surname: "; cin >> surname;
        cout << "Ciclo: "; cin >> ciclo;
        next = -1;
        archivo = 'd';
    }
    void setData(int id_, string name_, string surname_, int ciclo_) {
        this->id = id_;
        strcpy(this->name, name_.c_str());
        strcpy(this->surname, surname_.c_str());
        this->ciclo = ciclo_;
        next = -1;
        archivo = 'd';
    }
    void set_key_int(T key_){
        key = key_;
    }
    void set_key_string(T key_){
        key = key_;
    }
    void showData() {
        cout << "ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Surname: " << surname << "\n";
        cout << "Ciclo: " << ciclo << "\n";
        cout << "Next: " << next << archivo << "\n\n";
    }
};

template <class T>
class SequentialFile {
    string datos;
    string auxiliar;

public:
    SequentialFile(string filename1, string filename2);

    Record<T> readRecord(int pos, char fileChar);

    int size_datos();
    int size_auxiliar();
    void reorganizar();
    void init_cabecera(fstream &file, Record<T> record);
    
    bool insert(Record<T> record);
    bool remove(T key);
    
    Record<T>* search(T key);
    vector<Record<T>> range_search(T key1, T key2);
};

template <class T>
SequentialFile<T>::SequentialFile(string filename1, string filename2) {
    this->datos = filename1;
    this->auxiliar = filename2;
}

template <class T>
Record<T> SequentialFile<T>::readRecord(int pos, char fileChar) {
    Record<T> result;
    if (fileChar == 'a') {
        fstream file(this->auxiliar, ios::in | ios::binary);
        if (!file.is_open()) throw("No se pudo abrir el archivo");
        if (pos > size_auxiliar()) {
            cout << "No existen datos en esa posición\n";
            return result;
        }

        file.seekg(sizeof(Record<T>)*pos, ios::beg);
        file.read((char*) &result, sizeof(Record<T>));

        file.close();
    }
    else if (fileChar == 'd') {
        fstream file(this->datos, ios::in | ios::binary);
        if (!file.is_open()) throw("No se pudo abrir el archivo");
        if (pos > size_datos()) {
            cout << "No existen datos en esa posición\n";
            return result;
        }

        file.seekg(sizeof(Record<T>)*(pos), ios::beg);
        file.read((char*) &result, sizeof(Record<T>));

        file.close();
    }
    else throw("No se pudo encontrar un archivo relacionado a ese char");

    return result;
}

template <class T>
int SequentialFile<T>::size_datos() {
    fstream file(this->datos, ios::in | ios::binary);
    if (!file.is_open()) throw("No se pudo abrir el archivo");
    
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.close();
    
    return size / sizeof(Record<T>);
}

template <class T>
int SequentialFile<T>::size_auxiliar() {
    fstream file(this->auxiliar, ios::in | ios::binary);
    if (!file.is_open()) throw("No se pudo abrir el archivo");
    
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.close();
    
    return size / sizeof(Record<T>);
}

template <class T>
void SequentialFile<T>::reorganizar() {
    fstream file(this->datos, ios::in | ios::binary);
    fstream auxFile(this->auxiliar, ios::in | ios::binary);
    
    if (!file.is_open() || !auxFile.is_open()) throw("No se pudo abrir el archivo");

    vector<Record<T>> records;
    Record<T> record;
    file.read((char*) &record, sizeof(Record<T>));

    char fileChar = record.archivo;
    int pos = record.next, auxPos = 1;

    record.next = auxPos++; record.archivo = 'd';
    records.push_back(record);

    while (fileChar != 'd' or pos != -1) {
        if (fileChar == 'a') {
            auxFile.seekg(sizeof(Record<T>)*pos, ios::beg);
            auxFile.read((char*) &record, sizeof(Record<T>));
        }
        else if (fileChar == 'd') {
            file.seekg(sizeof(Record<T>)*(pos), ios::beg);
            file.read((char*) &record, sizeof(Record<T>));
        }
        fileChar = record.archivo;
        pos = record.next;
        if (fileChar == 'd' && pos == -1) {
            records.push_back(record);
            break;
        }
        else if (pos != -1) {
            record.next = auxPos++;
            record.archivo = 'd';
            records.push_back(record);
        }
    }

    file.close();
    auxFile.close();

    ofstream file2(this->datos);

    file2.seekp(0, ios::beg);
    for (auto r : records) {
        r.archivo = 'd';
        r.showData();
        file2.write((char*) &r, sizeof(Record<T>));
    }

    file2.close();

    ofstream auxFile2(this->auxiliar, ios::trunc);
    auxFile2.close();
}
template <class T>
void SequentialFile<T>::init_cabecera(fstream &file, Record<T> record) {
    Record<T> cabecera;
    cabecera.setData(2, "nombre", "apellido", 1);
    cabecera.next = 1;
    file.seekp(0, ios::end);
    file.write((char *)&cabecera, sizeof(record));

    file.seekp(0, ios::end);
    file.write((char *)&record, sizeof(record));
    file.close();
}

template <class T>
bool SequentialFile<T>::insert(Record<T> record) {
    fstream file(this->datos, ios::app | ios::binary | ios::in | ios::out);

    if (!file.is_open()) throw("No se pudo abrir el archivo");

    if (size_datos() == 0) {
        // Se guarda un puntero al inicio de todos los datos
        init_cabecera(file, record);
        return true;
    }
    else {
        fstream file(this->datos, ios::binary | ios::in | ios::out);
        int size = sizeof(record);
        file.seekg(-size, ios::end);
        Record<T> last;
        file.read((char *)&last, sizeof(last));

        // string a = record.name;
        // string b = last.name;
        T a = record.key;
        T b = last.key;

        if (a > b) {
            last.next = size_datos();
            file.seekp(-sizeof(record), ios::end);
            file.write((char *)&last, sizeof(last));
            file.seekp(0, ios::cur);
            file.write((char *)&record, sizeof(record));
            file.close();
            return true;
        }
        else {
            fstream file(this->datos, ios::binary | ios::in | ios::out);
            fstream aux(this->auxiliar, ios::app | ios::binary | ios::in | ios::out);
            if (!aux.is_open()) throw("No se pudo abrir el archivo");

            Record<T> current;
            file.seekg(sizeof(Record<T>), ios::beg);
            file.read((char *)&current, sizeof(current));
            int pos = 0;

            // string a = record.name;
            // string b = current.name;
            T a = record.key;
            T b = current.key;

            while (a > b) {
                file.read((char *)&current, sizeof(current));
                b = current.key;
                pos++;
            }

            file.seekg((pos) * sizeof(record), ios::beg);
            file.read((char *)&current, sizeof(current));
            int siguiente = current.next;
            char archivo = current.archivo;
            
            // Verificado
            if (current.archivo == 'a') {
                fstream aux(this->auxiliar, ios::binary | ios::in | ios::out);
                Record<T> auxiliar;
                aux.seekg(siguiente * sizeof(Record<T>), ios::beg);
                aux.read((char *)&auxiliar, sizeof(auxiliar));
                int anterior = siguiente;

                // string a = record.name;
                // string b = auxiliar.name;
                T a = record.key;
                T b = auxiliar.key;

                while (a > b && auxiliar.archivo == 'a' && auxiliar.next != -1) {
                    aux.seekg(siguiente * sizeof(Record<T>), ios::beg);
                    aux.read((char *)&auxiliar, sizeof(auxiliar));
                    anterior = siguiente;
                    siguiente = auxiliar.next;
                    archivo = auxiliar.archivo;
                }

                record.archivo = auxiliar.archivo;
                record.next = auxiliar.next;
                auxiliar.next = size_auxiliar();
                auxiliar.archivo = 'a';

                aux.seekp(anterior * sizeof(Record<T>), ios::beg);
                aux.write((char *)&auxiliar, sizeof(auxiliar));
                aux.seekp(0, ios::end);
                aux.write((char *)&record, sizeof(record));
                aux.close();
                file.close();
                if (size_auxiliar() == 20) reorganizar();//Si es un millon de datos deberiamos cambiarlo?
                return true;
            }
            else {
                current.next = size_auxiliar();
                current.archivo = 'a';
                file.seekp((pos) * sizeof(record), ios::beg);
                file.write((char *)&current, sizeof(current));
                record.archivo = archivo;
                record.next = siguiente;
                aux.seekp(0, ios::end);
                aux.write((char *)&record, sizeof(record));
                aux.close();
                file.close();

                if (size_auxiliar() == 20) reorganizar();
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
bool SequentialFile<T>::remove(T key) {
    fstream file (this->datos, ios::in | ios::out | ios::binary);
    if (!file.is_open()) return false;
    // Al momento de eliminar, reemplazaremos el puntero con -1a ya que el últimos elemento siempre apunta a -1d
    
    // Primero validamos si el registro a eliminar es el primero
    Record<T> cabecera;
    file.read((char*) &cabecera, sizeof(Record<T>));

    // Ahora leemos ese registro
    Record<T> record = readRecord(cabecera.next, cabecera.archivo), auxRecord;

    if (record.key == key) {
        cabecera.next = record.next;
        cabecera.archivo = record.archivo;
        file.seekp(0, ios::beg);
        file.write((char*) &cabecera, sizeof(Record<T>));
        file.close();

        reorganizar();
        return true;
    } // En caso no sea el primero, deberemos buscar su predecesor
    else {
        fstream auxFile (this->auxiliar, ios::in | ios::out | ios::binary);

        char fileChar = 'd', auxChar; int pos = 1, auxPos;
        
        do {
            auxRecord = readRecord(record.next, record.archivo);
            if (auxRecord.key == key) {
                // Para reemplazar el puntero
                auxPos = auxRecord.next;
                auxChar = auxRecord.archivo;

                auxRecord.next = -1;
                auxRecord.archivo = 'a';

                if (record.archivo == 'd') {
                    file.seekp(sizeof(Record<T>) * record.next, ios::beg);
                    file.write((char*) &auxRecord, sizeof(Record<T>));
                }
                else {
                    auxFile.seekp(sizeof(Record<T>) * (record.next - 1), ios::beg);
                    auxFile.write((char*) &auxRecord, sizeof(Record<T>));
                }

                record.next = auxPos;
                record.archivo = auxChar;

                if (fileChar == 'd') {
                    file.seekp(sizeof(Record<T>) * pos, ios::beg);
                    file.write((char*) &record, sizeof(Record<T>));

                }
                else {
                    auxFile.seekp(sizeof(Record<T>) * (pos - 1), ios::beg);
                    auxFile.write((char*) &record, sizeof(Record<T>));
                }

                file.close();
                auxFile.close();
                
                reorganizar();
                return true;
            }
            fileChar = record.archivo; pos = record.next;
            record = auxRecord;
        } while (auxRecord.next != -1 or auxRecord.archivo != 'd');
    }

    return false;
}

template <class T>
Record<T>* SequentialFile<T>::search(T key) {
    fstream file (this->datos, ios::in | ios::out | ios::binary);
    Record<T>* result = new Record<T>();
    T a, b = key;
    int l = 1, u = size_datos() - 1, m;
    
    while (u >= l) {
        m = (l+u) / 2;
        file.seekg(sizeof(Record<T>)*m, ios::beg);
        file.read((char*) result, sizeof(Record<T>));
        a = result->key;
        if (a > b) u = m - 1;
        else if (a < b) l = m + 1;
        else break;
    }
    file.close();

    if (a != b) {
        fstream auxFile (this->auxiliar, ios::in | ios::out | ios::binary);
        if (!auxFile.is_open()) throw ("No se pudo abrir el archivo auxiliar");
        for (int i = 0; i < size_auxiliar(); i++) {
            auxFile.read((char*) result, sizeof(Record<T>));
            a = result->key;
            if (a == b) break;
        }
        auxFile.close();
    }
    
    return (a == b)? result : nullptr;
}

template <class T>
vector<Record<T>> SequentialFile<T>::range_search(T key1, T key2) {
    vector<Record<T>> result;
    fstream file(this->datos, ios::app | ios::in | ios::binary | ios::out);
    fstream aux(this->auxiliar, ios::app | ios::in | ios::binary | ios::out);

    if (!file.is_open() || !aux.is_open()) return result;

    Record<T> cabecera;

    file.seekg(0, ios::beg);
    file.read((char *)&cabecera, sizeof(cabecera));

    int pos = cabecera.next;
    char archivo = cabecera.archivo;
    Record<T> current;
    if (archivo == 'd') {
        file.seekg(pos * sizeof(Record<T>), ios::beg);
        file.read((char *)&current, sizeof(current));
    }else {
        aux.seekg(pos * sizeof(Record<T>), ios::beg);
        aux.read((char *)&current, sizeof(current));
    }
    T a = current.key;
    while (a <= key2){
        if (a >= key1) result.push_back(current);
        if (current.next == -1) break;
        if (current.archivo == 'a') {
            aux.seekg(current.next * sizeof(Record<T>), ios::beg);
            aux.read((char *)&current, sizeof(current));
            a = current.key;
        }else {
            file.seekg(current.next * sizeof(Record<T>), ios::beg);
            file.read((char *)&current, sizeof(current));
            a = current.key;
        }
    }
    file.close();
    aux.close();
    return result;
}

