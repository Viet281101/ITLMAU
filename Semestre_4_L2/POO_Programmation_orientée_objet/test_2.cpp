
#include <iostream>
#include <vector>
#include <exception>


using namespace std;

struct monExcep : public exception
{

};

void maFonction(int a, int b)
{
	if (a == b)
	{
		throw monException();
	}
}


int main()
{
	try {
		throw B();
	}
	catch (A& a)
	{
		cerr << "Error: " << a.what() << endl;
	}
}

