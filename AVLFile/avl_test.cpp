#include"avl_file.hpp"

template<class T, typename TK>
void writeFile(AVLFile<T,TK>& file){
    T record;
    int n = 0;
    cout<<"Ingrese el numero de registros: ";cin>>n;
    for (int i = 0; i < n; i++) {
        record.setData();
        file.insert(record);
    }
    cout<<"Se guardo correctamente"<<endl;
}
template<class T, typename TK>
void readFile(AVLFile<T,TK>& file){
    cout<<"--------- Show all sorted data -----------\n";
    vector<T> result = file.inorder();
    for(T re : result) {
        re.showData();
    }
}
template<class T, typename TK>
void ReadOne(AVLFile<T,TK>& file){
    TK key;
    cout<<"Ingrese el codigo a buscar: ";cin>>key;
    try{
        T record = file.find(key);
        cout<<"\n--------- Show a data finded -----------\n";
        record.showData();
    }catch(exception e){
        cout<<"Registro no encontrado"<<endl;
    }
}
template<class T, typename TK>
void Readrange(AVLFile<T,TK>& file){
    TK begin_key,end_key;
    cout<<"Ingrese el codigo de inicio: ";cin>>begin_key;
    cout<<"Ingrese el codigo de fin: ";cin>>end_key;
    vector<T> result = file.rangeSearch(begin_key,end_key);
    cout<<"\n--------- Show a data finded -----------\n";
    for(T re : result) {
        re.showData();
    };
};
template<class T, typename TK>
void Delete(AVLFile<T,TK>& file){
    TK Key;
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
template<class T, typename TK>
void test(AVLFile<T,TK>& file){
    string op = menu();
    if(op == "1") writeFile(file);
    else if(op == "2") readFile(file);
    else if(op == "4") Readrange(file);
    else if(op == "3") ReadOne(file);
    else if(op == "5") Delete(file);
    else if(op == "6") exit(0);
    else cout<<"Opcion incorrecta"<<endl;
}

int main(){
    //key = cod
    // AVLFile<Record,int> file("data.dat",
    //                 []( Record const&a, Record const&b) { return a.cod < b.cod;}, //less
    //                 []( Record const&a, Record const&b) { return a.cod > b.cod;}, //greater
    //                 []( Record const&a, int const&b) { return a.cod == b;}, //equal_key
    //                 []( Record const&a, int const&b) { return a.cod < b;}, //less_key
    //                 []( Record const&a, int const&b) { return a.cod > b;}, //greater_key
    //                 []( Record const&a) { return a.cod;} //get_key
    //                     );
    //key = name
    AVLFile<Record,string> file("data.dat",
                    []( Record const&a, Record const&b) { return strcmp(a.nombre,b.nombre) < 0;}, //less
                    []( Record const&a, Record const&b) { return strcmp(a.nombre,b.nombre) > 0;}, //greater
                    []( Record const&a, string const&b) { return strcmp(a.nombre,b.c_str()) == 0;}, //equal_key
                    []( Record const&a, string const&b) { return strcmp(a.nombre,b.c_str()) < 0;}, //less_key
                    []( Record const&a, string const&b) { return strcmp(a.nombre,b.c_str()) > 0;}, //greater_key
                    []( Record const&a) { return a.nombre;} //get_key
                    );
    test(file);
    return 0;
}