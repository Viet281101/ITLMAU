
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main() {
    char* my_name = "Viet Nguyen";
    int nb_noeuds = 5;
    unsigned long hash_value = get_index(my_name, nb_noeuds);
    printf("Le hash de mon prénom 'Viet Nguyen' est : %ld\n", hash_value);
    return 0;
}

