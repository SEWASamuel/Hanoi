#include<stdio.h>
#include "../include/hanoi.h"
#include "../include/evenements.h"

// CONVERSIONS

    // MATRICE -> HANOI

int ligneToHauteur(int ligne){
    return (NB_DISQUES - ligne);
}

int colonneToQuille(int colonne){
    return (colonne + 1);
}

    // HANOI -> MATRICE

int hauteurToLigne(int hauteur){
    return (NB_DISQUES - hauteur);
}

int quilleToColonne(int quille){
    return (quille-1);
}

int obtenirDisque(THanoi *hanoi, int hauteur, int quille){
    return hanoi->objet[hauteurToLigne(hauteur)][quilleToColonne(quille)];
}

// but : mettre une valeur dans une case de la matrice
void modifierDisque(THanoi *hanoi, int hauteur, int quille, int valeur){
    hanoi->objet[hauteurToLigne(hauteur)][quilleToColonne(quille)] = valeur;
}

// but : initialiser la matrice représentant la tour de hanoi
void initTHanoiVide(THanoi *hanoi){
    // ici , on parcourt toutes les cases de du objet de hanoi pour les mettre à vide (0)
    for(int i=1 ; i<=NB_DISQUES ; i++){
        for(int j=1 ; j<=NB_QUILLES ; j++){
            modifierDisque(hanoi, i, j, 0);
        }
    }
}

// but : initialiser la matrice représentant la tour de hanoi
void initTHanoi(THanoi *hanoi){
    // ici , on parcourt toutes les cases de du objet de hanoi pour les mettre à vide (0)
    for(int i=1 ; i<=NB_DISQUES ; i++){
        for(int j=1 ; j<=NB_QUILLES ; j++){
            modifierDisque(hanoi, i, j, 0);
        }
    }

    // Ici, on parcourt tous les niveaud de la première quille de sorte à placer les disques à leur position initiale
    for(int k=1 ; k<=NB_DISQUES ; k++){
        modifierDisque(hanoi, k, 1, NB_DISQUES-k+1);
    }
}

// but : afficher l'objet dans la console
void afficherHanoi(THanoi *hanoi){
    
    printf("\nTour de hanoi :\n\n");

    /**
     * ici, on parcour toute la matrice pour afficher le jeu du hanoi
     * Où il y a des disques, on affiche lavaleur du disque
     * Et où il n'u a pas de disque, on affiche une barre (pour former une quille)
     */
    for(int i=1 ; i<=NB_DISQUES ; i++){
        for(int k=1 ; k<=NB_QUILLES ; k++){
            if(obtenirDisque(hanoi, NB_DISQUES-i+1, k) == 0){
                printf("| ");
            }else{
                printf("%d ", obtenirDisque(hanoi, NB_DISQUES-i+1, k));
            }
        }
        sautDeLigne(1);
    }
    sautDeLigne(1);
}

// but : savoir si un disque est present sur une quille
Bool disquePresent(THanoi *hanoi, int quille){
    Bool present = FALSE;
    int i = NB_DISQUES;

    while(hauteurValide(i) && present == FALSE){
        if(obtenirDisque(hanoi, i, quille) != 0){
            present = TRUE;
        }
        i--;
    }
    //AMELIORER : au lieu d'une boucle for, on peut utiliser une boucle while qui s'arrêtera lorsqu'on aura trouvé au moins un disque sur une colonne
    return present;
}

Bool hauteurValide(int niveauHauteur){
    return ((niveauHauteur >= 1) && (niveauHauteur <= NB_DISQUES));
}

int obtenirHauteurDisqueAuSommet(THanoi *hanoi, int quille){
    /**
     * on commence à parcourir les cases à partir du haut (donc on initialise la compteur i à NB_DISQUES)
     * et tant qu'on ne trouve pas de disque, on continue à descendre
     */
    int i = NB_DISQUES;

    while(hauteurValide(i) && (obtenirDisque(hanoi, i, quille) == 0)){
        i--;
    }

    return i;// on retourne la valeur de la hauteur du disque le plus élvevé
}

