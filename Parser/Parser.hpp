/*
Sentences:
. create table Customer from file “C:\data.csv” using index hash(“DNI”)
- select * from Customer where DNI = x
- select * from Customer where DNI between x and y
- insert into Customer values (...)
- delete from Customer where DNI = x

*/
#include "Scanner.hpp"
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
    void parse();
    bool parse_create_table();
    bool parse_select();
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
    if(!match(Token::STRING)) return false;
    string key_table = previous->lexema;
    if(!match(Token::RPAREN)) return false;

    if(index_type == Token::HASH)
        cout<<"Creando indice Hash"<<endl;
    else if(index_type == Token::AVL)
        cout<<"Creando indice AVL"<<endl;
    else if(index_type == Token::SEQUENTIAL)
        cout<<"Creando indice Secuencial"<<endl;
    else
        cout<<"Error"<<endl;
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
                int number = stoi(value->lexema);
                cout<<"Buscando en la tabla donde "<<key_table<<" = "<<number<<endl;
            }else{
                string cadena = value->lexema;
                cout<<"Buscando en la tabla donde "<<key_table<<" = "<<cadena<<endl;
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
void Parser::parse(){
    current = scanner->nextToken();
    if (check(Token::ERR)) {
        cout << "Error en scanner - caracter invalido" << endl;
        exit(0);
    }
    if(check(Token::CREATE)){
        parse_create_table();
    }else if(check(Token::SELECT)){
        parse_select();
    }else{
        cout<<"Error"<<endl;
    }
}