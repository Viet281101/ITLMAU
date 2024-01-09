#include"personne_t.hpp"
#include<string>

personne_t::personne_t(std::string nom,std::string prenom,int age)
{
   this->age=age;
   this->nom=nom;
   this->prenom=prenom;
}
void personne_t::setAge(int a)
{
   age=a;
}
int personne_t::getAge(void){
   return age;
}
std::string personne_t::getProfession(void)
{
   return profession;
}
void personne_t::setProfession(std::string pr)
{
   profession=pr;
}
std::string personne_t::affiche(){
   std::string retour=
      std::string("Je suis ")+
      nom+
      std::string(" ")+
      prenom+
      std::string(", j'ai ")+
      std::string(std::to_string(age));
   if(profession=="")
   {
      retour+=" ans.";
   }
   else
   {
      retour+=" ans et ma profession est ";
      retour+=profession;
      retour+=".";
   }
   return retour;
}
