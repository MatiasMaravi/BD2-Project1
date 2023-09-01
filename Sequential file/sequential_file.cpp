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
};

template <class T>
class SequentialFile{
    string filename;
public:
    SequentialFile(string filename);
    bool insert(Record record);
    bool remove(T key);
    vector<Record> search(T key);
    vector<Record> range_search(T key1, T key2);
};

template <class T>
SequentialFile<T>::SequentialFile(string filename) {
    this->filename = filename;
}

template <class T>
bool SequentialFile<T>::insert(Record record) {
    /*
    fstream file;
    file.open(filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        file.open(filename, ios::out | ios::binary);
        file.write((char*)&record, sizeof(record));
        file.close();
        return true;
    }
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);
    Record last;
    file.read((char*)&last, sizeof(last));
    if (last.id < record.id) {
        file.seekg(0, ios::end);
        file.write((char*)&record, sizeof(record));
        file.close();
        return true;
    }
    int pos = 0;
    while (pos < size) {
        Record current;
        file.read((char*)&current, sizeof(current));
        if (current.id == record.id) {
            file.close();
            return false;
        }
        if (current.id > record.id) {
            file.seekg(pos, ios::beg);
            file.write((char*)&record, sizeof(record));
            file.write((char*)&current, sizeof(current));
            file.close();
            return true;
        }
        pos += sizeof(current);
    }
    file.close();
    return false; */  // recomendacion de copilot
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
        if (current.id >= key1 && current.id <= key2) {
            result.push_back(current);
        }
        pos += sizeof(current);
    }
    file.close();
    return result;
    */ // recomendacion de copilot
}