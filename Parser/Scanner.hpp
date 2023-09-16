#include "Token.hpp"
#include <unordered_map>
class Scanner{
public:
    Scanner(const char* input);
    Token* nextToken();
    bool paren_flag = false;
private:
    unordered_map<string, Token::Type> reserved;
    string input;
    int first, current;
    char nextChar();
    void rollBack();
    void startLexema();
    void consume_white_spaces(char &c);
    Token* scan_number(char &c);
    Token* scan_alpha(char &c);
    Token* scan_string(char &c);
    Token* scan_lparen(char &c);
    Token* scan_valueparen(char &c);
    Token::Type checkReserved(string lexema);
    string getLexema();
};
Token::Type Scanner::checkReserved(string lexema) {
    unordered_map<string,Token::Type>::const_iterator it = reserved.find(lexema);
    if (it == reserved.end()){
        return Token::ID;
    }    else{
        return it->second;
    }
}

Scanner::Scanner(const char* s): input(s){
    first = current = 0;
    reserved["select"] = Token::SELECT;
    reserved["from"] = Token::FROM;
    reserved["table"] = Token::TABLE;
    reserved["where"] = Token::WHERE;
    reserved["create"] = Token::CREATE;
    reserved["insert"] = Token::INSERT;
    reserved["delete"] = Token::DELETE;
    reserved["values"] = Token::VALUES;
    reserved["into"] = Token::INTO;
    reserved["file"] = Token::FILE;
    reserved["using"] = Token::USING;
    reserved["index"] = Token::INDEX;
    reserved["hash"] = Token::HASH;
    reserved["avl"] = Token::AVL;
    reserved["sequential"] = Token::SEQUENTIAL;
    reserved["between"] = Token::BETWEEN;
    reserved["and"] = Token::AND;
}
void Scanner::rollBack() { // retract
    current--;
}
void Scanner::startLexema() {
    first = current-1;
return;
}
string Scanner::getLexema() {
    return input.substr(first,current-first);
}
void Scanner::consume_white_spaces(char &c){
    while(c == ' ' || c == '\n' || c == '\t') c = nextChar();
}
Token* Scanner::scan_number(char &c){
    c = nextChar();
    while(isdigit(c)) c = nextChar();
    rollBack();
    return new Token(Token::NUMBER, getLexema());
}
Token* Scanner::scan_alpha(char &c){
    c = nextChar();
    while(isalpha(c)) c = nextChar();
    rollBack();
    return new Token(checkReserved(getLexema()), getLexema());
}
Token* Scanner::scan_string(char &c){
    c = nextChar();
    while(c != '"') c = nextChar();
    return new Token(Token::STRING, getLexema());
}
Token* Scanner::scan_lparen(char &c){
    paren_flag = true;
    return new Token(Token::LPAREN, "(");
}
Token* Scanner::scan_valueparen(char &c){
    while(c != ')') c = nextChar();
    paren_flag = false;
    rollBack();
    return new Token(Token::VALUEPAREN, getLexema());
}
 Token* Scanner::nextToken(){
    char c;
    //consume white spaces
    c = nextChar();
    consume_white_spaces(c);
    if(c == '\0' || c == '-') return new Token(Token::END,"-");

    startLexema();

    if(paren_flag) return scan_valueparen(c);
    else if(c == '"') return scan_string(c);
    else if(c == '(') return scan_lparen(c);
    else if(isalpha(c)) return scan_alpha(c);
    else if(c == '*' ) return new Token(Token::ALL, "*");
    else if(c == '=') return new Token(Token::EQUAL, "=");
    else if(c == ')') return new Token(Token::RPAREN, ")");
    else if(isdigit(c)) return scan_number(c);
    else return new Token(Token::ERR, "Error");
    
}
char Scanner::nextChar() {
    int c = input[current];
    current++;
    return c;
}