#ifndef _INTRELIEE_T_HPP_
#define _INTRELIEE_T_HPP_

class intreliee_t
{
      int val;
      static int sommeN;
   public:
      intreliee_t(int a)
      {
         val=a;
         sommeN+=a;
      }
      int get()
      {
         return val;
      }
      void set(int a)
      {
         sommeN-=val;
         sommeN+=a;
         val=a;
      }
      ~intreliee_t()
      {
         sommeN-=val;
      }
      static int somme()
      {
         return sommeN;
      }
};
#endif 
