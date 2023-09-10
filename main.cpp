#include "extendible_hashing.hpp"
int main(){
    string palabra = "pepaaadadadaea";
    string binary = to_binary(hash_string(palabra));
    cout<<binary<<endl;
    
    return 0;
}