

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



typedef struct ll_node ll_node_t;
typedef int element_t;

struct ll_node{
	element_t data;
	struct ll_node* next;
};
        
ll_node_t* ll_add (ll_node_t* queue, element_t e)
{
	ll_node_t* l = malloc(sizeof(*l));
	assert(l);
	l -> data = e;
	l -> next = queue;
 	return l;
}

int Vide(ll_node_t* l);
void afficher(ll_node_t * l);
void afficher2(ll_node_t * l);
int size(ll_node_t* queue);
ll_node_t* insert( ll_node_t* l, element_t e, int pos);
void ll_clear(ll_node_t** headref);


int main(void){

	ll_node_t* l = NULL;
	l = ll_add(l,1);
	l = ll_add(l, 30);
	l = ll_add(l, 0);
	l = ll_add(l, -3);
	//int a = size(l);

	//int a = Vide(l);
	//printf("%d", a);
	//afficher(l);
	//afficher2(l);
	//insert(l, 5, 2);
	ll_clear(&l);
	int a = Vide(l);
	printf("%d", a);
	//afficher(l);
	return 0;
}


int Vide(ll_node_t* l){

	if (l != NULL) return 0; // return (l == NULL);
		return 1;
	}

	void afficher(ll_node_t * queue){

	if (queue -> next != NULL){

		printf("%d, ", queue -> data);
		afficher(queue -> next);
	}
	else printf("%d, NULL\n", queue -> data);
}



void afficher2(ll_node_t * queue){

    if (queue -> next != NULL){

		afficher2(queue -> next);
		printf(" %d,", queue -> data);
    }
    else printf("NULL, %d, ", queue -> data);
}

int size(ll_node_t* l){

    int i = 0;
    while (l != NULL){
        i++;
        l = l -> next; // et non pas juste l -> next
    }
    return i;
}
    

ll_node_t* insert( ll_node_t* l, element_t e, int pos){
    
    
    ll_node_t* head = l;
    ll_node_t* new_cell = malloc(sizeof(*new_cell));
    new_cell -> data = e;
 
    int i = 0;
    ll_node_t* temp;
    int size_l = size(l);
    if (pos > size_l){
        printf("Erreur\n");
        exit(1);
    }
    if (pos == 0) ll_add(l, e);
    while (i != pos -1){
		l = l -> next;
		i++;
    }
    temp = l -> next;
    l -> next = new_cell;
    new_cell -> next = temp;
    
    return head;  
}

void ll_clear(ll_node_t** headref){


ll_node_t* prev = *headref;

	while (*headref){
		*headref = (*headref) -> next;
		printf("Delete element %d\n", (*headref) -> data);
		free(prev);
		prev = *headref;
	} 
	// return NULL;

}



/////////// push back

/////////// push front

/////////// pop back

/////////// pop front

/////////// is incrise


