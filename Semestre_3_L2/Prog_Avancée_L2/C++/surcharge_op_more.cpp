

# include <iostream>

typedef struct vec2 vec2 ;
struct vec2 {
float x , y;
    vec2 operator +( vec2 v ) { // somme de deux vec2
        vec2 r ;
        r . x = x + v .x ;
        r . y = y + v .y ;
        return r ;
    }

    // notez le type de retour
float operator *( vec2 v ) { // produit scalaire de deux vec2
        return x * v. x + y * v . y ;
    }

    // Attention cette multiplication ne fonctionne que dans un sens
    vec2 operator *(float k ) { // renvoie ( u * k )
        vec2 r = { k * x , k * y };
        return r ;
    }
};

// Celle - l à la rend fonctionnelle dans l ’ autre sens
// Vous remarquerez que nous sommes en dehors de la structure
vec2 operator *(float k , vec2 u) { // renvoie ( k * u )
    return u * k ;
}
int main ( void ) {
    vec2 a = {1.0f , 2.0f }, b = {3.0f , 4.0f };
    vec2 ka = 0.5f * a ; // donne (0.5f , 1.0f )
    float s = ka * b ; // donne (0.5f * 3.0f + 1.0f * 4.0f ) = 5.5f
    std :: cout << " résultat  = " << s << " \n " ;
    return 0;
}


