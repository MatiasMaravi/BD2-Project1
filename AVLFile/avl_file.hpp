#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
#include <functional>
#include "../Record_avl.h"
using namespace std;
//struct Record
//{
//    int cod;
//    char nombre[12];
//    int ciclo;
//    long left = -1, right = -1;
//    int height = 0;
//    void setData();
//    void showData();
//};
//void Record::setData(){
//    cout << "Codigo: ";cin >> cod;
//    cout << "Nombre: ";cin >> nombre;
//    cout << "Ciclo: ";cin >> ciclo;
//}
//
//void Record::showData(){
//    cout << "\nCodigo: " << cod;
//    cout << "\nNombre: " << nombre;
//    cout << "\nCiclo : " << ciclo;
//    cout << "\nleft : " << left;
//    cout << "\nright : " << right <<endl;
//    cout << "\nheight : " << height <<endl;
//};

template <class T, typename TK>
class AVLFile{
private:
    string filename;
    long pos_root;
    std::function<bool(const T &, const T &)> less;
    std::function<bool(const T &, const T &)> greater;
    std::function<bool(const T &, const TK &)> equal_key;
    std::function<bool(const T &, const TK &)> less_key;
    std::function<bool(const T &, const TK &)> greater_key;
    std::function<TK(const T &)> get_key;
    static AVLFile<T, TK>* instance;
public:
    AVLFile(string filename,
            function<bool(const T &, const T &)> less,
            function<bool(const T &, const T &)> greater,
            function<bool(const T &, const TK &)> equal_key,
            function<bool(const T &, const TK &)> less_key,
            function<bool(const T &, const TK &)> greater_key,
            function<TK(const T &)> get_key);

    static AVLFile<T, TK>& getInstance(string filename,
                                              function<bool(const T &, const T &)> less,
                                              function<bool(const T &, const T &)> greater,
                                              function<bool(const T &, const T &)> equal_key,

                                              function<bool(const T &, const TK &)> less_key,
                                              function<bool(const T &, const TK &)> greater_key,
                                              function<TK(const T &)> get_key) {
        static AVLFile<T, TK> instance(filename, less, greater, equal_key, less_key, greater_key);
        return instance;
    }

    T find(TK key);

    void insert(T record);

    bool remove(TK key);

    vector<T> inorder();

    vector<T> rangeSearch(TK begin_key, TK end_key);
    ~AVLFile() {
        delete instance;
    }

private:
    void inorder(long pos_node, vector<T> &result, fstream &file);

    T find(long pos_node, TK key, fstream &file);

    void insert(long pos_node, T record, fstream& file);

    bool remove(long pos_node, TK key, fstream& file);
    
    long maxleft(long& pos_node, fstream &file);

    long searchFather(fstream& file,TK& keyChild,long& pos_node);

    void searchRange(long pos_node, TK start, TK end, vector<T>& result, ifstream& file);
    
    int height(long pos_node, fstream& file);
    
    void updateHeight(long pos_node, fstream& file);
    
    int balancingFactor(long pos_node, fstream& file);

    void balance(long pos_node, fstream& file);
    
    void left_rota(long pos_node, fstream& file);
    
    void right_rota(long pos_node, fstream& file);

