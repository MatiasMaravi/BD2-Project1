#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <functional>
#include "../SequentialFile/Record_sequential.h"

using namespace std;

template <class T, typename TK>
class SequentialFile {
    string datos;
    string auxiliar;
    std::function<bool(const T &, const T &)> less;
    std::function<bool(const T &, const T &)> greater;
    std::function<bool(const T &, const T &)> equal;
    std::function<bool(const T &, const TK &)> equal_key;
    std::function<bool(const T &, const TK &)> less_key;
    std::function<bool(const T &, const TK &)> greater_key;
    static SequentialFile<T, TK>* instance;
public:
    SequentialFile(string filename1, string filename2,
                   function<bool(const T &, const T &)> less,
                   function<bool(const T &, const T &)> greater,
                   function<bool(const T &, const T & )> equal,
                   function<bool(const T &, const TK &)> equal_key,
                   function<bool(const T &, const TK &)> less_key,
                   function<bool(const T &, const TK &)> greater_key);

    T readRecord(int pos, char fileChar);
    static SequentialFile<T, TK>& getInstance(string filename1, string filename2,
                                              function<bool(const T &, const T &)> less,
                                              function<bool(const T &, const T &)> greater,
                                              function<bool(const T &, const T &)> equal,
                                              function<bool(const T &, const TK &)> equal_key,
                                              function<bool(const T &, const TK &)> less_key,
                                              function<bool(const T &, const TK &)> greater_key) {
        static SequentialFile<T, TK> instance(filename1, filename2, less, greater, equal, equal_key, less_key, greater_key);
        return instance;
    }

    int size_datos();
    int size_auxiliar();
    vector<T> reorganizar();


    bool insert(T record);
    bool remove(TK key);
    vector<T> search(TK key);

    vector<T> range_search(TK key1, TK key2);

    ~SequentialFile() {
        delete instance;
    }

};

template <class T, typename TK>
SequentialFile<T, TK>* SequentialFile<T, TK>::instance = nullptr;


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

template <class T, typename TK>
T SequentialFile<T, TK>::readRecord(int pos, char fileChar) {
    T result;


    if (fileChar == 'a') {
        fstream file(this->auxiliar, ios::in | ios::binary);
        if (!file.is_open()) throw("No se pudo abrir el archivo");
        if (pos > size_auxiliar() || pos < 1) {
            cout << "No existen datos en esa posición\n";
            return result;
        }



        file.seekg(sizeof(T)*pos, ios::beg);
        file.read((char*) &result, sizeof(T));

        file.close();
    }
    else if (fileChar == 'd') {
        fstream file(this->datos, ios::in | ios::binary);
        if (!file.is_open()) throw("No se pudo abrir el archivo");
        if (pos > size_datos() || pos < 1) {
            cout << "No existen datos en esa posición\n";
            return result;
        }

        file.seekg(sizeof(T)*(pos), ios::beg);
        file.read((char*) &result, sizeof(T));

        file.close();
    }
    else throw("No se pudo encontrar un archivo relacionado a ese char");

    return result;
}

template <class T, typename TK>
int SequentialFile<T, TK>::size_datos() {
    fstream file(this->datos, ios::in | ios::binary);
    if (!file.is_open()) throw("No se pudo abrir el archivo");

    file.seekg(0, ios::end);
    int size = file.tellg();
    file.close();


    return size / sizeof(T);
}

template <class T, typename TK>
int SequentialFile<T, TK>::size_auxiliar() {
    fstream file(this->auxiliar, ios::in | ios::binary);
    if (!file.is_open()) throw("No se pudo abrir el archivo");

    file.seekg(0, ios::end);
    int size = file.tellg();
    file.close();



    return size / sizeof(T);
}


