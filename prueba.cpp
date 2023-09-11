#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
//Estructura para leer cualquier CSV

struct Record{
    string key_t;
    string content;
    void display(){
        cout<<"Key: "<<key_t<<endl;
        cout<<"Content: "<<content<<endl;
    }
    
};
bool operator<(const Record& a, const Record& b){
    try {
        int a_key = stoi(a.key_t);
        int b_key = stoi(b.key_t);
        return a_key < b_key;
    } catch (const std::exception& e) {
        // std::cerr << e.what() << '\n';
    }
    return a.key_t > b.key_t;
}
bool operator>(const Record& a, const Record& b){
    try {
        int a_key = stoi(a.key_t);
        int b_key = stoi(b.key_t);
        return a_key > b_key;
    } catch (const std::exception& e) {
        // std::cerr << e.what() << '\n';
    }
    return a.key_t < b.key_t;
}

void leer_columnas(string& linea, string key, int& pos){
    int aux = 0;
    std::istringstream lineaStream(linea);
    std::string campo;
    std::vector<std::string> fila;
    // Divide la línea en campos separados por comas
    while (std::getline(lineaStream, campo, ',')) {
        //eliminando el salto de linea
        if (campo[campo.size() - 1] == '\r') {
            campo.erase(campo.size() - 1);
        }
        if (aux == 0) campo = campo.substr(3);

        if(campo == key){
            cout<<"Se encontro la key"<<endl;
            pos = aux;
            break;
        }
        aux++;
        
    }
}

int main() {
    string key;
    cout<<"Ingresa la key: ";cin>>key;
    int pos = -1;

    vector<string> columnas;
    std::ifstream archivo("archive/data.csv"); // Abre el archivo

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }
    std::string linea;

    // Lee el archivo línea por línea
    getline(archivo, linea);
    
    leer_columnas(linea, key, pos);
    cout<<"Pos_key: "<<pos<<endl;

    
    std::string campo;
    vector<Record> records;
    while(getline(archivo,linea)){
        Record record;
        std::istringstream lineaStream(linea);
        int cont = 0;
        while(std::getline(lineaStream, campo, ',')){
            if(cont == pos){
                record.key_t = campo;
                record.content = linea;
                records.push_back(record);
            }
            cont++;
        }
    }
    records[1].display();
    if(pos == -1){
        cout<<"No se encontro la key"<<endl;
        return 0;
    }

    archivo.close(); // Cierra el archivo


    return 0;
}
