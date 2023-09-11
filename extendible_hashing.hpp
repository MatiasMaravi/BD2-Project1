#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;
unsigned long long D = 3;

unsigned long hash_int(int key){
    return key%(1ULL<<D);
}
unsigned long hash_string(const std::string& str) {
    unsigned long hash = 5381;
    
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    
    return hash_int(hash);
}


// #define fb 226//4084/18
//alumno
struct Record{
    int codigo;
    char name[10];
    int ciclo;
    void setData(){
        cout<<"Codigo: ";cin>>codigo;
        cout<<"Nombre: ";cin>>name;
        cout<<"Ciclo: ";cin>>ciclo;
    }
};


struct IndexEntry{
    int left;//0
    int right;//1
    bool isLeaf;
    int pos_bucket;
};


struct Bucket{
    Record *records;
    int count;
    int capacity;
    int next;
    int local_depth;
    //PAGE_SIZE = 4096
    // 4096 = 4+4+4+4+FB*sizeof(Record)

    Bucket(int fb = 227){
        records = new Record[fb];
        count = 0;
        capacity = fb;
        local_depth = 1;
        next = -1;
    }
    int size(){
        return sizeof(records[0])*capacity + sizeof(count) + sizeof(capacity) + sizeof(next)+sizeof(local_depth);
    }
    void read(ifstream &file){
        file.read((char*)&count,sizeof(int));
        file.read((char*)&capacity,sizeof(int));
        file.read((char*)&next,sizeof(int));
        
        for (int i = 0;  i < capacity; i++) {
            file.read((char*)&records[i],sizeof(Record));
        }
    }
    void write(ofstream &file){
        file.write((char*)&count,sizeof(int));
        file.write((char*)&capacity,sizeof(int));
        file.write((char*)&next,sizeof(int));
        for (int i = 0;  i < capacity; i++) {
            file.write((char*)&records[i],sizeof(Record));
        }
    }
    void print(){
        cout<<"count: "<<count<<endl;
        cout<<"capacity: "<<capacity<<endl;
        cout<<"next: "<<next<<endl;
        for (int i = 0;  i < count; i++) {
            cout<<"Codigo: "<<records[i].codigo<<endl;
            cout<<"Nombre: "<<records[i].name<<endl;
            cout<<"Ciclo: "<<records[i].ciclo<<endl;
        }
    }
};

class DynamicHash{
    string fileName;
    int M;//global depth(cantidad de buckets)
    int FB;//factor de bloqueo

    public:
    DynamicHash(string fileName, int fb = 226){
        this->fileName = fileName;
        ifstream file(this->fileName,ios::binary);
        if(!file.good()){//No se pudo abrir, no existe
            ofstream file2(this->fileName,ios::binary);
            M = 2;
            FB = fb;
            file2.write((char*)&M,sizeof(int));
            file2.write((char*)&FB,sizeof(int));
            for (int i = 0; i < M; i++){
                Bucket b(FB);
                b.write(file2);
            }
            file2.close();
        }else{
            file.read((char*)&M,sizeof(int));
            file.read((char*)&FB,sizeof(int));
            file.close();
        }
    }
    bool add(Record record){
        //To do
        return true;
    }
    template<typename TK>
    Record search(TK key){
        string binary = to_binary(hash(key) );
        Record temp;
        return temp;
    }
    unsigned long hash_string(const std::string& str) {
    unsigned long hash = 5381;
    
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    
    return hash;
    }

    template<typename TK>
    int hash(TK key){
        if(typeid(key) == typeid(int)) return key%(1ULL<<D);
        else return hash_string(key)%(1ULL<<D);
    }
};


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
    
    return binary_string;
}

int main(){
    DynamicHash dh("data.bin");
    
    int n = 6;
    string binary = to_binary(dh.hash(6));
    cout<<binary<<endl;
    
    return 0;
}