Bool retraitDisquePossible(THanoi *hanoi, int quille){
    // on verifie si il y a un disque sur la quille
    if(!disquePresent(hanoi, quille)){
        attention("obtenirhauteurDisqueAuSommet (il n'y a aucun disque sur la quille)");
    }

    int i = obtenirHauteurDisqueAuSommet(hanoi, quille);

    if(!hauteurValide(i)){
        attention("obtenirhauteurDisqueAuSommet (hauteur invalide)");
    }

    // Pour savoir si un disque peut être retiré, on regarde si le nivesu de hauteur renvoyé par la fonction "obtenirHauteurDisqueAuSommet" est valide (soit : entre 1 et NB_DISQUES)
    return (hauteurValide(obtenirHauteurDisqueAuSommet(hanoi, quille)));
}

// but : savoir si une quille est pleine
Bool quillePleine(THanoi *hanoi, int quille){
    // si la quille est pleine, c'est parce que le niveau de hauteur renvoyé par la fonction "obtenirHauteurDisqueAuSommet" est égale à NB_DISQUES
    return (obtenirHauteurDisqueAuSommet(hanoi, quille) == NB_DISQUES);
}

int obtenirHauteurPlacement(THanoi *hanoi, int quille){
    // Pour obenir la hauteur où on peut placer un disque, on prends le niveau juste au dessus du disque au sommet de la quille
    int i = obtenirHauteurDisqueAuSommet(hanoi, quille) + 1;

    if(!hauteurValide(i)){
        attention("hauteurPlacementDisquePossible (la hauteur de placment n'est pas valide)");
    }

    return i;
}

// savoir si un disque "a" est plus petit qu'un disque "b"
Bool plusPetit(int a, int b){
    return a<b;
}

// but : verifier qu'on peut deplacer un disque donné à une destinstion donnée
Bool deplacementPossible(THanoi *hanoi, int quilleDepart, int quilleDestination){

    Bool possible = TRUE;

    /**
     * Pour que le deplacement d'un disque d'une quille à l'autre soit possible il faut que :
     * - La quille de depart et la quille de destination ne soit pas la même
     * - La quille de départ ne soit pas vide
     * - La quille de destination ne soit pas pleine
     * - Si le disque de destination n'est pas vide, le le disque qu'on déplace ne soit pas plus grand que le disque sur lequel on va le poser
     */
    if(quilleDepart == quilleDestination){
        attention("deplacmentPossible (quille de depart = quille de destination)");
        possible = FALSE;
    }

    if(!disquePresent(hanoi, quilleDepart)){
        attention("deplacementPossible (la quille de depart est vide)");
        possible = FALSE;
    }

    if(quillePleine(hanoi, quilleDestination)){
        attention("deplacementPossible (la quille de destination est pleine)");
        possible = FALSE;
    }

    if((disquePresent(hanoi, quilleDestination)) && (obtenirDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDestination), quilleDestination) < obtenirDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart))){
        attention("deplacementPossible (le disque ne peut pas etre place sur un disque plus petit)");
        possible = FALSE;
    }

    // Ici, on verifie si le disque qu'on va déplacer est de même taille que le disque sur lequel on va le poser (ce qui est naturellement impossible; dans ce cas on, signale une erreur)
    if(obtenirDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDestination), quilleDestination) == obtenirDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart)){
        attention("deplacementPossible (plusieurs disques de la meme taille)");
        possible = FALSE;
    }

    return possible;
}

// but : deplacer le disque d'une quille à une autre
void deplacerDisque(THanoi *hanoi, int quilleDepart, int quilleDestination){

    if(deplacementPossible(hanoi, quilleDepart, quilleDestination)){
        int aux = obtenirDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart);
        modifierDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart, quilleDepart);
        modifierDisque(hanoi, obtenirHauteurPlacement(hanoi, quilleDestination), quilleDestination, aux);

        modifierDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart, 0); // on supprime le disque qu'on a dupliqué
    }else{
        sautDeLigne(1);
        printf("Deplacement du disque de la quille %d a la quille %d IMPOSSIBLE", quilleDepart, quilleDestination);
        sautDeLigne(2);
    }
}

