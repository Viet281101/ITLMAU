
typedef struct s_cellule_t
{
	int val; // valeur
	struct s_cellule_t* suiv; // suiv
} cellule_t;
// la liste vide sera NULL


int somme (cellule_t* li){
	int x;
	for (x = 0; li != NULL; li = li -> suiv)
		x += li -> suiv;
	return x;
}


int main(void){
	
	return 0;
}


