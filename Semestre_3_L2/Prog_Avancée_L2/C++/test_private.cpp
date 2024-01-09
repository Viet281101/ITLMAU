

#include <iostream>

using namespace std;

// class Employee {
//     private :
//         int salary ;
//     public :
//         void set_salary ( int s){
//         salary = s;
//     }

//     int get_salary ( void ){
//         return salary ;
//     }
// };

// int main ( void ){
//     Employee e;
//     e . set_salary (70000) ;
//     cout << e. get_salary () ;
//     return 0;
// }

class Name : public Employee {
    public :
        string name = " smith ";
        };int main ( void ){
            
Name nm ;
nm . set_salary (70000) ;
cout << nm . get_salary () ;
return 0;
}
