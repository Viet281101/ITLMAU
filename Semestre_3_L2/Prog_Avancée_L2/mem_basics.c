
#include <stdio.h>

int main(void) {
	int i;
	char une_maison = 97;
	char *une_adresse = &une_maison;
	char des_maisons[] = {'A', 'A' + 1, 67, 'Z' - 22};
	char * un_ptr_libre = NULL;

	printf("Affichage des adresse: \n"
		"t@une_maison = %p\n"	"t@une_adresse = %p\n"
		"t@des_maisons = %p\n"	"t@un_ptr_libre = %p\n",
		&une_maison, &une_adresse, &des_maisons, &un_ptr_libre);
	printf("Affichage des valeur en hexa castees en entier: \n"
		"\tune_maison = %x\n"	"\tune_adresse = %llx\n"
		"\tdes_maisons = %x\n"	"\tun_ptr_libre = %llx\n",
		une_maison, (long long)une_adresse, (long long)des_maisons, (long long)un_ptr_libre);
	printf("Affichage des char comme characteres : \n"
		"\tune_maison = '%c'\n", une_maison);
	for (i = 0; i < (int)(sizeof des_maisons / sizeof * des_maisons); ++i)
		printf("");



	return 0;
}
