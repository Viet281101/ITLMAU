

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main(void) {
    vector<int> vec = {0, 1, 2, 3, 4};

    // declaration d'un iteration
    vector<int>:: iterator ptr;
    for (ptr = vector.begin(); ptr != vector.end(); ptr++) {
        cout <<*ptr <<endl;
    }

    vector<int> vec2 = {10, 11, 12, 13, 14};
    vector<int> :: iterator = vec2.begin();

    advance(ptr, 3);
    cout<< *ptr << " ";


    vector<int> v1 = {0, 1, 2, 13, 4};
    vector<int> :: iterator = v1.begin();
    vector<int> :: iterator = v1.end();

    auto it1 = next(ptr, 3);
    auto it2 = prev(ptr, 3);

    cout << "it1" << *it1 << endl;
    cout << "it2" << *it2 << endl;


    return 0;
}


