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
    long left = -1, right= -1, height = 0;

    void setData();
    void showData();
};
void Record::setData(){
    cout << "Codigo: ";cin >> cod;
    cout << "Nombre: ";cin >> nombre;
    cout << "Ciclo: ";cin >> ciclo;
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

    template<class TK>
    Record find(TK key);

    template<class TK>
    vector<Record> search(TK key);

    template<class TK>
    vector<Record> rangeSearch(TK begin_key,TK end_key);

    template<class TK>
    void add(TK key);


    template<class TK>
    bool remove(TK key);



private:
    void init_root();
    template <typename TK>
    Record find(long pos_node, TK key, fstream &file);

    void add(long pos_node, Record record,fstream& file);

    void inorder(long pos_node, vector<Record> &result, fstream &file);
    
    template <typename TK>
    vector<Record> search(long &pos_node,TK key);
    
    template <typename TK>
    vector<Record> rangeSearch(fstream &file, TK begin_key,TK end_key,long& pos_node,vector<Record> &result);
    
    template<typename TK>
    bool remove(long& pos_node,TK& key,fstream& file);
    
    void balancefile(long pos_node,fstream& file);
    
    int height(long pos_node,fstream& file);
    
    int balancingfactor(long pos_node,fstream& file);
    
    void leftrota(long pos_node,fstream& file);
    
    void rightrota(long pos_node,fstream& file);
    
    void updateHeight(long pos_node,fstream& file);
    
    template<class TK>
    long searchFather(fstream& file,TK& keyChild,long& pos_node);
    
    long maxleft(long& pos_node,fstream& file);
};

AVLFile::AVLFile(string filename){
    this->filename = filename;
    init_root();
}
void AVLFile::init_root(){
    fstream file(this->filename, ios::app|ios::binary | ios::in | ios::out);

    file.seekg(0, ios::end);
    int tam = file.tellg();
    (!tam)?pos_root = -1:pos_root = 0;

    file.close();
}


template<typename TK>
void AVLFile::add(TK key) {
    fstream file(this->filename, ios::binary | ios::in |ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    add(pos_root, key,file);
    file.close();
}

void AVLFile::add(long pos_node, Record record, fstream& file){
        file.seekg(0, ios::end);
        if(file.tellg() == 0){
            file.write((char*)&record, sizeof(Record));
            return;
        }

        Record curr_record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&curr_record, sizeof(Record));

        if(record.cod < curr_record.cod){
            if(curr_record.left == -1){
                file.seekp(0, ios::end);
                curr_record.left = file.tellg();
                file.write((char*)&record, sizeof(Record));
                file.seekg(pos_node, ios::beg);
                file.write((char*)&curr_record, sizeof(Record));
            }
            else
                add(curr_record.left, record, file);
        }else if(record.cod > curr_record.cod){
            if(curr_record.right == -1){
            file.seekp(0, ios::end);
            curr_record.right = file.tellg();
            file.write((char*)&record, sizeof(Record));
            file.seekg(pos_node, ios::beg);
            file.write((char*)&curr_record, sizeof(Record));
            }
        else
            add(curr_record.right, record, file);
    }
    updateHeight(pos_node, file);
    balancefile(pos_node, file);
}

template<typename TK>
Record AVLFile::find(TK key){
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
template<typename TK>
Record AVLFile::find(long pos_node, TK key, fstream &file){
    if (pos_node == -1) throw std::runtime_error("No se encontro el registro");

    file.seekg(pos_node, ios::beg);
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
    file.seekg(pos_node, ios::beg);

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
    fstream file(this->filename, ios::binary | ios::in | ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    vector<Record> result;
    rangeSearch(file, begin_key, end_key, pos_root,result);
    file.close();
    return result;
}
template<typename TK>
vector<Record> AVLFile::rangeSearch(fstream &file, TK begin_key, TK end_key ,long &pos_node, vector<Record> &result) {
    Record record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(Record));
    if (record.cod >= begin_key && record.cod <= end_key){
        result.push_back(record);
    }
    if (record.left != -1){
        rangeSearch(file,begin_key,end_key,record.left,result);
    }
    if (record.right != -1){
        rangeSearch(file,begin_key,end_key,record.right,result);
    }
    return result;
}

template<typename TK>
vector<Record> AVLFile::search(TK key) {
    ifstream file(this->filename, ios::binary | ios::in);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    return vector<Record>();
}
int AVLFile::height(long pos_node,fstream& file){
    if(pos_node == -1)
        return -1;
    Record record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(Record));
    return record.height;
}

