
// forward_list::sort
#include <iostream>
#include <forward_list>
#include <functional>

using namespace std;

int main ()
{
  forward_list<int> mylist = {22, 13, 5, 40, 90, 62, 31};

  mylist.sort();

  cout << "default sort (operator<):";
  for (int& x: mylist) cout << ' ' << x;
  cout << '\n';

  mylist.sort(greater<int>());
  cout << "sort with greater():";
  for (int& x: mylist) cout << ' ' << x;
  cout << '\n';


  mylist.sort(less<int>());
  cout << "sort with less():";
  for (int& x: mylist) cout << ' ' << x;
  cout << '\n';

  return 0;
}
