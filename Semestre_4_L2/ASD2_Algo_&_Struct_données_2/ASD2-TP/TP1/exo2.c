

// #include <stdio.h>

// int foo(void);
// int appels_a_foo();

// int main(void) {
//     appels_a_foo();
//     return 0;
// }

// int foo(void) {
//     static int cpt = 0;
//     if (++cpt <= 3)
//     printf("Appel à foo() numéro %d\n", cpt);
//     return 0;
// }

// int appels_a_foo() {
//     int i;
//     for (i = 0; i<10; i++) {
//         foo();
//     }
//     return 0;
// }



#include <stdio.h>

int foo(void){
	static int cpt = 0; // définition d'une variable "static"
	/* remplacer par la ligne ci-dessous pour comparer avec 
	la définition d'une variable non "static" */
	// int cpt = 0 ;
	++cpt;
	printf("Appel à foo() numéro %d\n", cpt);
	return 0;
}

int main(){
	for (int i = 0; i<10; i++){
		foo();
	}
}