int AVLFile::balancingfactor(long pos_node,fstream& file){
    if (pos_node == -1)
    {
        return 0;
    }
    file.seekg(pos_node,ios::beg);
    Record record;
    file.read((char*)&record, sizeof(record));
    return height(record.left,file) - height(record.right,file);
};

void AVLFile::updateHeight(long pos_node,fstream& file){

        if (pos_node == -1)
            return;

        Record record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&record, sizeof(Record));

        int left_height = height(record.left, file);
        int right_height = height(record.right, file);

        record.height = max(left_height, right_height) + 1;

        file.seekp(pos_node, ios::beg);
        file.write((char*)&record, sizeof(Record));
}

void AVLFile::balancefile(long pos_node,fstream& file) {
        if(pos_node == -1)
            return;

        Record record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&record, sizeof(Record));

        if(balancingfactor(pos_node, file) == 2){
            if(balancingfactor(record.left, file) < 0){
                leftrota(record.left, file);
            }
            rightrota(pos_node, file);
        }
        else if(balancingfactor(pos_node, file) == -2){
            if(balancingfactor(record.right, file) > 0){
                rightrota(record.right, file);
            }
            leftrota(pos_node, file);
        }
        updateHeight(pos_node, file);
}
void AVLFile::leftrota(long pos_node,fstream& file){
         Record record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&record, sizeof(Record));

        Record temp;
        long pos_temp = record.right;
        file.seekg(pos_temp, ios::beg);
        file.read((char*)&temp, sizeof(Record));

        record.right = temp.left;
        temp.left = pos_temp;

        file.seekg(pos_node, ios::beg);
        file.write((char*)&temp, sizeof(Record));

        file.seekg(pos_temp, ios::beg);
        file.write((char*)&record, sizeof(Record));

        updateHeight(pos_node, file);
        updateHeight(pos_temp, file);
}

void AVLFile::rightrota(long pos_node,fstream& file){
        Record record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&record, sizeof(Record));

        Record temp;
        long pos_temp = record.left;
        file.seekg(pos_temp, ios::beg);
        file.read((char*)&temp, sizeof(Record));

        record.left = temp.right;
        temp.right = pos_temp;

        file.seekg(pos_node, ios::beg);
        file.write((char*)&temp, sizeof(Record));

        file.seekg(pos_temp, ios::beg);
        file.write((char*)&record, sizeof(Record));

        updateHeight(pos_node, file);
        updateHeight(pos_temp, file);
}


