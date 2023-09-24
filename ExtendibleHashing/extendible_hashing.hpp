#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include<cstring>
#include<functional>
using namespace std;
unsigned long long D = 3;

string to_binary(int n){
    vector <int> binary;
    string binary_string;
    while(n>0){
        binary.push_back(n%2);
        n/=2;
    }
    for (int i = binary.size() - 1; i >= 0; i--){
        binary_string += to_string(binary[i]);
    }
    if (binary_string.size() < D){
        int zeros = D - binary_string.size();
        for (int i = 0; i < zeros; i++){
            binary_string = "0" + binary_string;
        }
    }
    
    return binary_string;
}

// #define fb 226//4084/18
//alumno
struct Record{
    int id;
    char name[50];
    int value;
    int age;
    char fecha[50];
    int tamaño;
    char club[50];
    char nacionalidad[50];


    Record(){}

    Record(int codigo, string name_, int valor_, int age, string _fecha, int _tamaño,string _nacionalidad){
        this->id = codigo;
        strcpy(this->name, name_.c_str());
        this->value = valor_;
        this->age = age;
        strcpy(this->fecha, _fecha.c_str());
        this->tamaño = _tamaño;
        strcpy(this->nacionalidad, _nacionalidad.c_str());
    }
    void print(){
        cout<<"id: "<<id<<endl;
        cout<<"Nombre: "<<name<<endl;
        cout<<"valor: "<<value<<endl;
        cout<<"Edad: "<<age<<endl;
        cout<<"Fecha: "<<fecha<<endl;
        cout<<"Nacionalidad: "<<nacionalidad<<endl;
    }
};


struct IndexEntry{
    int pos_left;//0
    int pos_right;//1
    bool isLeaf;
    int pos_bucket;

    IndexEntry(){
        pos_left = -1;
        pos_right = -1;
        isLeaf = false;
        pos_bucket = -1;
    }

    IndexEntry(int pos_left, int pos_right, bool isLeaf, int pos_bucket){
        this->pos_left = pos_left;
        this->pos_right = pos_right;
        this->isLeaf = isLeaf;
        this->pos_bucket = pos_bucket;
    }
    void read(fstream &file, int pos = 0){
        file.seekg(pos,ios::beg);
        file.read((char*)&pos_left,sizeof(int));
        file.read((char*)&pos_right,sizeof(int));
        file.read((char*)&isLeaf,sizeof(bool));
        file.read((char*)&pos_bucket,sizeof(int));
    }
    void print(){
        cout<<"pos_left: "<<pos_left<<endl;
        cout<<"pos_right: "<<pos_right<<endl;
        cout<<"isLeaf: "<<isLeaf<<endl;
        cout<<"pos_bucket: "<<pos_bucket<<endl;
        cout<<endl;
    }
};

template <class T>
struct Bucket{
    T *records;
    int count;
    int capacity;
    int next;
    int local_depth;
    //PAGE_SIZE = 4096
    // 4096 = 4+4+4+4+FB*sizeof(Record)

    Bucket(int fb = 227){
        records = new T[fb];
        count = 0;
        capacity = fb;
        local_depth = 1;
        next = -1;
    }
    ~Bucket(){
        delete[] records;
    }


    int size(){
        return sizeof(records[0])*capacity + sizeof(count) + sizeof(capacity) + sizeof(next)+sizeof(local_depth);
    }
    void read(fstream &file){
        file.read((char*)&count,sizeof(int));
        file.read((char*)&capacity,sizeof(int));
        file.read((char*)&next,sizeof(int));
        
        for (int i = 0;  i < capacity; i++) {
            file.read((char*)&records[i],sizeof(T));
        }
    }
    void write(fstream &file){
        file.write((char*)&count,sizeof(int));
        file.write((char*)&capacity,sizeof(int));
        file.write((char*)&next,sizeof(int));
        for (int i = 0;  i < capacity; i++) {
            file.write((char*)&records[i],sizeof(T));
        }
    }
    void print(){
        cout<<"count: "<<count<<endl;
        cout<<"capacity: "<<capacity<<endl;
        cout<<"next: "<<next<<endl;
        cout<<endl;
        for (int i = 0;  i < count; i++) {
            cout<<"Codigo: "<<records[i].id<<endl;
        }
        cout<<endl;
    }
};
template <class T, typename TK>
class DynamicHash{
    string fileName_buckets;
    string fileName_index;
    int M;//global depth(cantidad de buckets)
    int FB;//factor de bloqueo
    function<TK(const T &)> get_key;
    function<unsigned long (const TK &)> hash_function;
    function<bool(const T &, const TK &)> equal_key;

public:
    DynamicHash(string fileName_buckets, string fileName_index,
                function<TK(const T &)> get_key,
                function<unsigned long(const TK &)> hash_function, 
                function<bool(const T &, const TK &)> equal_key,
                int fb = 4);

