
#include <stdio.h>

double monAbs(double x)
{
    return ((x>=0)?x:(-x)); /// if (x >= 0) return x; else return (-x);
}

float racineCarree(float a,float erreur){
    double s = 1.0f;
    while (monAbs(s * s - a) / a >= erreur)
        s = (a / s  - s) / 2 + s;
    return s;

    //// Avec recursive:
    // if (monAbs(s*s - a) < erreur){
    // 	s = (a / s  - s) / 2 + s;
    // }
    // return s;
    // racineCarree(a, erreur);

}


int main(void)
{
	printf("%f\n", racineCarree(9, 0.0001f));
	return 0;
}

