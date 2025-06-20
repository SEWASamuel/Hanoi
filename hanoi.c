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

// but : mettre un peu de graphisme sur des titres pour afficher les dans la console
void annonce(char *message){
    printf("****************************************************************\n\t%s\n****************************************************************\n", message);
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

// but : obtenir le niveau auquel on peut placer un disque selon la colonne(quille) passée en paramètre
int hauteurPlacementQuillePossible(THanoi *hanoi, int colonne){

    int i = 0; // on initialise le compteur à 0

    while((i < NB_DISQUES) && (hanoi->objet[i][colonne] == 0)){ // condition : on a pas dépassé la hauteur des quilles et  à la hauteur du compteur on na pas de disques
        i++;
    }

    return i-1; // on retourne la valeur du nombre de cases vides consecutives qu'on a rencontrées
}

// but : obtenir le niveau auquel on peut retirer un disque selon la colonne(quille) passée en paramètre
int hauteurRetraitQuillePossible(THanoi *hanoi, int colonne){
    int i = 0; // on initialise la compteur à 0

    while(i < NB_DISQUES-1 && (hanoi->objet[i][colonne] == 0)){
        i++;
    }

    return i;// on retourne la valeur de la hauteur du disque le plus élvevé
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

    // main est un test

    THanoi hanoi;

    // on initialise le jeu du hanoi
    initTHanoi(&hanoi);

    // on affiche le jeu du janoi qu'on vient de tester pour voir si il es bien initialisé
    annonce("TEST : affichage de la tour de hanoi");
    afficherHanoi(&hanoi);


    // on evalue la hauteur de olacements possibles sur toutes les quilles du hanoi
    annonce("test de : hauteurPlacementQuillePossible");
    printf("voici la hauteur de la quille 1 : %d\n", hauteurPlacementQuillePossible(&hanoi,0));
    printf("voici la hauteur de la quille 1 : %d\n", hauteurPlacementQuillePossible(&hanoi,1));
    printf("voici la hauteur de la quille 1 : %d\n", hauteurPlacementQuillePossible(&hanoi,2));

    // on evalue la hauteur de olacements possibles sur toutes les quilles du hanoi
    annonce("test de : hauteurretraitQuillePossible");
    printf("voici la hauteur de la quille 1 : %d\n", hauteurRetraitQuillePossible(&hanoi,0));
    printf("voici la hauteur de la quille 1 : %d\n", hauteurRetraitQuillePossible(&hanoi,1));
    printf("voici la hauteur de la quille 1 : %d\n", hauteurRetraitQuillePossible(&hanoi,1));

    exit(0);
}