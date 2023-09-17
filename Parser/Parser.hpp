/*
Sentences:
. create table Customer from file “C:\data.csv” using index hash(“DNI”)
- select * from Customer where DNI = x
- select * from Customer where DNI between x and y
- insert into Customer values (...)
- delete from Customer where DNI = x

*/

#include "Scanner.hpp"
#include "../sequential_file.hpp"


class Parser{
    Scanner* scanner;
    Token* current, *previous;
    bool match(Token::Type type);
    bool check(Token::Type type);
    bool advance();
    bool isAtEnd();
public:
    Parser(Scanner* scanner):scanner(scanner){
        previous = current = nullptr;
    }
    bool parse();
    bool parse_create_table();
    bool parse_select();
    bool parse_insert();
    bool parse_delete();
};
// match and consume next token
bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
        return false;
}
bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}
bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp =current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR)) {
            cout << "Parse error, unrecognised character: " << current->lexema << endl;
            exit(0);
        }
        return true;
    }
    return false;
}
bool Parser::isAtEnd() {
    return (current->type == Token::END);
}
template <typename T>
void leer_record(string line, Record<T> &record, string key_table){
    stringstream ss(line);
    string campo;
    getline(ss, campo, ',');
    int id = stoi(campo);
    getline(ss, campo, ',');
    string name = campo;
    getline(ss, campo, ',');
    string surname = campo;
    getline(ss, campo, ',');
    int ciclo = stoi(campo);
    record.setData(id, name, surname, ciclo);
    if(key_table == "id") record.set_key_int(id);
    else if(key_table == "name") record.set_key_string(name);
    else if(key_table == "surname") record.set_key_string(surname);
    else record.set_key_int(ciclo);
    
}
template <typename T>
void create_sequential(string key_table, string table_name, ifstream &file_){
    cout<<"Creando indice secuencial con key "<<key_table<<endl;

    SequentialFile<T> file(table_name + ".dat", "auxiliar.dat");
    Record<T> record;
    string campo, line;
    while(getline(file_, line)){
        leer_record(line, record, key_table);
        file.insert(record);
    }
    file_.close();
}
template <typename T>
void search_sequential(string key_table, string table_name, T cadena){
    cout<<"Buscando en la tabla "<<table_name<<" con key "<<key_table<< " donde "<<key_table<<" = "<<cadena<<endl;
    SequentialFile<T> file(table_name + ".dat", "auxiliar.dat");
    Record<T>* record = file.search(cadena);
    if(record){
        record->showData();
    }else{
        cout<<"No existe este registro"<<endl;
    }
}
void leer_csv(string table_name, string filename, Token::Type index_type, string key_table){
    ifstream file_(filename);
    string line;
    getline(file_, line);

    if(index_type == Token::SEQUENTIAL){
        if(key_table == "id" || key_table == "ciclo") create_sequential<int>(key_table, table_name, file_);
        else create_sequential<string>(key_table, table_name, file_);
    }
    // else if(index_type == Token::AVL){
    //     cout<<"Creando indice AVL con key "<<key_table<<endl;
    //     cout<<"Ruta: "<<filename<<endl;}
    // else if(index_type == Token::HASH)
    //     cout<<"Creando indice hash con key "<<key_table<<endl;
    else
        cout<<"Error"<<endl;


}

bool Parser::parse_create_table(){
    if(!match(Token::CREATE)) return false;
    if(!match(Token::TABLE)) return false;
    if(!match(Token::ID)) return false;
    string table_name = previous->lexema;
    if(!match(Token::FROM)) return false;
    if(!match(Token::FILE)) return false;
    if(!match(Token::STRING)) return false;
    string filename = previous->lexema;
    if(!match(Token::USING)) return false;
    if(!match(Token::INDEX)) return false;
    if(!match(Token::HASH) && !match(Token::AVL) && !match(Token::SEQUENTIAL)) return false;
    Token::Type index_type = previous->type;
    if(!match(Token::LPAREN)) return false;
    if(!match(Token::VALUEPAREN)) return false; // match(Token::ID) && match(Token::STRING)
    string key_table = previous->lexema;
    if(!match(Token::RPAREN)) return false;
    leer_csv(table_name, filename, index_type, key_table);
    return true;
}
bool Parser::parse_select(){
    if(!match(Token::SELECT)) return false;
    if(!match(Token::ALL)) return false;
    if(!match(Token::FROM)) return false;
    if(!match(Token::ID)) return false;
    string table_name = previous->lexema;
    if(!match(Token::WHERE)) return false;
    if(!match(Token::ID)) return false;
    string key_table = previous->lexema;
    if(!match(Token::EQUAL) && !match(Token::BETWEEN)) return false;
    if(previous->type == Token::EQUAL){
        if(!match(Token::ID) && !match(Token::NUMBER)) return false;
            Token* value = previous;
            if(value->type == Token::NUMBER){
                //Por el momento no es posible porque el key es name(string)
                int number = stoi(value->lexema);
                search_sequential(key_table, table_name, number);
            }else{
                search_sequential(key_table, table_name, value->lexema);
            }
    }else{
        if(!match(Token::NUMBER) && !match(Token::ID)) return false;
        Token value1 = *previous;
        if(!match(Token::AND)) return false;
        if(value1.type!=current->type) return false;
        if(value1.type == Token::NUMBER){
            int number1 = stoi(value1.lexema);
            int number2 = stoi(current->lexema);
            cout<<"Buscando en la tabla donde "<<key_table<<" entre "<<number1<<" y "<<number2<<endl;
        }else{
            string cadena1 = value1.lexema;
            string cadena2 = current->lexema;
            cout<<"Buscando en la tabla donde "<<key_table<<" entre "<<cadena1<<" y "<<cadena2<<endl;
        }
    }
    return true;
}
bool Parser::parse_insert(){
    if(!match(Token::INSERT)) return false;
    if(!match(Token::INTO)) return false;
    if(!match(Token::ID)) return false;
    string table_name = previous->lexema;
    if(!match(Token::VALUES)) return false;
    if(!match(Token::LPAREN)) return false;
    if(!match(Token::VALUEPAREN)) return false;
    string values = previous->lexema;
    if(!match(Token::RPAREN)) return false;
    return true;
}
bool Parser::parse_delete(){
    if(!match(Token::DELETE)) return false;
    if(!match(Token::FROM)) return false;
    if(!match(Token::ID)) return false;
    string table_name = previous->lexema;
    if(!match(Token::WHERE)) return false;
    if(!match(Token::ID)) return false;
    string key_table = previous->lexema;
    if(!match(Token::EQUAL)) return false;
    if(!match(Token::ID) && !match(Token::NUMBER)) return false;
    Token value = *previous;
    if(value.type == Token::NUMBER){
        int number = stoi(value.lexema);
        cout<<"Eliminando en la tabla donde "<<key_table<<" = "<<number<<endl;
    }else{
        string cadena = value.lexema;
        cout<<"Eliminando en la tabla donde "<<key_table<<" = "<<cadena<<endl;
    }
    return true;
}
bool Parser::parse(){
    current = scanner->nextToken();
    if (check(Token::ERR)) {
        cout << "Error en scanner - caracter invalido" << endl;
        exit(0);
    }
    if(check(Token::CREATE)){
        return parse_create_table();
    }else if(check(Token::SELECT)){
        return parse_select();
    }else if (check(Token::INSERT)) {
        return parse_insert();
    }else if (check(Token::DELETE)) {
        return parse_delete();
    }else{
        return false;
    }
}