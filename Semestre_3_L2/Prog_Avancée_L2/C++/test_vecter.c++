
#include<iostream>
#include<iterator>
#include<vector>

using namespace std;

// int main(void){
//     vector <int> v;
//     v.reserve(32);
//     for (int i = 0; i < 33; ++i){
//         v.push_back(i + 1);
//         cout << "size : " << v.size() << " capacity : " << v.capacity() <<endl;
//     }
//     return 0;
// }
 
int main()
{
    // Create a vector containing integers
    vector<int> v = {10, 11, 30, 44, 50};
    vector<int> v3(5, 10);
 
    // // // Add two more integers to vector
    // // v.push_back(25);
    // // v.push_back(13);
 
    // // // Print out the vector
    // // cout << "v = { ";
    // // for (int n : v)
    // //     cout << n << ", ";
    // // cout << "}; \n";

    for (int i = 0; i < v3.size(); i ++){
        cout << v3[i] << endl;
    }
    
    vector<int>::iterator ptr;
    for (ptr = v3.begin(); ptr < v3.end(); ptr++){
    
    }
    cout << v3.size() << endl;
    cout << v3.capacity() << endl;
    cout << v3.at(3) << endl;


    return 0;

}
