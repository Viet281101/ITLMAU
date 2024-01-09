

#include<iostream>
#include<iterator>
#include<vector>

using namespace std;

void print (vector<int> v){
    for (int i = 0; i < v.size(); i++){
        cout << v.at(i) << " ";
    }
    cout << endl;
}

void printStr (vector<string> v){
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
}


int main(void){

    vector <int> v1 = {1, 2, 3, 4};
    vector <int> v2 = {10, 20, 30};

    vector <int> :: iterator ptr = v1.begin();
    advance(ptr, 3);

    print(v1);
    // print(v2);

    auto it = v1.begin();
    /* insert int*/
    it = v1.insert(it, 100);
    print(v1);

    /* insert vector*/
    it = v1.insert(v1.begin(), v2.begin(), v2.end());
    print(v1);


    /* insert string*/

    vector <string> prog_vec;
    string str = 'avance';

    prog_vec.push_back(str);

    // printStr(prog_vec);

    // auto it2 = prog_vec.begin();
    // it2 = prog_vec.insert(it2, str);

    

    return 0;

}
