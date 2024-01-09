
# include<iostream>

typedef struct vec2 vec2 ;
struct vec2 {
    float x , y;
    // permet de dé finir l ’op é ration ’+ ’
    // entre deux vec2
    vec2 operator +( vec2 v) {
        vec2 r;
        r.x = this -> x + v.x; // le this -> est facultatif
        r.y = this -> y + v.y; // le this -> est facultatif
        return r;
    }
};

float operator *(vec2 v){
    int r;
    r = x * v.x + y * v.y;
    return r;
}

int main ( void ) {
    vec2 a = {1.0f , 2.0f}, b = {3.0f , 4.0f };
    vec2 res = a + b ;
    std :: cout << "résultat = (" << res .x << ", " << res . y << ") \n ";
    return 0;
}
