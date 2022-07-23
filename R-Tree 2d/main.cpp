#include <vector>
#include "clase.h"
using namespace std;

int main() {

    RTree r;
    auto ranges = r.generateFromFile("dataset1000.txt");
    r.searchOutFile("out2.txt", ranges[0],ranges[1]);
}

/*
            X:10 Y:1
            X:10 Y:5
            X:10 Y:10
            X:22 Y:12
            X:22 Y:30
            X:24 Y:7
            X:25 Y:8
 */