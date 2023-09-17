
#include <iostream>
using namespace std;
struct Token{
    enum Type{SELECT, ALL, 
                FROM, TABLE, 
                WHERE, CREATE, 
                INSERT, DELETE, 
                VALUES, INTO, 
                FILE, USING, 
                INDEX, HASH,
                AVL, SEQUENTIAL,
                BETWEEN, AND,
                STRING, NUMBER, 
                EQUAL, ID,
                LPAREN, RPAREN, VALUEPAREN,
                END, ERR};
    Type type;
    static const char* token_names[25];
    string lexema;
    Token(Type): type(type){
        lexema = "";
    }
    Token(Type type, const string lexema): type(type), lexema(lexema){}
};

const char* Token::token_names[25] = {"select", "*", 
                                        "from", "table", 
                                        "where", "create", 
                                        "insert", "delete", 
                                        "values", "into", 
                                        "file", "using", 
                                        "index", "hash",
                                        "avl", "sequential",
                                        "between", "and",
                                        "string", "number", 
                                        "=","ID",
                                        "(", ")","ValueParen"};


std::ostream& operator << ( std::ostream& outs, const Token & tok ){
    if (tok.lexema.empty())
        return outs << Token::token_names[tok.type];
    else
        return outs << Token::token_names[tok.type] << "(" << tok.lexema << ")";
}
ostream& operator << (ostream& out, const Token* tok){
    return out << *tok;
}
