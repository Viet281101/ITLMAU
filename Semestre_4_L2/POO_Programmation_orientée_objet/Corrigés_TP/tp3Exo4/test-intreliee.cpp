#include"intreliee_t.hpp"
#include<cassert>

int main()
{
   intreliee_t a(5);
   intreliee_t b(6);
   assert(a.get()==5);
   assert(b.get()==6);
   assert(intreliee_t::somme()==11);
   {
      intreliee_t b(-1);
      assert(intreliee_t::somme()==10);
   }
   assert(intreliee_t::somme()==11);
   b.set(2);
   assert(intreliee_t::somme()==7);
   return 0;
}
