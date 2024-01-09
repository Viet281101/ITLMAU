

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct vector vector_t;

struct vector {
	int max_size;
	int size;
	int *data;
};


/*vecteur_new*/
vector_t * vector_new(void){
	assert(vec);
	vector_t * vec = malloc(sizeof *vec);
	vec -> size = 0;
	vec -> max_size = 1024;
	vec -> data = malloc(vec ->max_size * sizeof * (vec -> data));
	assert(vec -> data);
	return vec;
}


/*vector_size*/
int vector_size (vector_t *vec){
	return vec -> size;
}


/*vector_max_size*/
int vector_max_size (vector_t * vec){
	return vec -> max_size;
}


/*vector_print*/
void vector_print (vector_t * vec){
	int i;
	for (i = 0; i < vec -> size; i ++){	
		printf("%d ", vec -> data[i]);
		printf("\n");
	}
}


/*vector_push*/
void vector_push_back(vector_t *vec, int elem){
	// while (vec)
	// 	head = &(vec)->data;

	// vec = malloc(sizeof(*vec));
	// (vec)->elem = elem;
	// (vec)->data = NULL;

	if (vec -> size == vec -> max_size){
		vec -> max_size *= 2;
		// int * temp = vec -> data;
		vec -> data = realloc(vec -> data, ((vec -> max_size) * sizeof * (vec -> data)));
	}
	vec -> data[vec -> size] = e;
	vec -> size += 1;
	return vec;
}


/*vector_empty*/


/*vector_delete*/


int main (void){

	return 0;
}

