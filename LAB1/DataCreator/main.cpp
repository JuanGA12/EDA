#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

int main() {
    fstream hola;
    hola.open("datasetB.txt",ios::in|ios::out);
    if (hola.is_open()) {
        cout<<"hola";
        for (int i = 0; i < 25000; i++) {
            int a = rand() % 901;
            int b = rand() % 901;
            hola << a;
            hola << " ";
            hola << b;
            hola << '\n';
        }
        for (int i = 0; i < 25000; i++) {
            int a = rand() % 1501;
            int b = rand() % 1501;
            hola << a;
            hola << " ";
            hola << b;
            hola << '\n';
        }
        hola.close();
    }
    return 0;
}