template<typename TK>
bool AVLFile::remove(TK key) {
    fstream file(this->filename, ios::binary | ios::in |ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    bool flag = remove(pos_root, key,file);
    file.close();
    return flag;
}

template<typename TK>
bool AVLFile::remove(long& pos_node, TK& key, fstream& file) {
    if (pos_node == -1) {
        throw runtime_error("No hay elementos");
    }
    Record record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(Record));

    bool flag = false;

    if (record.cod < key) {
        flag = remove(record.right, key, file);
    } else if (record.cod > key) {
        flag = remove(record.left, key, file);
    } else {
        if (record.left == -1 && record.right == -1) {
            int fatherPo = searchFather(file,record.cod,pos_root);
            Record RecordFather;
            if (fatherPo == 0 && pos_node == 0){
                pos_root = -1;
            }
            file.seekg(fatherPo, ios::beg);
            file.read((char*)&RecordFather, sizeof(Record));
            if (RecordFather.cod > record.cod) {
                RecordFather.left = -1;

            }else{
                RecordFather.right = -1;
            }
            file.seekp(fatherPo * sizeof(Record),ios::beg);
            file.write((char*)&RecordFather,sizeof(Record));

            flag = true;
        } else if (record.left == -1 || record.right == -1) {
            Record Child;
            if ( record.left == -1) {
                file.seekg(record.right,ios::beg);
                file.read((char*)& Child,sizeof(Record));
            }else if (record.right == -1){
                file.seekg(record.left,ios::beg);
                file.read((char*)& Child,sizeof(Record));
            }
            file.seekp(pos_node * sizeof(Record),ios::beg);
            file.write((char*)&Child,sizeof(Record));
            flag = true;
        } else {
            long successorPos = maxleft(record.left, file);
            Record succesor;
            file.seekg(successorPos,ios::beg);
            file.read((char*)&succesor,sizeof(Record));
            remove(successorPos,succesor.cod,file);

            succesor.right = record.right;
            succesor.height = record.height;
            succesor.left = record.left;

            if (record.left == successorPos){
                succesor.left = -1;
            }
            file.seekp(pos_node, ios::beg);
            file.write((char*)&succesor,sizeof(Record));
            flag = true;
        }
    }
    if (flag){
        updateHeight(pos_node,file);
        balancefile(pos_node,file);
    }
    return flag;
}
template <typename TK>
long AVLFile::searchFather(fstream& file,TK& keyChild,long& pos_node){
    Record father;
    file.seekg(pos_node,ios::beg);
    file.read((char*)&father,sizeof(Record));

    long childleft = father.left;
    long childRight = father.right;

    Record Childleft;
    file.seekg(childleft,ios::beg);
    file.read((char*)&Childleft,sizeof(Record));

    Record Childright;
    file.seekg(childRight,ios::beg);
    file.read((char*)&Childright,sizeof(Record));

    long posFather= -1;
    if (keyChild == Childleft.cod || keyChild == Childright.cod){
        posFather =pos_node;
    }

    if (posFather != -1){
        return posFather;
    }else{
        if (father.cod > keyChild){
            searchFather<TK>(file,keyChild, childleft);
        }else if(father.cod < keyChild){
            searchFather<TK>(file,keyChild,childRight);
        }else {
            throw std::runtime_error("No se encontro otro valor");
        }
        return pos_node;
    }
}

long AVLFile::maxleft(long& pos_node, std::fstream &file) {
    Record record;
    file.seekg(pos_node,ios::beg);
    file.read((char*)&record,sizeof(Record));
    if (record.right == -1){
        return  pos_node;
    }else{
        maxleft(record.right,file);
    }
    return -1;
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
void Readrange(){
    AVLFile file("data.bin");
    int begin_key,end_key;
    cout<<"Ingrese el codigo de inicio: ";cin>>begin_key;
    cout<<"Ingrese el codigo de fin: ";cin>>end_key;
    vector<Record> result = file.rangeSearch(begin_key,end_key);
    cout<<"\n--------- Show a data finded -----------\n";
    for(Record re : result) {
        re.showData();
    };
};

void Delete(){
    AVLFile file("data.bin");
    int Key;
    cout<<"Ingrese el codigo a borrar: "; cin>>Key;
    bool flag = file.remove(Key);
    if (flag){
        cout<<"Eliminado con exito"<<endl;
    }else{
        cout<<"No se pudo eliminar"<<endl;
    }
};
string menu(){
    string op;
    cout<<"\n--------- Menu -----------\n";
    cout<<"1. Escribir en el archivo"<<endl;
    cout<<"2. Leer todos los registros"<<endl;
    cout<<"3 Buscar un registro"<<endl;
    cout<<"4 Busqueda en un rango"<<endl;
    cout<<"5 Eliminar un registro"<<endl;
    cout<<"6 Salir"<<endl;
    cout<<"Ingrese una opcion: ";cin>>op;
    return op;
}


void test(){
    string op = menu();
    if(op == "1") writeFile();
    else if(op == "2") readFile();
    else if(op == "3") ReadOne();
    else if(op == "4") Readrange();
    else if(op == "5") Delete();
    else if(op == "6") exit(0);
    else cout<<"Opcion incorrecta"<<endl;
}


int main(){
    test();
    return 0;
}