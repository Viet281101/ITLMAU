
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>


int var = 1;

namespace monEDN
{
	int var=2;
	struct monType {};
	namespace MSED {
		int var = 3;
		int g = 0;
	}
}

int main()
{
	using namespace monEDN::MSED;
	//std::cout<< var << " ";
	std::cout<< g << " ";

	int t1[10];
	std::array<int, 10> t2;
	int i = 0;
	for (auto& a : t2) {
		a = i++;
	}
	for (int a : t2) {
		std::cout << a << " ";		
	}

	/*t2[2] = 1;
	t2.at(2) = 2;*/
	std::cout << std::endl;


	std::vector<int> v1;
	v1.push_back(45);
	v1.push_back(32);
	v1.push_back(4);
	std::cout << v1.size() << std::endl;
	v1[2] = 3;
	v1.at(1) = 2;
	for (auto a : v1) {
		std::cout << a << " ";
	}


	std::cout << std::endl;


	std::map<std::string, std::string> dico;
	dico["ballon"] = "objet rond et creux";
	/*dico["ballon"] = new std::string{"bonjour"};*/

	std::cout << dico["ballon"] << std::endl;
	dico["ballon"] = "objet sphérique et rempli de gaz";
	std::cout<< dico["ballon"] << std::endl;

}
