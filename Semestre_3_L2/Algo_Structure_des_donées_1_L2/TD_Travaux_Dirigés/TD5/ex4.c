
typedef struct s_cellule_t
{
	int val; // valeur
	struct s_cellule_t* suiv; // suiv
} cellule_t;
// la liste vide sera NULL


void ajoutQueue ( int val, cellule_t ** li){
	while ((*li) -> suiv!=NULL)
		(*li) = &liste -> suiv;
	(*li) -> suiv = consL(vol, NULL);
}


cellule_t* consL(int V, cellule_t * queue){
	cellule_t * n = (cellule_t*) malloc(signal(*queue));
	if (n == NULL)
		exit(1);
	n -> val = v;
	n -> suiv = queue;
	return n;
}

int main(void){
	
	return 0;
}


