#include <iostream>
#include <vector>
using namespace std;



#define fb 226//4084/18
//alumno
struct record{
    int codigo;
    char name[10];
    int ciclo;
    void setData(){
        cout<<"Codigo: ";cin>>codigo;
        cout<<"Nombre: ";cin>>name;
        cout<<"Ciclo: ";cin>>ciclo;
    }
};

class Bucket{
    record *data;
    int count;
    int size;
    int next;
    Bucket(){
        data = new record[4];
        count = 0;
        size = 4;
        next = -1;
    }
};








int main(){
    cout<<"---------------------------------"<<endl;
    cout <<  fb << endl;
    cout<<"---------------------------------"<<endl;
    
    return 0;
}