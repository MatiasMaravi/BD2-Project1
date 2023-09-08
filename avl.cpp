//
// Created by jerimy on 3/09/23.
//
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

struct Record
{
    int cod;
    char nombre[12];
    int ciclo;
    long left, right, height;

    void setData();
    void showData();
};
void Record::setData(){
    cout << "Codigo: ";cin >> cod;
    cout << "Nombre: ";cin >> nombre;
    cout << "Ciclo: ";cin >> ciclo;
    left = -1;
    right = -1;
    height = -1;
}
void Record::showData(){
    cout << "\nCodigo: " << cod;
    cout << "\nNombre: " << nombre;
    cout << "\nCiclo : " << ciclo;
    cout << "\nleft : " << left;
    cout << "\nright : " << right <<endl;
    cout << "\nheight : " << height <<endl;
};

class AVLFile {
private:
    string filename;
    long pos_root;
public:

    AVLFile(string filename);
    vector<Record> inorder();
    Record find(int key);
    template<class TK>
    vector<Record> search(TK key);
    template<class TK>
    vector<Record> rangeSearch(TK begin_key,TK end_key);
    template<class TK>
    bool add(TK key);
    template<class TK>
    bool remove(TK key);
private:
    void init_root();
    Record find(long pos_node, int key, fstream &file);
    bool add(long &pos_node, Record record,fstream& file);
    void inorder(long pos_node, vector<Record> &result, fstream &file);
    template <typename TK>
    vector<Record> search(long &pos_node,TK key);
    template <typename TK>
    vector<Record> rangeSearch(long& pos_node, TK begin_key,TK end_key);
    template<typename TK>
    bool remove(long& pos_node,TK key);
    void balancefile(long& pos_node,Record father,fstream& file);
    int Record_height(long& pos_node,fstream& file);
    int balancingfactor(long& pos_node,fstream& file);
    void leftrota(long& pos_node,fstream& file);
    void rightrota(long& pos_node,fstream& file);
    void updatHeight(long& pos_node,fstream& file);
};

AVLFile::AVLFile(string filename){
    this->filename = filename;
    init_root();
}

