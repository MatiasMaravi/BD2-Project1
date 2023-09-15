#include <iostream>
#include "Parser/Parser.hpp"
using namespace std;

int main(){
    // string s;
    // cin>>s;
    // Scanner scanner("create table Customer from file \"C:\\data.csv\" using index avl(\"DNI\")");
    // Scanner scanner("select * from Customer where DNI = 72790028");
    // Scanner scanner("select * from Customer where NAME = Juan");
    // Scanner scanner("select * from Customer where DNI between Pepe and Tito");
    Scanner scanner("insert into Customer values (72790028, Juan, 123456789)");
    Parser parser(&scanner);
    parser.parse();
    return 0;
}