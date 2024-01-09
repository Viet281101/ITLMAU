#include"personne_t.hpp"
#include<cassert>
#include<iostream>


int main(void)
{
   personne_t a{"jean","dagobert",45};
   std::cout << a.affiche() << std::endl;
   a.setProfession("roi");
   std::cout << a.affiche() << std::endl;
   a.setAge(67);
   assert(a.getAge()==67);
   assert(a.getProfession()=="roi");
   a.setProfession("calife");
   assert(a.getProfession()=="calife");
   std::cout << a.affiche() << std::endl;
   std::cout << "la ligne précédente devrait afficher quelque chose comme jean,dagobert,67 profession calife"<< std::endl;
   
}
