
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main(int argc, char** argv ) {
// 	int n;
// 	int i;
// 	char* p;
// 	if (argc > 0) {
// 		n = strlen(argv[0]);
// 		p = malloc(sizeof(**argv)*n); // on se considere pas le cas où NULL est renvoyé
// 		for (i = 0; i < n; i++) {
// 			p[i] = argv[0][n - i - 1];
// 		}
// 		printf("%s\n", p);
// 	}

// 	return EXIT_SUCCESS;
// }



int main(int argc, char** argv ) {
	int n;
	int i;
	char* p = NULL;
	if (argc > 0) {
		n = strlen(argv[0]);
		p = malloc(sizeof(char)*n + 1); // on se considere pas le cas où NULL est renvoyé
		for (i = 0; i < n; i++) {
			p[n] = '\0';
			p[i] = argv[0][n - i - 1];
		}
		printf("%s\n", p);
		// if faut ajouter free(p); p = NULL
	}

	return EXIT_SUCCESS;
}

/*

suite Exo 3
- il y a une fruite de mémoire
- et problème sur le toulle reservée

*/

