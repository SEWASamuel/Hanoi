#include <stdio.h>
#include <stdlib.h>
#define NB_DISQUES 3 // correspond à la taille des quilles
#define NB_QUILLES 3 // correspond au nombre de quilles
#define TRUE 1
#define FALSE 0

// but : quitter le programme en cas d'erreur et afficher un message
void erreur(char *message){
    fprintf(stderr, "Erreur : %s \n", message);
}

// on va "créer" le type de variable : booleen
typedef int Bool;

// on va utiliser cette structure sn forme de matrice pour représenter le jeu du hanoi (les 3 tiges)
typedef struct Matrix{
    int objet[NB_DISQUES][NB_QUILLES];
}Matrice, THanoi;

// but : mettre une valeur dans une case de la matrice
void hanoiMettreValeur(THanoi *hanoi, int ligne, int colonne, int valeur){
    hanoi->objet[ligne][colonne] = valeur;
}

// but : initialiser la matrice représentant la tour de hanoi
void initTHanoi(THanoi *hanoi){

    for(int i=0 ; i<NB_DISQUES ; i++){
        for(int j=0 ; j<NB_QUILLES ; j++){
            hanoi->objet[i][j] = 0;
        }
    }

    for(int k=NB_QUILLES-1 ; k>=0; k--){ // on va de la hauteur la plus petite à la plus grande pour placer les disques du plus grand au plus petit
        hanoi->objet[k][0] = k+1;
    }
}

// // but : convertir un nombre en caractère pour l'affichage
// char convertEntierVersCaractere(int nb){
//     return nb+48;
// }

// but : afficher l'objet dans la console
void afficherHanoi(THanoi *hanoi){
    
    printf("\nTour de hanoi :\n\n");

    for(int i=0 ; i<NB_DISQUES ; i++){
        for(int j=0 ; j<NB_QUILLES ; j++){

            if(hanoi->objet[i][j] == 0){ // dans l'affichage, on remplacera les "0" par des "|"
                printf("|");
            }else{
                printf("%d",hanoi->objet[i][j]);
            }

            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

// but : savoir si un disque est present sur une quille
Bool disquePresent(THanoi *hanoi, int colonne){
    Bool present = FALSE;

    for(int i=0 ; i<NB_DISQUES ; i++){
        if(hanoi->objet[i][colonne] != 0){
            present = TRUE;
        }
    }

    return present;
}

// but : obtenir le niveau auquel on peut placer un disque
int hauteurPossible(THanoi *hanoi, int colonne){

    int hauteur = -1; // j'ai mis -1 car avec "NULL", ça marchait pas lors de la compilation
    Bool existe = FALSE;

    int i = 0;

    while(i<NB_DISQUES-1 && hanoi->objet[i][colonne] == 0){
        // TODO
        existe = FALSE;
        i++;
    }

}

// savoir si un disque "a" est plus petit qu'un disque "b"
Bool plusPetit(int a, int b){
    return a<b;
}

// but : deplacer le disque d'une quille à une autre
void deplacerDisque(THanoi *hanoi, int posQuilleDepart, int PosQuilleDestination){
    //TODO
}


void main(void){

    THanoi hanoi;

    initTHanoi(&hanoi);

    afficherHanoi(&hanoi);

    exit(0);
}