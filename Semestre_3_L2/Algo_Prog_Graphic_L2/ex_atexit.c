
#include <stdio.h>
#include <stdlib.h>


int quit(void) {
	printf("Au revoir ... je fais du nettoyage ...\n");
}

void q2(void) {
	printf("vraiment au revoir !!!!\n");
}

void foo(int n) {
	if(n == 0)
		exit(0);
	
}

int main (void){

	char tmp[1024];
	atexit(q2);
	atexit(quit);
	while(fgets(tmp, sizeof tmp, stdin))
		printf("-> %s", tmp);
	
	return 0;
}
