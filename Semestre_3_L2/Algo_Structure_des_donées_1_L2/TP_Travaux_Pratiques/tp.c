
void rotationD(noeudh_t **a){
    noeudh_t * t = *a;
    *a = t -> g;
    t -> g = (*a) -> d;
    (*a) -> d = t;
    
    misA5Hauteur(t);
    misA5Hauteur(*a);
}
