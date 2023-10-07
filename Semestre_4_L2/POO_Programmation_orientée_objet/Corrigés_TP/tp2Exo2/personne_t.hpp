#include<string>

#ifndef __PERSONNE_T_H__
#define __PERSONNE_T_H__
class personne_t 
{
   private:
      std::string nom;
      std::string prenom;
      std::string profession;
      int age;
   public:
      personne_t(std::string nom,std::string prenom,int age);
      void setAge(int);
      int getAge(void);
      std::string getProfession(void);
      void setProfession(std::string);
      std::string affiche();
};
#endif 

/*
 2. Oui, de même qu'on aurait pu ajouter une méthode getNom 

 3. Non si une personne n'est pas censée 
   changer de prénom au cours de sa vie. (oui sinon)
*/

