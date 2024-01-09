

# include <iostream>

using namespace std;


// void swap(int* xp, int* yp)
// {
// 	int temp = *xp;
// 	*xp = *yp;
// 	*yp = temp;
// }

// template <class T> void bubbleSort(T a[], int n) {
//     for (int i = 0; i < n -1; i ++){
//         for ( int j = n -1; i < j; j --){
//             if (a[j] < a[j- 1]){
//                 swap(a[j], a[j-1]);
//             }
//         }
//     }
// }


// Test constructor has two arguments of generic type T1 and T2 .
template < class T1 , class T2 > class Test {
    T1 x ;
    T2 y ;
    public :
        Test ( T1 a , T2 b){ // constructor of type template
            cout << " Constructor called " << endl ;
            x = a;
            y = b;
        } // end of Test ()
        void print () {
            cout << x << " and " << y << endl ;
        }
}; // end of class


template < typename T > class Array {
    private :
        T * ptr ;
        int size ;
    public :
        Array (T arr [] , int s);
        void print (){
            for ( int i = 0; i < size ; i ++)
                cout << " " << *( ptr + i) ;
                cout << endl ;
        };
};

template < typename T > Array <T > :: Array (T * arr, int s){
    ptr = new T[s ];
    size = s;
    for ( int i = 0; i < size ; i ++)
        ptr [ i ] = arr [i];
}

// template < typename T > void Array <T > :: print () {
// for ( int i = 0; i < size ; i ++)
//     cout << " " << *( ptr + i) ;
//     cout << endl ;
// }

int main ( void ){
    // int arr [5] = {1 , 2, 3, 4, 5};
    // Array < int >a( arr ,5) ;
    // a . print () ;


    // instantiation with string and string type
    // and passing values by creating an object
    Test < string , string > obj1 (" one " , " two ");
    // instantiation with int and string type
    Test < int , string > obj2 (1 , " one ");
    obj1.print () ;
    obj2.print () ;


    return 0;
}

