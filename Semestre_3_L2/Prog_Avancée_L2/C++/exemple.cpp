
#include <iostream>
#include <new>

using namespace std;

int main (void) {
    int *p = new int [5];
    for (int i = 0; i < 5; i++){
        *(p+i) = 0;
        cout <<"p[" << i << "] = " << p[i] << endl;
    }
    delete []p;
    return 0;
}