Bool HanoiResolu(THanoi *hanoi, int quilleDestinationFinale){

    Bool resolu = TRUE;

    int i = 1;

    while(hauteurValide(i) && (resolu == TRUE)){
        if(obtenirDisque(hanoi, i, quilleDestinationFinale) != (NB_DISQUES - i + 1)){
            resolu = FALSE;
        }
        i++;
    }

    return resolu;
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

Bool caractereValide(char c){
    Bool valide = FALSE;

    /**
     * Pour qu'un caractère soit valide, il faut que :
     * - Soit il corresponde à une à un déplacement, soit entre 1 et NB_QUILLES
     * - Soit il correspond à "q", pour quitter la partie
     * - Soit il correspond à "r", pour recommencer la partie
     */

    if( ( (atoi(c) <= NB_QUILLES) && (atoi(c) >= 1) ) && ((c == "q") || (c == "Q") || (c == "r") || (c == "R") ) ){
        valide = TRUE;
    }else{
        printf("Le caractère saisi est incorrect !!!\n");
    }

    return valide;
}

void afficherInstructions(){
    messageTabule(1, "Pour déplacer un disque, saisissez le numero de la quille de depart et le numero de la quille de destination");
    sautDeLigne(1);

    messageTabule(1, "Pour quitter le jeu, saisissez : -1");
    sautDeLigne(1);
    messageTabule(1, "Pour recommencer la partie, saisissez : 0");
    sautDeLigne(1);
    messageTabule(1, "Pour afficher les instructions, saisissez = -2");
    sautDeLigne(1);
}
    

void presentation(){
    printf("Ici, le jeu des tours de Hanoi");
    sautDeLigne(2);
    printf("voici les règles pour jouer :");
    sautDeLigne(2);
    messageTabule(1, "A chaque tour, on va vous demander de saisir les coordonnées (n,m) pour déplacer un disque de la quille n à la quille m");
    sautDeLigne(1);
    afficherInstructions();
}

// but : faire jouer l'utilisateur
void jouer(THanoi *hanoi){
    Bool partieEnCours = TRUE;
    int quilleDepart;
    int quilleDestination;

    // initialisations des quilles
    initTHanoi(hanoi);

    // On afficehe un message de presentation et d'explication pour les règles du jeu
    printf("Bienvenu à ce jeu des Tours de Hanoi!\nVoici les règles pour jouer :\n\n\tSaisissez les numeros des quilles pour deplacer un disque\n\tSaisissez 0 pour recommencer la partie\n\tSaisissez un nombre negatif pour arrêter la partie");

    do{
        afficherHanoi(hanoi);
        quilleDepart = demandeSaisieEntier("Veuillez saisir le numero de la quille de depart : ");
        quilleDestination = demandeSaisieEntier("Veuillez saisir le numero de la quille de destination : ");

        // On affiche dans la console les ereurs éventuelles de l'utilisateur pour qu'il puisse se corriger

        if(quilleDepart > NB_QUILLES){
            printf("Attention! La quille %d n'existe pas", quilleDepart);
        }

        if(quilleDestination > NB_QUILLES){
            printf("Attention! La quille %d n'existe pas", quilleDestination);
        }

        // On traite la saisie

        if((quilleDepart > 0) && (quilleDestination > 0))
        {
            deplacerDisque(hanoi, quilleDepart, quilleDestination);
        }else if((quilleDepart == 0) || (quilleDestination == 0)){
            initTHanoi(hanoi);
            sautDeLigne(1);
            messageTabule(1, "Reinitialisation des quilles");
            sautDeLigne(1);
        }else{
            partieEnCours == FALSE;
        }

    }while(partieEnCours && !HanoiResolu(hanoi, NB_QUILLES) && (quilleDepart >= 0) && (quilleDestination >= 0));

    if(HanoiResolu(hanoi, NB_QUILLES)){
        printf("Bravo! Vous avez gagné la partie\n");
    }else{
        printf("A bientot...\n");
    }
}