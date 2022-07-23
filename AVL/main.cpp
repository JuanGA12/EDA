#include <iostream>
#include "AVL.h"
using namespace std;
int main() {

    AVLtree<int> r;
    r.insert(50,100);
    r.insert(25,100);
    r.insert(26,100);

    r.preOrder();
}