    vector<T> rangeSearch(fstream &file, TK begin_key, TK end_key ,long &pos_node, vector<T> &result);
};
//Constructor
template<class T, typename TK>
AVLFile<T, TK>::AVLFile(string filename,
                    function<bool(const T &, const T &)> less,
                    function<bool(const T &, const T &)> greater,
                    function<bool(const T &, const TK &)> equal_key,
                    function<bool(const T &, const TK &)> less_key,
                    function<bool(const T &, const TK &)> greater_key,
                    function<TK(const T &)> get_key) {
    this->pos_root = 0;
    this->filename = filename;
    this->less = less;
    this->greater = greater;
    this->equal_key = equal_key;
    this->less_key = less_key;
    this->greater_key = greater_key;
    this->get_key = get_key;

    ifstream file(filename, ios::app | ios::binary);

    if(!file.good()){
        file.close();
        ofstream f(filename, ios::app | ios::binary);
        f.close();
    }

}
template<class T, typename TK>
T AVLFile<T,TK>::find(TK key){
    fstream file(this->filename, ios::app | ios::binary | ios::in | ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    T record = find(pos_root,key,file);
    file.close();
    return record;
}
template<class T, typename TK>
void AVLFile<T,TK>::insert(T record){
    fstream file(this->filename, ios::in | ios::out | ios::binary);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    insert(pos_root, record, file);
    file.close();
}

template<class T, typename TK>
bool AVLFile<T,TK>::remove(TK key) {
    fstream file(this->filename, ios::binary | ios::in |ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    bool flag = remove(pos_root, key,file);
    file.close();
    return flag;
}

template<class T, typename TK>
vector<T> AVLFile<T,TK>::inorder(){
    fstream file(this->filename, ios::app | ios::binary | ios::in | ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");

    vector<T> result;
    inorder(pos_root, result, file);

    file.close();
    return result;
}

template<class T, typename TK>
vector<T> AVLFile<T,TK>::rangeSearch(TK begin_key, TK end_key) {
    fstream file(this->filename, ios::binary | ios::in | ios::out);
    if (!file.is_open()) throw std::runtime_error("No se pudo abrir el archivo");
    vector<T> result;
    rangeSearch(file, begin_key, end_key, pos_root,result);
    file.close();
    return result;
}

template<class T, typename TK>
void AVLFile<T,TK>::inorder(long pos_node, vector<T> &result, fstream &file){
    if (pos_node == -1)
        return;
    file.seekg(pos_node, ios::beg);
    T record;
    file.read((char*) &record, sizeof(T));

    inorder(record.left, result, file);
    result.push_back(record);
    inorder(record.right, result, file);
}  

template<class T, typename TK>
T AVLFile<T,TK>::find(long pos_node, TK key, fstream &file){
    if (pos_node == -1) throw std::runtime_error("No se encontro el registro");

    file.seekg(pos_node, ios::beg);
    T record;
    file.read((char*) &record, sizeof(Record_avl));

    if(equal_key(record,key))return record; //if(record.cod == key) return record;
    else if(greater_key(record,key)) return find(record.left, key, file); //else if(record.cod > key) return find(record.left, key, file);
    else return find(record.right, key, file);
}

template<class T, typename TK>
void AVLFile<T,TK>::insert(long pos_node, T record, fstream& file){
    file.seekg(0, ios::end);

    if(file.tellg() == 0){
        file.write((char*)&record, sizeof(T));
        return;
    }

    T RecordCurrent;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&RecordCurrent, sizeof(T));

    if(less(record,RecordCurrent)){ //if(record.cod < RecordCurrent.cod){
        if(RecordCurrent.left == -1){
            file.seekp(0, ios::end);
            RecordCurrent.left = file.tellg();
            file.write((char*)&record, sizeof(Record_avl));
            file.seekg(pos_node, ios::beg);
            file.write((char*)&RecordCurrent, sizeof(Record_avl));
        }
        else
            insert(RecordCurrent.left, record, file);
    }else if(greater(record,RecordCurrent)){//}else if(record.cod > RecordCurrent.cod){
        if(RecordCurrent.right == -1){
            file.seekp(0, ios::end);
            RecordCurrent.right = file.tellg();
            file.write((char*)&record, sizeof(Record_avl));
            file.seekg(pos_node, ios::beg);
            file.write((char*)&RecordCurrent, sizeof(Record_avl));
        }
        else
            insert(RecordCurrent.right, record, file);
    }

    updateHeight(pos_node, file);
    balance(pos_node, file);

}
template<class T, typename TK>
bool AVLFile<T,TK>::remove(long pos_node, TK key, fstream& file){
    if (pos_node == -1) {
        throw runtime_error("No hay elementos");
    }
    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));

    bool flag = false;

    if (less_key(record,key)) {//if (record.cod < key) {
        flag = remove(record.right, key, file);
    } else if (greater_key(record,key)) {//} else if (record.cod > key) {
        flag = remove(record.left, key, file);
    } else {
        if (record.left == -1 && record.right == -1) {
            TK aux = get_key(record);//int aux = record.cod;
            int fatherPo = searchFather(file,aux,pos_root);//int fatherPo = searchFather(file,record.cod,pos_root);
            T RecordFather;
            if (fatherPo == 0 && pos_node == 0){
                pos_root = -1;
            }
            file.seekg(fatherPo, ios::beg);
            file.read((char*)&RecordFather, sizeof(T));
            if (greater(RecordFather,record)) {//if (RecordFather.cod > record.cod) {
                RecordFather.left = -1;

            }else{
                RecordFather.right = -1;
            }
            file.seekp(fatherPo * sizeof(T),ios::beg);
            file.write((char*)&RecordFather,sizeof(T));

            flag = true;
        } else if (record.left == -1 || record.right == -1) {
            T Child;
            if ( record.left == -1) {
                file.seekg(record.right,ios::beg);
                file.read((char*)& Child,sizeof(T));
            }else if (record.right == -1){
                file.seekg(record.left,ios::beg);
                file.read((char*)& Child,sizeof(T));
            }
            file.seekp(pos_node * sizeof(T),ios::beg);
            file.write((char*)&Child,sizeof(T));
            flag = true;
        } else {
            long successorPos = maxleft(record.left, file);
            T succesor;
            file.seekg(successorPos,ios::beg);
            file.read((char*)&succesor,sizeof(Record_avl));
            remove(successorPos,get_key(succesor),file);//remove(successorPos,succesor.cod,file);

            succesor.right = record.right;
            succesor.height = record.height;
            succesor.left = record.left;

            if (record.left == successorPos){
                succesor.left = -1;
            }
            file.seekp(pos_node, ios::beg);
            file.write((char*)&succesor,sizeof(Record_avl));
            flag = true;
        }
    }
    if (flag){
        updateHeight(pos_node,file);
        balance(pos_node,file);
        }
    return flag;
}
template<class T, typename TK>
long AVLFile<T,TK>::maxleft(long& pos_node, std::fstream &file) {
    T record;
    file.seekg(pos_node,ios::beg);
    file.read((char*)&record,sizeof(T));
    if (record.right == -1){
        return  pos_node;
    }else{
        maxleft(record.right,file);
    }
    return -1;
}
template<class T, typename TK>
long AVLFile<T,TK>::searchFather(fstream& file,TK& keyChild,long& pos_node){
    T father;
    file.seekg(pos_node,ios::beg);
    file.read((char*)&father,sizeof(T));

    long childleft_pos = father.left;
    long childRight_pos = father.right;

    T Childleft;
    file.seekg(childleft_pos,ios::beg);
    file.read((char*)&Childleft,sizeof(T));

    T Childright;
    file.seekg(childRight_pos,ios::beg);
    file.read((char*)&Childright,sizeof(T));

    long posFather= -1;
    if (equal_key(Childleft,keyChild) || equal_key(Childright,keyChild)){//if (keyChild == Childleft.cod || keyChild == Childright.cod){
        posFather =pos_node;
    }

    if (posFather != -1){
        return posFather;
    }else{
        if (greater_key(father, keyChild)){//if (father.cod > keyChild){
            searchFather(file, keyChild, childleft_pos);
        }else if(less_key(father,keyChild)){//}else if(father.cod < keyChild){
            searchFather(file, keyChild, childRight_pos);
        }else {
            return 0;
        }
        return pos_node;
        }
}
template<class T, typename TK>
void AVLFile<T,TK>::searchRange(long pos_node, TK start, TK end, vector<T>& result, ifstream& file){
    if(pos_node == -1)
        return;
    T curr_record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&curr_record, sizeof(T));

    if((greater_key(curr_record,start) || equal_key(curr_record,start)) && (less_key(curr_record,end) || equal_key(curr_record,end))){//if(curr_record.cod >= start && curr_record.cod <= end){
        result.push_back(curr_record);
        searchRange(curr_record.left, start, end, result, file);
        searchRange(curr_record.right, start, end, result, file);
    }
    else if(less_key(curr_record,start))//else if(curr_record.cod < start)
        searchRange(curr_record.right, start, end, result, file);
    else if(greater_key(curr_record,end))//else if(curr_record.cod > end)
        searchRange(curr_record.left, start, end, result, file);
}
template<class T, typename TK>
int AVLFile<T,TK>::height(long pos_node, fstream& file){
    if(pos_node == -1)
        return -1;
    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));
    return record.height;
}
template<class T, typename TK>
void AVLFile<T,TK>::updateHeight(long pos_node, fstream& file){
    if (pos_node == -1)
        return;

    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));

    int left_height = height(record.left, file);
    int right_height = height(record.right, file);

    record.height = max(left_height, right_height) + 1;

    file.seekp(pos_node, ios::beg);
    file.write((char*)&record, sizeof(T));
}
template<class T, typename TK>
int AVLFile<T,TK>::balancingFactor(long pos_node, fstream& file){
    if(pos_node == -1)
        return 0;
    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));
    return height(record.left, file) - height(record.right, file);
}
template<class T, typename TK>
void AVLFile<T,TK>::balance(long pos_node, fstream& file){
    if(pos_node == -1)
        return;

    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));

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
template<class T, typename TK>
void AVLFile<T,TK>::left_rota(long pos_node, fstream& file){
    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));

    T temp;
    long pos_temp = record.right;
    file.seekg(pos_temp, ios::beg);
    file.read((char*)&temp, sizeof(T));

    record.right = temp.left;
    temp.left = pos_temp;

    file.seekg(pos_node, ios::beg);
    file.write((char*)&temp, sizeof(T));

    file.seekg(pos_temp, ios::beg);
    file.write((char*)&record, sizeof(T));

    updateHeight(pos_node, file);
    updateHeight(pos_temp, file);
}
template<class T, typename TK>
void AVLFile<T,TK>::right_rota(long pos_node, fstream& file){
    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));

    T temp;
    long pos_temp = record.left;
    file.seekg(pos_temp, ios::beg);
    file.read((char*)&temp, sizeof(T));

    record.left = temp.right;
    temp.right = pos_temp;

    file.seekg(pos_node, ios::beg);
    file.write((char*)&temp, sizeof(T));

    file.seekg(pos_temp, ios::beg);
    file.write((char*)&record, sizeof(Record_avl));

    updateHeight(pos_node, file);
    updateHeight(pos_temp, file);
}   
template<class T, typename TK>
vector<T> AVLFile<T,TK>::rangeSearch(fstream &file, TK begin_key, TK end_key ,long &pos_node, vector<T> &result) {
    T record;
    file.seekg(pos_node, ios::beg);
    file.read((char*)&record, sizeof(T));
    if ((greater_key(record,begin_key) || equal_key(record,begin_key)) && (less_key(record,end_key) || equal_key(record,end_key))){//if (record.cod >= begin_key && record.cod <= end_key){
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