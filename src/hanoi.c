#include<stdio.h>
#include "../include/hanoi.h"
#include "../include/evenements.h"
#include "../include/sequence.h"

// but : mettre une valeur dans une case de la matrice
void modifierCaseHanoi(THanoi *hanoi, int ligne, int colonne, int valeur){
    hanoi->objet[ligne-1][colonne-1] = valeur;//MODIF ICI
}

// but : initialiser la matrice représentant la tour de hanoi
void initTHanoi(THanoi *hanoi){

    for(int i=0 ; i<NB_DISQUES ; i++){
        for(int j=0 ; j<NB_QUILLES ; j++){
            // hanoi->objet[i][j] = 0;
            modifierCaseHanoi(hanoi, i+1, j+1, 0); //MODOF ICI
        }
    }

    for(int k=NB_QUILLES-1 ; k>=0; k--){ // on va de la hauteur la plus petite à la plus grande pour placer les disques du plus grand au plus petit
        // hanoi->objet[k][0] = k+1;
        modifierCaseHanoi(hanoi, k+1, 1, k+1);// MODIF ICI
    }
}

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

// but : verifier qu'on peut deplacer un disque donné à une destinstion donnée
Bool deplacementPossible(THanoi *hanoi, int quilleDepart, int quilleDestination){
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
        erreur("La hauteur de retrait possible n'est pas valide\n");
        printf("la hauteur de retrait obtenue par la fonction est : %d\n", hauteurRetrait);
    }

    if(hauteurPlacement < 0 || hauteurPlacement > NB_QUILLES-1){ // il faut que la valeur renvoyée par la fonction "hauteurPlacementQuillePossible" soit valable (0 <= v <= NB_QUILLES)
        possible = FALSE;
        erreur("La hauteur de placement possible n'est pas valide\n");
        printf("la hauteur de placement obtenue par la fonction est : %d\n", hauteurPlacement);
    }

    if(quilleDepart == quilleDestination){ // il faut que la la quille où on prends le disque ne soit pas la meme quille où on va le placer
        possible = FALSE;
        erreur("la quille de depart est la même que la quille de destination");
        printf("Quille de depart : %d\nQuille de destination : %d\n", quilleDepart, quilleDestination);
    }

    int valeurDisqueRetire = hanoi->objet[hauteurRetrait][quilleDepart];
    int valeurDisqueDestinationSupport = hanoi->objet[hauteurPlacement+1][quilleDestination];

    if(valeurDisqueRetire < 1){
        erreurQuitter("aucun disque n'a ete retire");
    }

    if(!(hauteurPlacement > NB_QUILLES-1)){ // si la quille de destination n'est pas vide
        if(valeurDisqueRetire > valeurDisqueDestinationSupport){ // "hauteurPlacement+1" parce qu'on veut la valeur du disque qui va être en dessosus du diasque qu'on va déplacer
            // TODO : evaluer le cas ou la quille de destination est vide. On n'aurait donc aucun disque de support à verifier
            if(!quilleVide(hanoi, quilleDestination)){
                possible = FALSE;
                erreur("le disque a deplacer est plus grand que le disque sur lequel on le pose\n");
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

    if(deplacementPossible(hanoi, quilleDepart, quilleDestination) == TRUE){
        printf("\nDeplacement possible! (de la quille %d a %d)\n", quilleDepart+1, quilleDestination+1);
        int hauteurRetrait = hauteurRetraitQuillePossible(hanoi, quilleDepart);
        int hauteurPlacement = hauteurPlacementQuillePossible(hanoi, quilleDestination);

        int aux = hanoi->objet[hauteurRetrait][quilleDepart];
        // hanoi->objet[hauteurRetrait][quilleDepart] = 0;
        // hanoi->objet[hauteurPlacement][quilleDestination] = aux;
        modifierCaseHanoi(hanoi, hauteurRetrait+1, quilleDepart+1, 0);//MODIF ICI
        modifierCaseHanoi(hanoi, hauteurPlacement+1, quilleDestination+1, aux);//MODIF ICI
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

void executerDeplacement(THanoi *hanoi, struct Deplacement *depl){
    // ici, pas besoin de verifier si le deplacement est vide ou pas, car la fonction afficherDeplacement le fait
    printf("Execution du deplacement : "); afficherDeplacement(depl);
    deplacerDisque(hanoi, obtenirDep(depl)-1, obtenirDest(depl)-1);
    afficherHanoi(hanoi);
}

void executerSequence(THanoi *hanoi, struct Sequence *sequence){
    // ici, on verifie si la sequence n'est pas vide
    if(sequenceVide(sequence)){
        erreur("executerSequence (sequence vide)");
        return;
    }

    while(!sequenceVide(sequence)){
        executerDeplacement(hanoi, defilerSequence(sequence));
    }
}

void ResolutionHanoiRecursif(THanoi *hanoi, int nbQuilles, int quilleDepart, int quilleDestination){
    if(nbQuilles == 1){
        deplacerDisque(hanoi, quilleDepart-1, quilleDestination-1);
    }else{
        int quilleRestante = 6 - (quilleDepart + quilleDestination);
        
        ResolutionHanoiRecursif(hanoi, nbQuilles-1, quilleDepart, quilleRestante);

        deplacerDisque(hanoi, quilleDepart-1, quilleDestination-1); // TODO : corriger la fooction deplacerDisque our qu'on ait pas de soicis d'index (0=1)
        ResolutionHanoiRecursif(hanoi, nbQuilles-1, quilleRestante, quilleDestination);
    }
}

//toujours initialiser le paramètre "arret" à : vrai
struct Sequence* ResolutionHanoiRecursifSequence(THanoi * hanoi, struct Sequence *sequence, int nbDisques, int quilleDepart, int quilleDestination, Bool arret){
    if(nbDisques == 1){
        // deplacerDisque(hanoi, quilleDepart, quilleDestination);
        ajouterDeplacement(sequence, quilleDepart, quilleDestination);
    }else{
        int quilleRestante = 6 - (quilleDepart + quilleDestination);
        
        ResolutionHanoiRecursifSequence(hanoi, sequence, nbDisques-1, quilleDepart, quilleRestante, FALSE);

        // deplacerDisque(hanoi, quilleDepart, quilleDestination);
        ajouterDeplacement(sequence, quilleDepart, quilleDestination);

        ResolutionHanoiRecursifSequence(hanoi, sequence, nbDisques-1, quilleRestante, quilleDestination, FALSE);
    }

    if(arret){
        return sequence;
    }
}

// but : faire jouer l'utilisateur
void jouer(THanoi *hanoi){
    printf("Bienvenu au jeu du Hanoi!\nRegles du jeu :\n\n\t- Saisissez le numero de la quille ou vous voulez retirer le disque et ensuite le numero de la quille ou vous voulez le poser\n\n\t- saisir 0 ou une valeur negative pour quitter la partie\n\n");
    // on créé l'objet et on l'initialise
    initTHanoi(hanoi);

    printf("voici le disposition initiale\n");
    afficherHanoi(hanoi);

    // ces deux entiers serviront au choix de deplacement de l'utilisateur
    int quilleDep;
    int quilleDest;

    // cette variable servira a faire quitter la boucle while dans le cas ou le joueur voudrait quitter la partie
    Bool quitter = FALSE;


    // on fait une boucle qui se répète tant que le hanoi n'est pas résolus
    while(!HanoiResolu(hanoi) && !quitter){
        /**
         * à faire :
         * - faire saisir une quille de depart et de destination à l'utilisateur
         * - faire verifier si c'est possible
         *      -> si c'est possible, on la refait saisir
         *      -> sinon on effectue le dplacement et on affiche les tours
         *   On repete le processus jusqu'à ce que le hanoi soit résolu ou que l'utilisateur quitte le programme
         */

        do{
            quilleDep = demandeSaisieEntier("Saisissez la quille d'ou vous voulez retirer le disque :") - 1;
            quilleDest = demandeSaisieEntier("Saisissez la quille ou vous voulez poser le disque :") - 1;

            if(quilleDep+1 < 1 || quilleDest+1 < 1){
                quitter = TRUE;
                printf("A bientot\n");
                return;
            }

        }while(!deplacementPossible(hanoi, quilleDep, quilleDest));

        deplacerDisque(hanoi, quilleDep, quilleDest);
        afficherHanoi(hanoi);
    }

    if(HanoiResolu(hanoi)){
        printf("\nBravo ! Vous avez gagne la partie\n");
    }
}