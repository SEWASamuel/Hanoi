#include <stdio.h>
#include <stdlib.h>
#define NB_DISQUES 3 // correspond à la taille des quilles
#define NB_QUILLES 3 // correspond au nombre de quilles
#define TRUE 1
#define FALSE 0

// but : afficher un message d'erreur personnalidé dans la console
void erreur(char *message){
    fprintf(stderr, "Erreur : %s \n", message);
}

// but : en plus d'afficher le message d'erreur dans la console, on quitte le programme
void erreurQuitter(char *message){
    fprintf(stderr, "Erreur : %s \n", message);
    exit(1);
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
        printf("\t");
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

// but : obtenir le niveau auquel on peut retirer un disque selon la colonne(quille) passée en paramètre
int hauteurRetraitQuillePossible(THanoi *hanoi, int colonne){
    int i = 0; // on initialise la compteur à 0

    while(i < NB_DISQUES-1 && (hanoi->objet[i][colonne] == 0)){
        i++;
    }

    return i;// on retourne la valeur de la hauteur du disque le plus élvevé
}

// but : obtenir le niveau auquel on peut placer un disque selon la colonne(quille) passée en paramètre
int hauteurPlacementQuillePossible(THanoi *hanoi, int colonne){

    int i = 0; // on initialise le compteur à 0

    while((i < NB_DISQUES) && (hanoi->objet[i][colonne] == 0)){ // condition : on a pas dépassé la hauteur des quilles et  à la hauteur du compteur on na pas de disques
        i++;
    }

    return i-1; // on retourne le niveau de hauteur du dernier emplacement vide
}

// savoir si un disque "a" est plus petit qu'un disque "b"
Bool plusPetit(int a, int b){
    return a<b;
}

Bool quilleVide(THanoi *hanoi, int numQuille){

    Bool vide = TRUE;

    int i =0;

    while((i<NB_QUILLES) && (vide == TRUE)){
        if(hanoi->objet[i][numQuille] != 0){
            vide = FALSE;
        }
        i++;
    }

    return vide;
}

Bool afficherBool(Bool b){
    if(b == TRUE){
        printf("TRUE\n");
    }else if(b == FALSE){
        printf("FALSE\n");
    }else{
        printf("Booleen invalide\n");
    }
}

// but : verifier qu'on peut deplacer un disque donné à une destinstion donnée
Bool DeplacementPossible(THanoi *hanoi, int quilleDepart, int quilleDestination){
    /**
     * On va verifier qu'on peut déplacer un disque d'une quille à un autre
     * il faut que :
     *  La quille de depart ne soit pas la même que la quille de dstination
     *  Il y ait au moins un disque sur le quille de départ
     *  Il y ait de la place sur la quille de destination
     *  Le disque de depart ne soit pas mis au dessus d'un disque plus petit
     */

    Bool possible = TRUE;

    int hauteurRetrait = hauteurRetraitQuillePossible(hanoi, quilleDepart);
    int hauteurPlacement = hauteurPlacementQuillePossible(hanoi, quilleDestination);


    if(hauteurRetrait < 0 || hauteurRetrait > NB_DISQUES-1){ // il faut que la quille retirée soit entre 0 et le NB_QUILLES-1
        possible = FALSE;
        erreur("La hauteur de retrait possible n'est pas valide");
        printf("la hauteur de retrait obtenue par la fonction est : %d", hauteurRetrait);
    }

    if(hauteurPlacement < 0 || hauteurPlacement > NB_QUILLES-1){ // il faut que la valeur renvoyée par la fonction "hauteurPlacementQuillePossible" soit valable (0 <= v <= NB_QUILLES)
        possible = FALSE;
        erreur("La hauteur de placement possible n'est pas valide");
        printf("la hauteur de placement obtenue par la fonction est : %d", hauteurPlacement);
    }

    if(quilleDepart == quilleDestination){ // il faut que la la quille où on prends le disque ne soit pas la meme quille où on va le placer
        possible = FALSE;
        erreur("la quille de depart est la même que la quille de destination");
        printf("Quille de depart : %d\nQuille de destination : %d\n", quilleDepart, quilleDestination);
    }

    int valeurDisqueRetire = hanoi->objet[hauteurRetrait][quilleDepart];
    int valeurDisqueDestinationSupport = hanoi->objet[hauteurPlacement+1][quilleDestination];

    if(!(hauteurPlacement > NB_QUILLES-1)){ // si la quille de destination n'est pas vide
        if(valeurDisqueRetire > valeurDisqueDestinationSupport){ // "hauteurPlacement+1" parce qu'on veut la valeur du disque qui va être en dessosus du diasque qu'on va déplacer
        // TODO : evaluer le cas ou la quille de destination est vide. On n'aurait donc aucun disque de support à verifier
        if(!quilleVide(hanoi, quilleDestination)){
            possible = FALSE;
            erreur("le disque a deplacer est plus grand que le disque sur lequel on le pose");
            printf("Valeur du disque de départ : %d\nValeur du disque de support de destination : %d\n", valeurDisqueRetire, valeurDisqueDestinationSupport);
            }
        }
    }

    return possible;
}

// but : deplacer le disque d'une quille à une autre
void deplacerDisque(THanoi *hanoi, int quilleDepart, int quilleDestination){
    /**
     * On va verifier qu'on peut déplacer un disque d'une quille à un autre
     * il faut que :
     *  Il y ait au moins un disque sur le quille de départ
     *  Il y ait de la place sur la quille de destination
     *  Le disque de depart ne soit pas mis au dessus d'un disque plus grand
     */

    if(DeplacementPossible(hanoi, quilleDepart, quilleDestination) == TRUE){
        printf("\nDeplacement possible! (de la quille %d a %d)\n", quilleDepart+1, quilleDestination+1);
        int hauteurRetrait = hauteurRetraitQuillePossible(hanoi, quilleDepart);
        int hauteurPlacement = hauteurPlacementQuillePossible(hanoi, quilleDestination);

        int aux = hanoi->objet[hauteurRetrait][quilleDepart];
        hanoi->objet[hauteurRetrait][quilleDepart] = 0;
        hanoi->objet[hauteurPlacement][quilleDestination] = aux;
    }else{
        printf("\nDEPLACEMENT IMPOSSIBLE!!!!!! (de la quille %d a %d)\n", quilleDepart+1, quilleDestination+1);
    }
}

// but : vérifier si le jeu du hanoi est résolu
Bool HanoiResolu(THanoi *hanoi){
    Bool resolu = TRUE;

    /**
     * on va parcourir les cases de la dernière colonne de la matrice (c-à-d les niveaux de la dernière quille du hanoi)
     * Pour ceci, on va  se servir d'un compteur i.
     * Et pour chaque iteration de i, on va vérfier si la valeur de la case parcourue est égale à i+1.
     * "i+1" car "i" commence avec la valeur 0
     * Si au moins un disque n'est pas au bon niveau, le booléen "resolu" devient faux
     */

    for(int i=0 ; i<NB_DISQUES ; i++){
        if(i+1 != hanoi->objet[i][NB_QUILLES-1]){
            resolu = FALSE;
        }
    }

    return resolu;
}

void resolutionHanoiManuelle3x3(THanoi *hanoi){
    deplacerDisque(hanoi, 0, 2);
    afficherHanoi(hanoi);

    deplacerDisque(hanoi, 0, 1);
    afficherHanoi(hanoi);

    deplacerDisque(hanoi, 2, 1);
    afficherHanoi(hanoi);

    deplacerDisque(hanoi, 0, 2);
    afficherHanoi(hanoi);

    deplacerDisque(hanoi, 1, 0);
    afficherHanoi(hanoi);

    deplacerDisque(hanoi, 1, 2);
    afficherHanoi(hanoi);

    deplacerDisque(hanoi, 0, 2);
    afficherHanoi(hanoi);
}


void main(void){

    // main est un test

    THanoi hanoi;

    // on initialise le jeu du hanoi
    initTHanoi(&hanoi);

    // // on affiche le jeu du janoi qu'on vient de tester pour voir si il es bien initialisé
    // annonce("TEST : affichage de la tour de hanoi");
    // afficherHanoi(&hanoi);


    // // on evalue la hauteur de placements possibles sur toutes les quilles du hanoi
    // annonce("test de : hauteurPlacementQuillePossible");
    // printf("voici la hauteur de la quille 1 : %d\n", hauteurPlacementQuillePossible(&hanoi,0));
    // printf("voici la hauteur de la quille 2 : %d\n", hauteurPlacementQuillePossible(&hanoi,1));
    // printf("voici la hauteur de la quille 3 : %d\n", hauteurPlacementQuillePossible(&hanoi,2));

    // // on va tester un deplacement de la quille n°1 à la Quille n°2 (normalement possible)
    // annonce("Test d'un deplacement de la quille 1 a la quille 2 (possible)");
    // deplacerDisque(&hanoi, 0, 1);
    // afficherHanoi(&hanoi);

    // // on va tester un deplacement de la quille n°1 à la Quille n°2 (normalement possible)
    // annonce("Test d'un deplacement de la quille 1 a la quille 3 (possible)");
    // deplacerDisque(&hanoi, 0, 2);
    // afficherHanoi(&hanoi);

    // // on va tester un deplacement de la quille n°1 à la Quille n°2 (normalement impossible)
    // annonce("Test d'un deplacement de la quille 1 a la quille 3 (impossible)");
    // deplacerDisque(&hanoi, 0, 2);
    // afficherHanoi(&hanoi);

    // // on va tester un deplacement de la quille n°2 à la Quille n°3 (normalement possible)
    // annonce("Test d'un deplacement de la quille 1 a la quille 3 (possible)");
    // deplacerDisque(&hanoi, 1, 2);
    // afficherHanoi(&hanoi);


    // // test de resolution manuelle de la tour de hanoi
    // annonce("test de resolution du jeu manuellement");

    // deplacerDisque(&hanoi, 0, 2);
    // afficherHanoi(&hanoi);

    // deplacerDisque(&hanoi, 0, 1);
    // afficherHanoi(&hanoi);

    // deplacerDisque(&hanoi, 2, 1);
    // afficherHanoi(&hanoi);

    // deplacerDisque(&hanoi, 0, 2);
    // afficherHanoi(&hanoi);

    // deplacerDisque(&hanoi, 1, 0);
    // afficherHanoi(&hanoi);

    // deplacerDisque(&hanoi, 1, 2);
    // afficherHanoi(&hanoi);

    // deplacerDisque(&hanoi, 0, 2);
    // afficherHanoi(&hanoi);

    // // Test de la fonction : quilleVide
    // printf("La quille 1 est vide :");
    // afficherBool(quilleVide(&hanoi, 0));
    // printf("La quille 2 est vide :");
    // afficherBool(quilleVide(&hanoi, 1));
    // printf("La quille 3 est vide :");
    // afficherBool(quilleVide(&hanoi, 2));

    // Test de la fonction : hanoiResolu
    annonce("test : hanoiResolu");
    afficherHanoi(&hanoi);

    if(HanoiResolu(&hanoi)){
        printf("Hanoi valde!\n");
    }else{
        printf("Hanoi NON valide!\n");
    }

    resolutionHanoiManuelle3x3(&hanoi);

    if(HanoiResolu(&hanoi)){
        printf("Hanoi valde!\n");
    }else{
        printf("Hanoi NON valide!\n");
    }

    exit(0);
}