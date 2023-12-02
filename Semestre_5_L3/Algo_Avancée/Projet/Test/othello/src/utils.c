#include "../includes/utils.h"

void majuscule(char *lettre) {
    if (*lettre >= 'a' && *lettre <= 'z') {
        *lettre -= 32;
    }
}
