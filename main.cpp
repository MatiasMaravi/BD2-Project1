#include <iostream>
#include "Parser/Parser.hpp"
using namespace std;

int main(){
    // string s;
    // cin>>s;
    // Scanner scanner("create table Customer from file \"data.csv\" using index avl(NAME)");
    // Scanner scanner("select * from Customer where DNI = 72790028");
    // Scanner scanner("select * from Customer where NAME = Juan");
    // Scanner scanner("select * from Customer where ALTURA between 75 and 100");
    // Scanner scanner("insert into Customer values (72790028, Juan, 123456789)");
    Scanner scanner("delete from Customer where DNI = XXX");

    Parser parser(&scanner);
    if(!parser.parse()) cout << "Parse error" << endl;
    

    return 0;
}