template <class T, typename TK>
vector<T> SequentialFile<T, TK>::reorganizar() {
    fstream file(this->datos, ios::in | ios::binary);
    fstream auxFile(this->auxiliar, ios::in | ios::binary);

    if (!file.is_open() || !auxFile.is_open()) throw("No se pudo abrir el archivo");

    vector<T> records;
    T record;
    file.read((char*) &record, sizeof(T));

    char fileChar = record.archivo;
    int pos = record.next, auxPos = 1;

    record.next = auxPos++; record.archivo = 'd';
    records.push_back(record);

    while (fileChar != 'd' or pos != -1) {
        if (fileChar == 'a') {
            auxFile.seekg(sizeof(T)*pos, ios::beg);
            auxFile.read((char*) &record, sizeof(T));
        }
        else if (fileChar == 'd') {
            file.seekg(sizeof(T)*(pos), ios::beg);
            file.read((char*) &record, sizeof(T));
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
        file2.write((char*) &r, sizeof(T));
    }

    file2.close();

    ofstream auxFile2(this->auxiliar, ios::trunc);
    auxFile2.close();

    return records;  // Devuelve el vector de records
}


template <class T, typename TK>
bool SequentialFile<T, TK>::insert(T record) {
    fstream file(this->datos, ios::app | ios::binary | ios::in | ios::out);

    if (!file.is_open()) throw("No se pudo abrir el archivo");

    if (size_datos() == 0) {
        // Se guarda un puntero al inicio de todos los datos
        T cabecera;

        //cabecera.setData(2, "nombre", "apellido", 1);
        cabecera.setData(2, "nombre", 100, 20,"alianza","peru");

        cabecera.next = 1;
        file.seekp(0, ios::end);
        file.write((char *)&cabecera, sizeof(record));

        file.seekp(0, ios::end);
        file.write((char *)&record, sizeof(record));
        file.close();
        return true;
    }
    else {
        fstream file(this->datos, ios::binary | ios::in | ios::out);
        int size = sizeof(record);
        file.seekg(-size, ios::end);
        T last;
        file.read((char *)&last, sizeof(last));

        if (greater(record, last)) {
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
            if (!aux.is_open())
                throw("No se pudo abrir el archivo");

            T current;
            file.seekg(sizeof(T), ios::beg);
            file.read((char *)&current, sizeof(current));
            int pos = 0;

            while (greater(record,current)) {
                file.read((char *)&current, sizeof(current));
                pos++;
            }

            file.seekg((pos) * sizeof(record), ios::beg);
            file.read((char *)&current, sizeof(current));
            int siguiente = current.next;
            char archivo = current.archivo;

            // Verificado
            if (current.archivo == 'a') {
                fstream aux(this->auxiliar, ios::binary | ios::in | ios::out);
                T auxiliar;
                aux.seekg(siguiente * sizeof(T), ios::beg);
                aux.read((char *)&auxiliar, sizeof(auxiliar));
                int anterior = siguiente;

                while (greater(record,auxiliar) && auxiliar.archivo == 'a' && auxiliar.next != -1) {
                    aux.seekg(siguiente * sizeof(T), ios::beg);
                    aux.read((char *)&auxiliar, sizeof(auxiliar));
                    anterior = siguiente;
                    siguiente = auxiliar.next;
                    archivo = auxiliar.archivo;
                }

                record.archivo = auxiliar.archivo;
                record.next = auxiliar.next;
                auxiliar.next = size_auxiliar();
                auxiliar.archivo = 'a';

                aux.seekp(anterior * sizeof(T), ios::beg);
                aux.write((char *)&auxiliar, sizeof(auxiliar));
                aux.seekp(0, ios::end);
                aux.write((char *)&record, sizeof(record));
                aux.close();
                file.close();

                if (size_auxiliar() == 20) reorganizar();
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

template <class T, typename TK>
bool SequentialFile<T, TK>::remove(TK key) {
    fstream file (this->datos, ios::in | ios::out | ios::binary);
    if (!file.is_open()) return false;

    T cabecera;
    file.read((char*) &cabecera, sizeof(T));

    T record = readRecord(cabecera.next, cabecera.archivo), auxRecord;
    if (equal_key(record, key)) {
        int auxPos = record.next;
        char auxChar = record.archivo;
        if (cabecera.archivo == 'd') {
            record.next = -1;
            record.archivo = 'a';
            file.seekp(sizeof(T) * cabecera.next, ios::beg);
            file.write((char*) &record, sizeof(T));
        }
        else {
            fstream auxFile (this->auxiliar, ios::in | ios::out | ios::binary);
            if (!auxFile.is_open()) {
                cout << "No se pudo remover el registro ya que no se abrio el archivo auxiliar\n";
                return false;
            }
            
            record.next = -1;
            record.archivo = 'a';
            
            auxFile.seekp(sizeof(T) * (cabecera.next - 1), ios::beg);
            auxFile.write((char*) &record, sizeof(T));
            auxFile.close();
        }
        cabecera.next = auxPos;
        cabecera.archivo = auxChar;

        file.seekp(0, ios::beg);
        file.write((char*) &cabecera, sizeof(T));
        file.close();

        return true;
    }
    else {
        fstream auxFile (this->auxiliar, ios::in | ios::out | ios::binary);
        if (!auxFile.is_open()) {
            cout << "No se pudo remover el registro ya que no se abrio el archivo auxiliar\n";
            return false;
        }
        
        char fileChar = 'd', auxChar; int pos = 1, auxPos;

        do {
            auxRecord = readRecord(record.next, record.archivo);
            if (equal_key(auxRecord, key)) {
                // Para reemplazar el puntero
                auxPos = auxRecord.next;
                auxChar = auxRecord.archivo;

                auxRecord.next = -1;
                auxRecord.archivo = 'a';

                if (record.archivo == 'd') {
                    file.seekp(sizeof(T) * record.next, ios::beg);
                    file.write((char*) &auxRecord, sizeof(T));
                }
                else {
                    auxFile.seekp(sizeof(T) * (record.next - 1), ios::beg);
                    auxFile.write((char*) &auxRecord, sizeof(T));
                }

                record.next = auxPos;
                record.archivo = auxChar;

                if (fileChar == 'd') {
                    file.seekp(sizeof(T) * pos, ios::beg);
                    file.write((char*) &record, sizeof(T));

                }
                else {
                    auxFile.seekp(sizeof(T) * (pos - 1), ios::beg);
                    auxFile.write((char*) &record, sizeof(T));
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

template <class T, typename TK>
vector<T> SequentialFile<T, TK>::search(TK key) {
    fstream file(this->datos, ios::in | ios::binary);
    vector<T> results;

    T result;
    int l = 1, u = size_datos() - 1, m;

    while (u >= l) {
        m = (l + u) / 2;
        file.seekg(sizeof(T) * m, ios::beg);
        file.read((char*)&result, sizeof(T));
        if (greater_key(result, key)) {
            u = m - 1;
        } else if (less_key(result, key)) {
            l = m + 1;
        } else {

            results.push_back(result);

            for (int i = m - 1; i >= l; i--) {
                file.seekg(sizeof(T) * i, ios::beg);
                file.read((char*)&result, sizeof(T));
                if (equal_key(result, key)) {
                    results.push_back(result);
                } else {
                    break;
                }
            }

            for (int i = m + 1; i <= u; i++) {
                file.seekg(sizeof(T) * i, ios::beg);
                file.read((char*)&result, sizeof(T));
                if (equal_key(result, key)) {
                    results.push_back(result);
                } else {
                    break;
                }
            }
            break;
        }
//=======
//        m = (l+u) / 2;
//        file.seekg(sizeof(T)*m, ios::beg);
//        file.read((char*)&result, sizeof(T));
//        if (greater_key(result,key)) u = m - 1;
//        else if (less_key(result,key)) l = m + 1;
//        else break;
//>>>>>>> main
    }

    file.close();


    if (results.empty()) {
        fstream auxFile(this->auxiliar, ios::in | ios::binary);
        if (!auxFile.is_open()) throw("No se pudo abrir el archivo auxiliar");
        while (auxFile.read((char*)&result, sizeof(T))) {
            if (equal_key(result, key)) {
                results.push_back(result);
            }
        }
        auxFile.close();
    }

    return results;

}




template <class T, typename TK>
vector<T> SequentialFile<T, TK>::range_search(TK key1, TK key2) {
    vector<T> result;
    fstream file(this->datos, ios::app | ios::in | ios::binary | ios::out);
    fstream aux(this->auxiliar, ios::app | ios::in | ios::binary | ios::out);

    if (!file.is_open() || !aux.is_open()) return result;

    T cabecera;

    file.seekg(0, ios::beg);
    file.read((char *)&cabecera, sizeof(cabecera));

    int pos = cabecera.next;
    char archivo = cabecera.archivo;

    if (archivo == 'd') {
        T current;
        file.seekg(pos * sizeof(T), ios::beg);
        file.read((char *)&current, sizeof(current));
        while (less_key(current,key2) || equal_key(current,key2)) //a <= key2
        {
            if (greater_key(current,key1) || equal_key(current,key1)) result.push_back(current); //a >= key1
            
            if (current.next == -1) break;
            
            if (current.archivo == 'a') {
                aux.seekg(current.next * sizeof(T), ios::beg);
                aux.read((char *)&current, sizeof(current));
            }
            else {
                file.seekg(current.next * sizeof(T), ios::beg);
                file.read((char *)&current, sizeof(current));
            }
        }
        file.close();
        aux.close();
        return result;
    }
    else {
        T current;
        aux.seekg(pos * sizeof(T), ios::beg);
        aux.read((char *)&current, sizeof(current));
        while (less_key(current,key2) || equal_key(current,key2)) { //a <= key2
            if (greater_key(current,key1) || equal_key(current,key1)) result.push_back(current); //a >= key1
            
            if (current.next == -1) break;

            if (current.archivo == 'a') {
                aux.seekg(current.next * sizeof(T), ios::beg);
                aux.read((char *)&current, sizeof(current));
            }
            else {
                file.seekg(current.next * sizeof(T), ios::beg);
                file.read((char *)&current, sizeof(current));
            }
        }
        file.close();
        aux.close();
        return result;
    }
}