#include "Token.hpp"
#include <unordered_map>
class Scanner{
public:
    Scanner(const char* input);
    Token* nextToken();
private:
    unordered_map<string, Token::Type> reserved;
    string input;
    int first, current;
    char nextChar();
    void rollBack();
    void startLexema();
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
Token* Scanner::nextToken(){
    Token* tok;
    char c;
    //consume white spaces
    c = nextChar();
    while(c == ' ' || c == '\n' || c == '\t') c = nextChar();
    if(c == '\0' || c == '-') return new Token(Token::END,"-");
    startLexema();
    if(c == '"'){
        c = nextChar();
        while(c != '"') c = nextChar();
        return new Token(Token::STRING, getLexema());
    }
    else if(isalpha(c)){
        c = nextChar();
        while(isalpha(c)) c = nextChar();
        rollBack();
        tok = new Token(checkReserved(getLexema()), getLexema());
        return tok;
    }else if(c == '*' ) return new Token(Token::ALL, "*");
    else if(c == '=') return new Token(Token::EQUAL, "=");
    else if(c == '(') return new Token(Token::LPAREN, "(");
    else if(c == ')') return new Token(Token::RPAREN, ")");
    else if(isdigit(c)){
        c = nextChar();
        while(isdigit(c)) c = nextChar();
        rollBack();
        return new Token(Token::NUMBER, getLexema());
    }else{
        return new Token(Token::ERR, "Error");
    }
}
char Scanner::nextChar() {
    int c = input[current];
    current++;
    return c;
}