    bool add(T record);

    void aumentar_buckets(fstream &file, fstream &file2,int pos,int post_bucket,string binario,int &indice, Record record);

    bool enlazar_bucket(fstream &file,int post_bucket,T record);

    bool add(fstream &file,int post_bucket,T record);

    bool add(fstream &file, fstream &file2,string binario, int &pos, T record,int &indice);

    T search(fstream &file,int pos,TK key);

    T search(fstream &file, fstream &file2, string binary, int &pos, int &indice, TK key);

    T search(TK key);

    bool remove(TK key);

    bool remove(fstream &file, fstream &file2, string binary, int &pos, int &indice, TK key);
};
//Constructor
template <class T, typename TK>
DynamicHash<T,TK>::DynamicHash(string fileName_buckets, string fileName_index,
                                function<TK(const T &)> get_key,
                                function<unsigned long(const TK &)> hash_function,
                                function<bool(const T &, const TK &)> equal_key,
                                int fb){
    this->fileName_buckets = fileName_buckets;
    this->fileName_index = fileName_index;
    this->FB = fb;
    this->M = 0;
    this->get_key = get_key;
    this->hash_function = hash_function;
    this->equal_key = equal_key;

    fstream file(this->fileName_buckets,ios::app|ios::binary|ios::in|ios::out);
    fstream file2(this->fileName_index,ios::app|ios::binary|ios::in|ios::out);
    if(!file.is_open()) throw runtime_error("No se pudo abrir el archivo");
    if(!file2.is_open()) throw runtime_error("No se pudo abrir el archivo");

    int indece_bucket0 = file.tellg();
    //Escribir bucket 0
    Bucket<T> b(FB);
    file.seekp(0,ios::end);
    b.write(file);
    //Escribir index 0
    file2.seekp(0,ios::end);
    IndexEntry indexEntry(-1,-1,true,indece_bucket0);
    file2.write((char*)&indexEntry,sizeof(IndexEntry));

    int indece_bucket1 = file.tellg();
    //Escribir bucket 1
    Bucket<T> b1(FB);
    file.seekp(0,ios::end);
    b1.write(file);
    //Escribir index 1
    file2.seekp(0,ios::end);
    IndexEntry indexEntry1(-1,-1,true,indece_bucket1);
    file2.write((char*)&indexEntry1,sizeof(IndexEntry));

    M+=2;

    file2.close();
    file.close();
}
template <class T, typename TK>
bool DynamicHash<T,TK>::add(T record){
    fstream file(fileName_buckets,ios::binary|ios::in|ios::out);
    fstream file2(fileName_index,ios::binary|ios::in|ios::out);
    if(!file.is_open()) return false;
    if(!file2.is_open()) return false;
    string binario = to_binary(hash_function(get_key(record)));//string binario = to_binary(hash_int(record.id));
    int indice = 0;
    int pos = 0;
    if (binario[indice]=='0')pos = 0;
    else pos = 16;
    bool res = add(file,file2,binario,pos,record,indice);
    file.close();
    file2.close();
    return res;
}
template <class T, typename TK>
void DynamicHash<T,TK>::aumentar_buckets(fstream &file, fstream &file2,int pos,int post_bucket,string binario,int &indice, Record record){
    if(M<pow(2,D)){
        // Obtener bucket
        Bucket<T> bucket;
        file.seekg(post_bucket,ios::beg);
        bucket.read(file);
        // Crear dos nuevos buckets
        Bucket<T> bucket1(FB);
        Bucket<T> bucket2(FB);
        // Recorrer bucket y agregar a los nuevos buckets
        indice++;
        for (int i = 0; i < bucket.count; i++){
            string bin = to_binary(hash_function(get_key(bucket.records[i])));//string bin = to_binary(hash_int(bucket.records[i].id));
            if(bin[indice]=='0'){
                bucket1.records[bucket1.count] = bucket.records[i];
                bucket1.count++;
            }
            else{  
                bucket2.records[bucket2.count] = bucket.records[i];
                bucket2.count++;
            }
        }
        // Agregar el nuevo record
        if(binario[indice]=='0'){
            bucket1.records[bucket1.count] = record;
            bucket1.count++;
        }
        else{
            bucket2.records[bucket2.count] = record;
            bucket2.count++;
        }
        // Escribir los nuevos buckets
        file.seekp(0,ios::end);
        int pos1_buck = file.tellp();
        bucket1.write(file);
        int pos2_buck = file.tellp();
        bucket2.write(file);

        // Actualizamos el M
        M+=2;

        // Crear dos nuevos index
        IndexEntry indexEntry;
        file2.seekg(pos,ios::beg);
        file2.read((char*)&indexEntry,sizeof(IndexEntry));
        // Escribir los nuevos index
        IndexEntry indexEntry1(-1,-1,true,pos1_buck);
        IndexEntry indexEntry2(-1,-1,true,pos2_buck);

        file2.seekp(0,ios::end);
        int pos1_index = file2.tellp();
        file2.write((char*)&indexEntry1,sizeof(IndexEntry));

        file2.seekp(0,ios::end);
        int pos2_index = file2.tellp();
        file2.write((char*)&indexEntry2,sizeof(IndexEntry));

        // Actualizar el index
        indexEntry.pos_left = pos1_index;
        indexEntry.pos_right = pos2_index;
        indexEntry.isLeaf = false;
        indexEntry.pos_bucket = -1;

        file2.seekp(pos,ios::beg);
        file2.write((char*)&indexEntry,sizeof(IndexEntry));

    }
    else{
        enlazar_bucket(file,post_bucket,record);
    }

}    
template <class T, typename TK>
bool DynamicHash<T,TK>::enlazar_bucket(fstream &file,int post_bucket,T record){
    Bucket<T> bucket;
    file.seekg(post_bucket,ios::beg);
    bucket.read(file);

    // Creamos un nuevo bucket para enlazarlo
    Bucket<T> bucket1(FB);
    bucket1.records[bucket1.count] = record;
    bucket1.count++;
    file.seekp(0,ios::end);
    int pos1_buck = file.tellp();
    bucket1.write(file);

    M++;

    // Enlazamos el bucket
    bucket.next = pos1_buck;
    file.seekp(post_bucket,ios::beg);
    bucket.write(file);
    return true;
}
template <class T, typename TK>
bool DynamicHash<T,TK>::add(fstream &file,int post_bucket,T record){
    Bucket<T> bucket2;
    file.seekg(post_bucket,ios::beg);
    bucket2.read(file);
    if(bucket2.count<bucket2.capacity){
        bucket2.records[bucket2.count] = record;
        bucket2.count++;
        file.seekp(post_bucket,ios::beg);
        bucket2.write(file);
        return true;
    }
    else if(bucket2.next!=-1){
        return add(file,bucket2.next,record);
    }
    else{
        return enlazar_bucket(file,post_bucket,record);
    }
}
template <class T, typename TK>
bool DynamicHash<T,TK>::add(fstream &file, fstream &file2,string binario, int &pos, T record,int &indice){
    IndexEntry indexEntry;
    file2.seekg(pos,ios::beg);
    file2.read((char*)&indexEntry,sizeof(IndexEntry));
    if(indexEntry.pos_left==-1 && indexEntry.pos_right==-1){
        int post_bucket = indexEntry.pos_bucket;
        file.seekg(post_bucket,ios::beg);
        Bucket<T> bucket;
        bucket.read(file);
        if(bucket.count<bucket.capacity){
            bucket.records[bucket.count] = record;
            bucket.count++;
            file.seekp(post_bucket,ios::beg);
            bucket.write(file);
            file.seekg(post_bucket,ios::beg);
            bucket.read(file);
            return true;
        }
        else if(bucket.next!=-1){
                return add(file,bucket.next,record);
        }
        else{
            aumentar_buckets(file,file2,pos,post_bucket,binario,indice,record);
            return true;
        }
    }
    else{
        indice++;
        if(binario[indice]=='0'){
            pos = indexEntry.pos_left;
            return add(file,file2,binario,pos,record,indice);
            }
        else {
            pos = indexEntry.pos_right;
            return add(file,file2,binario,pos,record,indice);
        }
    }
}
template <class T, typename TK>
T DynamicHash<T,TK>::search(fstream &file,int pos,TK key){
    file.seekg(pos,ios::beg);
    Bucket<T> bucket;
    bucket.read(file);
    for (int i = 0; i < bucket.count; i++){
        if(equal_key(bucket.records[i],key)){//if(bucket.records[i].id==key){
            return bucket.records[i];
        }
    }
    if(bucket.next!=-1){
        return search(file,bucket.next,key);
    }
    else{
        return T();
    }
    return T();
}
template <class T, typename TK>
T DynamicHash<T,TK>::search(fstream &file, fstream &file2, string binary, int &pos, int &indice, TK key){
    file2.seekg(pos,ios::beg);
    IndexEntry indexEntry;
    file2.read((char*)&indexEntry,sizeof(IndexEntry));
    if(indexEntry.pos_left==-1 && indexEntry.pos_right==-1){
        int post_bucket = indexEntry.pos_bucket;
        file.seekg(post_bucket,ios::beg);
        Bucket<T> bucket;
        bucket.read(file);
        for (int i = 0; i < bucket.count; i++){
            if(equal_key(bucket.records[i],key)){//if(bucket.records[i].id==key){
                return bucket.records[i];
            }
        }
        if(bucket.next!=-1){
            return search(file,bucket.next,key);
        }
        else{
            return T();
        }
        return T();
    }
    else{
        indice++;
        if(binary[indice]=='0'){
            pos = indexEntry.pos_left;
            return search(file,file2,binary,pos,indice,key);
            }
        else {
            pos = indexEntry.pos_right;
            return search(file,file2,binary,pos,indice,key);
        }
    }
}
template <class T, typename TK>
T DynamicHash<T,TK>::search(TK key){
    string binary = to_binary(hash_function(key));//string binary = to_binary(hash_int(key));
    fstream file(fileName_buckets,ios::binary|ios::in|ios::out);
    fstream file2(fileName_index,ios::binary|ios::in|ios::out);
    int indice = 0;
    int pos = 0;
    if (binary[indice]=='0')pos = 0;
    else pos = sizeof(IndexEntry);
    T temp=search(file, file2, binary, pos, indice, key);
    file.close();
    file2.close();
    return temp;
}
template <class T, typename TK>
bool DynamicHash<T,TK>::remove(TK key){
    string binary = to_binary(hash_function(key));//string binary = to_binary(hash_int(key));
    fstream file(fileName_buckets,ios::binary|ios::in|ios::out);
    fstream file2(fileName_index,ios::binary|ios::in|ios::out);
    int indice = 0;
    int pos = 0;
    if (binary[indice]=='0')pos = 0;
    else pos = sizeof(IndexEntry);
    bool temp = remove(file, file2, binary, pos, indice, key);
    file.close();
    file2.close();
    return temp;
}
template <class T, typename TK>
bool DynamicHash<T,TK>::remove(fstream &file, fstream &file2, string binary, int &pos, int &indice, TK key){
    file2.seekg(pos,ios::beg);
    IndexEntry indexEntry;
    indexEntry.read(file2);
    if(indexEntry.pos_left==-1 && indexEntry.pos_right==-1){
        int post_bucket = indexEntry.pos_bucket;
        file.seekg(post_bucket,ios::beg);
        Bucket<T> bucket;
        bucket.read(file);
        for (int i = 0; i < bucket.count; i++){
            if(equal_key(bucket.records[i],key)){//if(bucket.records[i].id==key){
                bucket.records[i] = bucket.records[bucket.count-1];
                bucket.count--;
                file.seekp(post_bucket,ios::beg);
                bucket.write(file);
                return true;
            }
        }
        if(bucket.next!=-1){
            Bucket<T> bucket2;
            file.seekg(bucket.next,ios::beg);
            bucket2.read(file);
            for (int i = 0; i < bucket2.count; i++){
                if(equal_key(bucket2.records[i],key)){//if(bucket2.records[i].id==key){
                    bucket2.records[i] = bucket2.records[bucket2.count-1];
                    bucket2.count--;
                    file.seekp(bucket.next,ios::beg);
                    bucket2.write(file);
                    return true;
                }
            }
        }else return false;
        
    return false;
    }
    else{
        indice++;
        if(binary[indice]=='0'){
            pos = indexEntry.pos_left;
            return remove(file,file2,binary,pos,indice,key);
            }
        else {
            pos = indexEntry.pos_right;
            return remove(file,file2,binary,pos,indice,key);
        }
    }
}