#include <iostream>
#include "Parser/Parser.hpp"
using namespace std;

int main(){
    // string s;
    // cin>>s;
    Scanner scanner("create table Customer from file \"C:\\data.csv\" using index avl(\"DNI\")");
    Parser parser(&scanner);
    parser.parse();
    return 0;
}