Record AVLFile::find(int key){
    fstream file(this->filename, ios::app | ios::binary | ios::in | ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    Record record = find(pos_root,key,file);
    file.close();
    return record;
}

vector<Record> AVLFile::inorder(){
    fstream file(this->filename, ios::app | ios::binary | ios::in | ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");

    vector<Record> result;
    inorder(pos_root, result, file);

    file.close();
    return result;
}

void AVLFile::init_root(){
    fstream file(this->filename, ios::app|ios::binary | ios::in | ios::out);

    file.seekg(0, ios::end);
    int tam = file.tellg();
    (!tam)?pos_root = -1:pos_root = 0;

    file.close();
}
Record AVLFile::find(long pos_node, int key, fstream &file){
    if (pos_node == -1) throw std::runtime_error("No se encontro el registro");

    file.seekg(pos_node * sizeof(Record), ios::beg);
    Record record;
    file.read((char*) &record, sizeof(Record));

    if(record.cod == key) return record;
    else if(record.cod > key) return find(record.left, key, file);
    else return find(record.right, key, file);
}

void AVLFile::inorder(long pos_node, vector<Record> &result, fstream &file){
    // Si no encuentra ningun nodo
    if (pos_node == -1)
        return;

    // Desplazar el cursor hacia la posicion deseada
    file.seekg(pos_node * sizeof(Record), ios::beg);

    // Leyendo "record"
    Record record;
    file.read((char*) &record, sizeof(Record));

    // Logica "InOrder"
    inorder(record.left, result, file);
    result.push_back(record);
    inorder(record.right, result, file);
}

template<typename TK>
vector<Record> AVLFile::rangeSearch(TK begin_key, TK end_key) {
    vector<Record> result;
    while (begin_key++ != end_key){
        Record record;
        record = find(begin_key);
        result.push_back(record);
    };
    return result;
}

template<typename TK>
vector<Record> AVLFile::search(TK key) {
    ifstream file(this->filename, ios::binary | ios::in);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    return vector<Record>();
}

template<typename TK>
bool AVLFile::add(TK key) {
    fstream file(this->filename, ios::binary | ios::in |ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    bool flag = add(pos_root, key,file);
    file.close();
    return flag;
}

bool AVLFile::add(long &pos_node, Record record,fstream& file) {
    if (pos_node == -1){
        file.seekp(0, ios::end);
        pos_node = file.tellg() / sizeof(Record);
        record.height = record.height+1;
        file.write((char*)&record, sizeof(record));
        return true;
    }else{
        file.seekg(pos_node * sizeof(Record),ios::beg);
        Record father;
        file.read((char*)&father, sizeof(Record));
        father.height = father.height +1;

        if(record.cod < father.cod){
            add(father.left, record,file);
            file.seekp(pos_node * sizeof(Record), ios::beg);
            file.write((char*)&father, sizeof(Record));
        }else if(record.cod > father.cod){
            add(father.right, record,file);
            file.seekp(pos_node * sizeof(Record), ios::beg);
            file.write((char*)&father, sizeof(Record));
        }
        balancefile(pos_node,father,file);
        return false;
    }
}
int AVLFile::Record_height(long& pos_node,fstream& file){
    if (pos_node == -1) {
        return -1;
    }else{
        file.seekg(pos_node * sizeof(Record),ios::beg);
        Record record;
        file.read((char*)&record, sizeof(record));
        int size= record.height;
        return size;
    }
}

int AVLFile::balancingfactor(long& pos_node,fstream& file){
    file.seekg(pos_node * sizeof(Record),ios::beg);
    Record record;
    file.read((char*)&record, sizeof(record));
    long pos_node_right = record.right;
    long pos_node_left = record.left;
    return Record_height(pos_node_left,file) - Record_height(pos_node_right,file);
};

void AVLFile::balancefile(long &pos_node,Record father,fstream& file) {
    //Record father innecesario
    file.seekg( sizeof(Record) * pos_node,ios::beg);
    Record parent;
    file.read((char*)&parent, sizeof(Record));
    if(balancingfactor(pos_node,file) > 1){
        if (balancingfactor(parent.left,file) < 0){
            leftrota(parent.left,file);
        }
        rightrota(pos_node,file);
    }else if (balancingfactor(pos_node,file) < -1){
        if (balancingfactor(parent.right,file) > 0){
            rightrota(parent.right,file);
        }
        leftrota(pos_node,file);
    }
}
void AVLFile::leftrota(long& pos_node,fstream& file){
    file.seekg(pos_node * sizeof(Record),ios::beg);
    Record record_father;
    file.read((char*)&record_father, sizeof(Record));

    long childright = record_father.right;

    Record childRight;
    file.seekg(childright * sizeof(Record),ios::beg);
    file.read((char*)& childRight, sizeof(Record));

    int temp = childRight.left;
    childRight.left = record_father.right;

    file.seekp(pos_node * sizeof(Record),ios::beg);
    file.write((char*)&childRight,sizeof(Record));

    int pos_right = record_father.right;
    record_father.right = temp;

    file.seekp(pos_right * sizeof(Record),ios::beg);
    file.write((char*)&record_father, sizeof(Record));

    Record pos_node_Right;
    file.seekg(pos_node *sizeof (Record),ios::beg);
    file.read((char*)& pos_node_Right, sizeof(Record));
    
    updatHeight(pos_node_Right.left,file);
    updatHeight(pos_node,file);
}

void AVLFile::rightrota(long& pos_node,fstream& file){
    file.seekg(pos_node * sizeof(Record),ios::beg);
    Record record_father;
    file.read((char*)&record_father, sizeof(Record));

    long childleft = record_father.left;

    Record childLeft;
    file.seekg(childleft * sizeof(Record),ios::beg);
    file.read((char*)& childLeft, sizeof(Record));
    int temp = childLeft.right;
    childLeft.right = record_father.left;

    file.seekp(pos_node * sizeof(Record),ios::beg);
    file.write((char*)&childLeft, sizeof(Record));

    int pos_left = record_father.left;
    record_father.left = temp;

    file.seekp(pos_left * sizeof(Record),ios::beg);
    file.write((char*)&record_father, sizeof(Record));

    Record pos_node_Left;
    file.seekg(pos_node * sizeof(Record),ios::beg);
    file.read((char*)& pos_node_Left, sizeof(Record));

    updatHeight(pos_node_Left.right,file);
    updatHeight(pos_node,file);
}
void AVLFile::updatHeight(long& pos_node,fstream& file){
    Record father;
    file.seekg(pos_node * sizeof(Record),ios::beg);
    file.read((char*)&father,sizeof(Record));

    long child_pos_left = father.left;
    long child_pos_right = father.right;
    
    if (child_pos_left == -1 && child_pos_right == -1){
        father.height = 0;
        file.seekp(pos_node * sizeof(Record),ios::beg);
        file.write((char*)&father,sizeof(Record));
    }else{
        Record record_left;
        file.seekg(child_pos_left * sizeof(Record),ios::beg);
        file.read((char*)&record_left, sizeof(Record));

        Record record_right;
        file.seekg(child_pos_right * sizeof(Record),ios::beg);
        file.read((char*)&record_right, sizeof(Record));
        if (record_left.left == -1 && record_left.right == -1){
            record_left.height = 0;
        }
        if (record_right.left == -1 && record_right.right == -1){
            record_right.height = 0;
        }
        father.height = max(record_left.height, record_right.height) + 1;
        file.seekp(pos_node * sizeof(Record),ios::beg);
        file.write((char*)&father,sizeof(Record));
    }
}

template<typename TK>
bool AVLFile::remove(TK key) {

    return 0;
}

void writeFile(){
    AVLFile file("data.bin");
    Record record;
    int n = 0;
    cout<<"Ingrese el numero de registros: ";cin>>n;
    for (int i = 0; i < n; i++) {
        record.setData();
        file.add(record);
    }
    cout<<"Se guardo correctamente"<<endl;
}

void readFile(){
    AVLFile file("data.bin");
    cout<<"--------- Show all sorted data -----------\n";
    vector<Record> result = file.inorder();
    for(Record re : result) {
        re.showData();
    }
}
void ReadOne(){
    AVLFile file("data.bin");
    int key;
    cout<<"Ingrese el codigo a buscar: ";cin>>key;
    try{
        Record record = file.find(key);
        cout<<"\n--------- Show a data finded -----------\n";
        record.showData();
    }catch(exception e){
        cout<<"Registro no encontrado"<<endl;
    }
}
string menu(){
    string op;
    cout<<"\n--------- Menu -----------\n";
    cout<<"1. Escribir en el archivo"<<endl;
    cout<<"2. Leer todos los registros"<<endl;
    cout<<"3. Buscar un registro"<<endl;
    cout<<"4. Salir"<<endl;
    cout<<"Ingrese una opcion: ";cin>>op;
    return op;
}
void test(){
    string op = menu();
    if(op == "1") writeFile();
    else if(op == "2") readFile();
    else if(op == "3") ReadOne();
    else if(op == "4") exit(0);
    else cout<<"Opcion incorrecta"<<endl;
}


int main(){

    test();
    return 0;
}