/*//ne fonctionne pas : error : Segmentation fault (core dumped)
char *my_strcpy_03(char *dst, const char *src){
    int *idst = (int*)dst;
    int *isrc = (int*)src;

    char *ret = dst;

    int continuer = 1;

    while(1) {
        for(int i = 0; i < (int)sizeof(int) - 1; ++i){
            if(src[i] == '\0'){
                continuer = 0;
                break;
            }

        if(!continuer){
            break;
        }

        *(idst++) = *(isrc++);
        }
    }

    dst = (char*)idst;
    while((*dst++ = *src++));

    return ret;
}
*/


/*
char *my_strcpy_03(char *dst, const char *src) {
    char *ret = dst;
    int *dstInt = (int *)dst;
    int *srcInt = (int *)src;
    int continuer = 1;
    //fprintf(stderr, "je suis 57\n");
    while(1){
        src = (char *)srcInt;
        for(int i = 0; i < (int)sizeof(int) -1; i++){ //I added -1 because if the 4th
            //fprintf(stderr, "adresse %p : valeur %d\n", src+i, src[i]);
            if (src[i] == '\0') {
                continuer = 0;
                break;
            }
        }
        if (!continuer) break;

        //fprintf(stderr, "je suis %d\n", __LINE__);
        *(dstInt++) = *(srcInt++);
    }
    //fprintf(stderr, "je suis %d\n", __LINE__);
    dst = (char *)dstInt;
    while((*(dst++) = *(src++)));

    return ret;
}
*/


/*
char *my_strcpy_03(char *dst, const char *src){
    char * save = dst;
    int *isrc = (int *)src, *idst = (int *)dst;

    do{
        if(((char *)isrc)[0]) {
            if(((char *)isrc)[1]) {
                if(((char *)isrc)[2]) {
                    *idst = *isrc;
                    if(!((char *)isrc)[3]) break;
                } else {
                    *((short *)idst) = *((short *)isrc);
                    ((char *)idst)[2] = 0;
                    break;
                }
            } else {
                *((short *)idst) = *((short *)isrc);
                break;
            }
        } else {
            ((char *)idst)[0] = 0;
            break;
        }
        ++idst;++isrc;
    } while(1);
    return save;
}
*/
