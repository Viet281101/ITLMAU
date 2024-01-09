

#include <iostream>


int min(int a, int b) {
    return a < b ? a : b;
}

float min1 (float f, float g) {
    return f < g ? f : g;
}
float min2 (float f, float g, float h) {
    return f < g ? (f < h ? f : h) : (g < h ? g : h );
}

int main ( void ) {
    int a = 2, b = 3, c;
    c = min(a, b);
    // donnera 2
    float d = 1.1f , e = 2.2f , f;
    f = min1(d, e);
    // donnera 1.1 f
    float g = 3.3f , h = 4.4f , i = 0.1f , k ;
    k = min2(g, h, i); // donnera 0.1f
    return 0;
}
