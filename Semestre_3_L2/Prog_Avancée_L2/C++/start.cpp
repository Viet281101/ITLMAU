
#include <iostream>

using namespace std;
namespace a {
    int x = 5;
    void f(void) {
        cout <<"This is f() of a"<< endl;
    }
}

namespace b {
    int x = 10;
    void f(void){
        cout <<"This is f() of b"<< endl;
    }
}

int main(void) {
    // call var using scope resoltion (::)
    cout << a::x<<endl;
    // function call using scope resoltion (::)
    a::f();
    cout << b::x<<endl;
    b::f();
    
    getchar();
    return 0;
}

