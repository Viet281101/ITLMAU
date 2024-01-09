#include<cassert>
/*
 * 
 */

double max(double a,double b)
{
   if(a>b)
      return a;
   else
      return b;
}

double min(double a,double b)
{
   if(a>b)
      return b;
   else
      return a;
}

class Interv
{
      double bMax; // borne supérieure
      double bMin; // borne inférieure
   public:
      Interv(double a, double b){
         bMin=a;
         bMax=b;
      }
      Interv(double a) {
         bMin=bMax=a;
      }
      Interv() {
         bMin=1;
         bMax=0;
      }
      int appartient(double a){
         return a<=bMax && bMin<=a;
      }
      Interv intersect(Interv b) {
         return Interv(max(b.bMin,this->bMin),min(b.bMax,this->bMax));
      }
      int estVide()
      {
         return bMin>bMax;
      }
      Interv unifier(Interv b){
         if(b.estVide())
            return *this;
         if(estVide())
            return b;
         if(b.intersect(*this).estVide())
            throw 1; // une union d'intervalles non vides
            // est un intervalle si et seulement si 
            // leur intersection est non vide
         return Interv{min(b.bMin,bMin),max(b.bMax,bMax)};
      }
};

// pour tester
int main()
{
   Interv a{0,1};
   assert(a.appartient(0));
   assert(a.appartient(1));
   assert(a.appartient(0.9));
   assert(a.appartient(0.1));
   assert(!a.appartient(-0.3));
   assert(!a.appartient(1.3));

   Interv b{7,5};
   assert(!b.appartient(5));
   assert(!b.appartient(4.9));
   assert(!b.appartient(6));
   assert(!b.appartient(7.1));
   assert(!b.appartient(6.9));

   assert(b.estVide());

   Interv c=Interv{2,5}.intersect(Interv{3,6});
   assert(!c.appartient(1.9));
   assert(!c.appartient(2.1));
   assert(c.appartient(3.1));
   assert(c.appartient(3));
   assert(!c.appartient(2.9));
   assert(c.appartient(4.9));
   assert(!c.appartient(5.1));
   assert(c.appartient(5));

   Interv d=Interv{-2,4}.unifier(Interv{3,6});
   assert(!d.appartient(-2.1));
   assert(d.appartient(-1.9));
   assert(d.appartient(6));
   assert(!d.appartient(6.1));
   assert(d.appartient(5.9));

   try // utilise les méchanime try catch throw (exception)
   {
      Interv h=Interv{-2,4}.unifier(Interv{5,6});
      assert(0); // ne doit pas être éxécuté
   }
   catch(int a)
   {
      assert(a==1);
   }
   return 0;

}
