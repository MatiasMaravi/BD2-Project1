#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char a[20] = "hola";
    char b[20] = "pepe";

    if (strcmp(a, b)<0) {
        cout << "a es menor que b" << endl;
    } else {
        cout << "a no es menor que b" << endl;
    }

    return 0;
}
