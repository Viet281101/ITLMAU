
#include<stdio.h> 
int main(void) 
{ 
	char nom[25]; 
	printf("Quel est votre nom ?\n"); 
    scanf("%[^\n]*c",nom); 
	 
	printf("Bonjour %s. Au revoir.",nom); 

	return 0;
	 
} 


