
# include <iostream>

using namespace std;


template <class T> class my_Test {
    T x;
    T y;
    public:
        void type(T a){
            x = a;
            cout << "The element " << x <<" has size " << sizeof(x) << endl;
        }
};


int main (void){
    my_Test <int> test1;
    test1.type(22);
    
    // my_Test <char> test2;
    // test1.type("22");
    
    return 0;
}

