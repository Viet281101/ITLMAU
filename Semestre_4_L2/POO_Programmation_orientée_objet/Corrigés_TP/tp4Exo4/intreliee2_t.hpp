#ifndef _INTRELIEE2_T_HPP_
#define _INTRELIEE2_T_HPP_

class intreliee2_t
{
      int val;
      static int sommeN;
   public:
      intreliee2_t(int a)
      {
         val=a;
         sommeN+=a;
      }
      intreliee2_t(const intreliee2_t& p)
      {
         val=p.val;
         sommeN+=p.val;
      }
      intreliee2_t& operator=(const intreliee2_t& p)
      {
         sommeN-=val;
         sommeN+=p.val;
         val=p.val;
         return *this;
      }
      int get() const
      {
         return val;
      }
      void set(int a)
      {
         sommeN-=val;
         sommeN+=a;
         val=a;
      }
      ~intreliee2_t()
      {
         sommeN-=val;
      }
      static int somme() 
      {
         return sommeN;
      }
};
#endif 
