#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define NBR_MOTS 20 

char mot[30]="\0"; //une variable globale

void CopierMot(char *motSecret, char *mot)
{
    //Pour stocker le mot aleatoire dans la var global mot[]
    int i=0;
    while (motSecret[i] != '\0') {
        mot[i] = motSecret[i++];
    }
    mot[i] = '\0';
}

void ChoisirMot()
{
    //Creer une liste
    char motSecret[NBR_MOTS][20]={
        "HEUREUSEMENT",
        "MAGNIFIQUE",
        "BONJOUR",
        "ALEATOIRE",
        "ANTICONSTITUTIONEL",
        "FARFADET",
        "REELECTION",
        "ENTRAVER",
        "TIRAILLEMENT",
        "CONNAISSEUSE",
        "SALOPETTE",
        "TISONNIER",
        "ATTESTER",
        "MARINE",
        "POLITIQUE",
        "DECODER",
        "INTERNATIONAL",
        "TECHNIQUE"};
    int aleatoire;

    srand(time(NULL));
    
    aleatoire = (rand() %(NBR_MOTS)); //Pour choisir un mot de manière aléatoire dans la liste
    CopierMot(motSecret[aleatoire], mot);
}

int StringLength(char ch[])
{
    //Longueur taille du mot
    int i=0;
    while (ch[i]){ 
        i++;
    }
    return i;
}

//Pour compare 2 chaine
int ChaineComparer (char str1[], char str2[])
{
    int i=0;
    if (StringLength(str1) == StringLength(str2))
    {while (str1[i] && str2[i])
        {
            if (str1[i] != str2[i++]) {
                return 0;   //to quit
            }
        }
        return 1;   //to continue
    }
}

int TestLettre (char mot[], char lettre[])
{
    int i=0;
    while (mot[i])
    {
        if (mot[i++] == lettre[0]) {
            return 1;   // si la lettre est contenue dans le mot
        }
    }
    return 0;
}

int Affichage (char mot[], char trouves[])
{
    int i=-1, win=1;
    printf("\nMot à trouver : ");
    while (mot[++i])
    {
        if (TestLettre(trouves,&mot[i])==1){
            printf("%c ",mot[i]);
        }else{
            printf("_ " );
            win=0;
        }
    }
    return win;
}

int PenduDessiner(int erreurs)
{
    //Affichage l'image de pendu
    printf("\n\n\n" );
    if (erreurs <= 3){
        printf("\n" );
    }else{
        printf(" ________\n" );
    }if (erreurs >= 5) {
        printf(" |/     |\n" );
        
    }else if (erreurs >= 3) {
        printf(" |/\n" );
    }else if (erreurs >= 2) {
        printf(" |\n" );
    }else{
        printf("\n" );
    }
    if (erreurs >= 6) {
        printf(" |      O\n" );
    }else if (erreurs >= 2) {
        printf(" |\n" );
    }else {
        printf("\n" );
    }
    if (erreurs >= 7) {
        printf(" |     /|\n" );
    }else if (erreurs >= 2) {
        printf(" |\n" );
    }else {
        printf("\n" );
    }
    if (erreurs >= 8) {
        printf(" |      |\n" );
    }else if (erreurs >= 2) {
        printf(" |\n" );
    }else {
        printf("\n" );
    }
    if (erreurs == 9) {
        printf("\n\nAttention !!! Une seule dernière chance pour toi !!\n" );
    }else if (erreurs >= 2) {
        printf("_|_\n" );
    }
    if (erreurs >= 10) {
        printf("\n\nGAME OVER ! \n");
        printf("\nPerdu ! Pend-toi ! \n\n");
        return 0;
    }
    else {return 1;}
}

// On met la lettre en majuscule
char to_upper(char s[])
{
    int i = 0;
    while(s[i] != '\0'){
        if(isalpha(s[i])){
            if(s[i] >= 97){
                s[i] -= 32;
            }
        }
        i++;
    }
}

int main()
{
    char lettre[5]="\0", trouves[30]="\0";
    int fautes=0, n=0;
    int i = 0;
    ChoisirMot();
    printf("\n-----Bienvenue dans le Pendu !--------\n");
    while ((ChaineComparer(lettre, "quit" ) != 1) && (Affichage(mot, trouves) != 1) && (PenduDessiner(fautes) == 1))
    {
        printf("\n\n\n\n\nSaisissez une lettre : '%s'\n\n",trouves);
        printf("\n\n\nEntrez une lettre ou 'quit' pour quitter\n" );
        scanf("%s",lettre);
        to_upper(lettre);   
        printf("\n\n" );
        if (TestLettre(mot,lettre)){
            trouves[n++]= lettre[i];
        }
        else if (ChaineComparer(lettre, "quit" ) != 1){
            fautes++;
        }
        
        printf("\nVous avez trouvé les lettres '%s'\n\n",trouves);
        printf("\n\n Vous avez %d fautes\n\n",fautes);
        printf("\nNombre d’erreurs restantes : %d \n\n\n",(10-fautes)); //afficher le nombre d’erreurs restantes
        
        
    }
    if((TestLettre(mot, trouves) == 1) && (Affichage(mot, trouves) == 1)) /* gagné !!! */
    {
        printf("\n\n\n WINNER - GAGNÉ\n");
        printf("Bravo ! Vous remportez la partie !\n\n\n");
        return 0;
    }
    if(ChaineComparer(lettre, "quit") == 1){
        return 0;
    }
    getchar();
    getchar();
    
    return 0;
    
}



