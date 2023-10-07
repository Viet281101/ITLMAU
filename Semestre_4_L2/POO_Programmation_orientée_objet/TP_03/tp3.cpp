
#include <iostream>

class Interv {
    private: 
        double bi; 
        double bs;
    public: 
        Interv(double a, double b){
            bi = min(a, b);
            bs = max(a, b);
        }
        Interv(double a){
            bi = bs = a;
        }
        Interv(){
            bi = 1;
            bs = 0;
        }
        double min(double a, double b){
            if (a > b) 
                return b;
            return a;
        }
        double max(double a, double b){
            if (a > b)
                return a;
            return b;
        }
        int apportient(double e){
            if ( e <= bs && e >= bi)
                return 1; 
            return 0;
        }

        Interv ~ intersect(Interv b){
            Interv a;
            a.bs = min(this -> bs, b.bs);
            a.bi = max(this -> bi, b.bi);
        }

        int estVide(){
            if (this -> bs < this -> bi)
                return 1;
            return 0;
        }
}

