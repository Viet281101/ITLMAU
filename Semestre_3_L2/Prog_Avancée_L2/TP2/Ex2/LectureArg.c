
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
# define MAX_INPUT 100
  
int main()
{
	printf("Veuillez entrez un arguments: \n");
	char value[MAX_INPUT] = "";

	double temp;

	int n;

	char str[MAX_INPUT] = "";

	double val = 1e-12;

	fgets(value, 100, stdin);
  
    if (sscanf(value, "%lf", &temp) == 1) 
    {
        n = (int)temp;
        if (fabs(temp - n) / temp > val) 
            printf("la sortie standard ce nombre arguments est 'float'\n");        
        else 
            printf("la sortie standard ce nombre arguments est 'int'\n");        
    }
   
    else if (sscanf(value, "%s", str) == 1)     
        printf("Le data type arguments est string\n");
      
    else
        printf("Ce n est pas un arguments \n");    
}
