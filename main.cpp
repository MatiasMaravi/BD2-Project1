#include <iostream>
#include "Parser/Scanner.hpp"
using namespace std;

int main(){
    // string s;
    // cin>>s;
    Scanner* scanner = new Scanner("select * from Customer where DNI = 7279");
    Token* tok = scanner->nextToken();
    do{
        cout<<tok<<endl;
        tok = scanner->nextToken();
    }while(tok->type != Token::END);

    return 0;
}