#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;
struct Record
{
    int cod;
    char nombre[12];
    int ciclo;
    long left = -1, right = -1;
    int height = 0;
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

class AVLFile
{
private:
    string filename;
    long pos_root;
public:
    AVLFile(string filename){
        this->pos_root = 0;
        this->filename = filename;

        ifstream file(filename, ios::app | ios::binary);

        if(!file.good()){
            file.close();
            ofstream f(filename, ios::app | ios::binary);
            f.close();
        }

    }

    Record find(int key){
        fstream file(this->filename, ios::app | ios::binary | ios::in | ios::out);
        if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
        Record record = find(pos_root,key,file);
        file.close();
        return record;
    }

    void insert(Record record){
        fstream file(this->filename, ios::in | ios::out | ios::binary);
        if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
        insert(pos_root, record, file);
        file.close();
    }

    template<typename TK>
    bool remove(TK key) {
        fstream file(this->filename, ios::binary | ios::in |ios::out);
        if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
        bool flag = remove(pos_root, key,file);
        file.close();
        return flag;
    }

    vector<Record> inorder(){
        fstream file(this->filename, ios::app | ios::binary | ios::in | ios::out);
        if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");

        vector<Record> result;
        inorder(pos_root, result, file);

        file.close();
        return result;
    }
    template<typename TK>
    vector<Record> rangeSearch(TK begin_key, TK end_key) {
        fstream file(this->filename, ios::binary | ios::in | ios::out);
        if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
        vector<Record> result;
        rangeSearch(file, begin_key, end_key, pos_root,result);
        file.close();
        return result;
    }

private:
    void inorder(long pos_node, vector<Record> &result, fstream &file){
        if (pos_node == -1)
            return;
        file.seekg(pos_node, ios::beg);
        Record record;
        file.read((char*) &record, sizeof(Record));

        inorder(record.left, result, file);
        result.push_back(record);
        inorder(record.right, result, file);
    }   

    template<typename TK>
    Record find(long pos_node, TK key, fstream &file){
        if (pos_node == -1) throw std::runtime_error("No se encontro el registro");

        file.seekg(pos_node, ios::beg);
        Record record;
        file.read((char*) &record, sizeof(Record));

        if(record.cod == key) return record;
        else if(record.cod > key) return find(record.left, key, file);
        else return find(record.right, key, file);
    }

    void insert(long pos_node, Record record, fstream& file){
        file.seekg(0, ios::end);

        if(file.tellg() == 0){
            file.write((char*)&record, sizeof(Record));
            return;
        }

        Record RecordCurrent;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&RecordCurrent, sizeof(Record));

        if(record.cod < RecordCurrent.cod){
            if(RecordCurrent.left == -1){
                file.seekp(0, ios::end);
                RecordCurrent.left = file.tellg();
                file.write((char*)&record, sizeof(Record));
                file.seekg(pos_node, ios::beg);
                file.write((char*)&RecordCurrent, sizeof(Record));
            }
            else
                insert(RecordCurrent.left, record, file);
        }else if(record.cod > RecordCurrent.cod){
            if(RecordCurrent.right == -1){
                file.seekp(0, ios::end);
                RecordCurrent.right = file.tellg();
                file.write((char*)&record, sizeof(Record));
                file.seekg(pos_node, ios::beg);
                file.write((char*)&RecordCurrent, sizeof(Record));
            }
            else
                insert(RecordCurrent.right, record, file);
        }

        updateHeight(pos_node, file);
        balance(pos_node, file);

    }

    template <class T>
    bool remove(long pos_node, T key, fstream& file){
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
        balance(pos_node,file);
    }
    return flag;
    }
    long maxleft(long& pos_node, std::fstream &file) {
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
    template <typename TK>
    long searchFather(fstream& file,TK& keyChild,long& pos_node){
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
            return 0;
        }
        return pos_node;
        }
    }


    void searchRange(long pos_node, int start, int end, vector<Record>& result, ifstream& file){
        if(pos_node == -1)
            return;
        Record curr_record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&curr_record, sizeof(Record));

        if(curr_record.cod >= start && curr_record.cod <= end){
            result.push_back(curr_record);
            searchRange(curr_record.left, start, end, result, file);
            searchRange(curr_record.right, start, end, result, file);
        }
        else if(curr_record.cod < start)
            searchRange(curr_record.right, start, end, result, file);
        else if(curr_record.cod > end)
            searchRange(curr_record.left, start, end, result, file);
    }


    int height(long pos_node, fstream& file){
        if(pos_node == -1)
            return -1;
        Record record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&record, sizeof(Record));
        return record.height;
    }

    void updateHeight(long pos_node, fstream& file){
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

    int balancingFactor(long pos_node, fstream& file){
        if(pos_node == -1)
            return 0;
        Record record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&record, sizeof(Record));
        return height(record.left, file) - height(record.right, file);
    }

    void balance(long pos_node, fstream& file){
        if(pos_node == -1)
            return;

        Record record;
        file.seekg(pos_node, ios::beg);
        file.read((char*)&record, sizeof(Record));

        if(balancingFactor(pos_node, file) == 2){
            if(balancingFactor(record.left, file) < 0){
                left_rota(record.left, file);
            }
            right_rota(pos_node, file);
        }
        else if(balancingFactor(pos_node, file) == -2){
            if(balancingFactor(record.right, file) > 0){
                right_rota(record.right, file);
            }
            left_rota(pos_node, file);
        }
        updateHeight(pos_node, file);
    }

    void left_rota(long pos_node, fstream& file){
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

    void right_rota(long pos_node, fstream& file){
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
    vector<Record> rangeSearch(fstream &file, TK begin_key, TK end_key ,long &pos_node, vector<Record> &result) {
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
};


void writeFile(){
    AVLFile file("data.bin");
    Record record;
    int n = 0;
    cout<<"Ingrese el numero de registros: ";cin>>n;
    for (int i = 0; i < n; i++) {
        record.setData();
        file.insert(record);
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
    else if(op == "4") Readrange();
    else if(op == "3") ReadOne();
    else if(op == "5") Delete();
    else if(op == "6") exit(0);
    else cout<<"Opcion incorrecta"<<endl;
}

int main(){
    test();
    return 0;
}