#include"intreliee2_t.hpp"
#include<cassert>

int main()
{
   intreliee2_t a(5);
   intreliee2_t b(6);
   assert(a.get()==5);
   assert(b.get()==6);
   assert(intreliee2_t::somme()==11);
   {
      intreliee2_t b(-1);
      assert(intreliee2_t::somme()==10);
   }
   assert(intreliee2_t::somme()==11);
   b.set(2);
   assert(intreliee2_t::somme()==7);
   return 0;
}
