#include<stdio.h>
#include "../include/hanoi.h"
#include "../include/evenements.h"

int obtenirNbDisques(THanoi *hanoi){
    return hanoi->nbDisques;
}

void modifierNbDisques(THanoi *hanoi, int nb){
    hanoi->nbDisques = nb;
}

// CONVERSIONS

    // MATRICE -> HANOI

int ligneToHauteur(THanoi *hanoi, int ligne){
    return (obtenirNbDisques(hanoi) - ligne); 
}

int colonneToQuille(int colonne){
    return (colonne + 1);
}

    // HANOI -> MATRICE

int hauteurToLigne(THanoi *hanoi, int hauteur){
    return (obtenirNbDisques(hanoi) - hauteur);
}

int quilleToColonne(int quille){
    return (quille-1);
}

int obtenirDisque(THanoi *hanoi, int hauteur, int quille){
    return hanoi->objet[hauteurToLigne(hanoi,hauteur)][quilleToColonne(quille)];
}

void modifierDisque(THanoi *hanoi, int hauteur, int quille, int valeur){
    hanoi->objet[hauteurToLigne(hanoi, hauteur)][quilleToColonne(quille)] = valeur;
}

void initTHanoiVide(THanoi *hanoi, int nbDisques){
    modifierNbDisques(hanoi, nbDisques);
    // ici , on parcourt toutes les cases de du objet de hanoi pour les mettre à vide (0)
    for(int i=1 ; i<=obtenirNbDisques(hanoi) ; i++){
        for(int j=1 ; j<=NB_QUILLES ; j++){
            modifierDisque(hanoi, i, j, 0);
        }
    }
}

void initTHanoi(THanoi *hanoi, int nbDisques){
    modifierNbDisques(hanoi, nbDisques);
    initTHanoiVide(hanoi, nbDisques);

    // Ici, on parcourt tous les niveaud de la première quille de sorte à placer les disques à leur position initiale
    for(int k=1 ; k<=nbDisques ; k++){
        modifierDisque(hanoi, k, 1, nbDisques-k+1);
    }
}

void afficherHanoi(THanoi *hanoi){
    printf("\nTour de Hanoi :\n\n");

    /**
     * ici, on parcour toute la matrice pour afficher le jeu du hanoi
     * Où il y a des disques, on affiche lavaleur du disque
     * Et où il n'u a pas de disque, on affiche une barre (pour former une quille)
     */
    for(int i=1 ; i<=obtenirNbDisques(hanoi) ; i++){
        for(int k=1 ; k<=NB_QUILLES ; k++){
            if(obtenirDisque(hanoi, obtenirNbDisques(hanoi)-i+1, k) == 0){
                printf("| ");
            }else{
                printf("%d ", obtenirDisque(hanoi, obtenirNbDisques(hanoi)-i+1, k));
            }
        }
        sautDeLigne(1);
    }
    sautDeLigne(1);
}

Bool disquePresent(THanoi *hanoi, int quille){
    Bool present = FALSE;
    int i = obtenirNbDisques(hanoi);

    while(hauteurValide(hanoi, i) && present == FALSE){
        if(obtenirDisque(hanoi, i, quille) != 0){
            present = TRUE;
        }
        i--;
    }
    return present;
}

Bool hauteurValide(THanoi *hanoi, int niveauHauteur){
    return ((niveauHauteur >= 1) && (niveauHauteur <= obtenirNbDisques(hanoi)));
}

int obtenirHauteurDisqueAuSommet(THanoi *hanoi, int quille){
    /**
     * on commence à parcourir les cases à partir du haut (donc on initialise la compteur i à NB_DISQUES)
     * et tant qu'on ne trouve pas de disque, on continue à descendre
     */
    int i = obtenirNbDisques(hanoi);

    while(hauteurValide(hanoi, i) && (obtenirDisque(hanoi, i, quille) == 0)){
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

    if(!hauteurValide(hanoi, i)){
        attention("obtenirhauteurDisqueAuSommet (hauteur invalide)");
    }

    // Pour savoir si un disque peut être retiré, on regarde si le nivesu de hauteur renvoyé par la fonction "obtenirHauteurDisqueAuSommet" est valide (soit : entre 1 et NB_DISQUES)
    return (hauteurValide(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quille)));
}

Bool quillePleine(THanoi *hanoi, int quille){
    // si la quille est pleine, c'est parce que le niveau de hauteur renvoyé par la fonction "obtenirHauteurDisqueAuSommet" est égale à NB_DISQUES
    return (obtenirHauteurDisqueAuSommet(hanoi, quille) == obtenirNbDisques(hanoi));
}

int obtenirHauteurPlacement(THanoi *hanoi, int quille){
    // Pour obenir la hauteur où on peut placer un disque, on prends le niveau juste au dessus du disque au sommet de la quille
    int i = obtenirHauteurDisqueAuSommet(hanoi, quille) + 1;

    if(!hauteurValide(hanoi, i)){
        attention("hauteurPlacementDisquePossible (la hauteur de placment n'est pas valide)");
    }

    return i;
}

Bool plusPetit(int a, int b){
    return a<b;
}

Bool deplacementPossible(THanoi *hanoi, int quilleDepart, int quilleDestination){

    Bool possible = TRUE;

    /**
     * Pour que le deplacement d'un disque d'une quille à l'autre soit possible il faut que :
     * - La quille de depart et la quille de destination ne dépassent pas les bornes (1 et NB_QUILLES)
     * - La quille de depart et la quille de destination ne soit pas la même
     * - La quille de départ ne soit pas vide
     * - La quille de destination ne soit pas pleine
     * - Si le disque de destination n'est pas vide, le le disque qu'on déplace ne soit pas plus grand que le disque sur lequel on va le poser
     */
    if( (quilleDepart < 1) || (quilleDepart > NB_QUILLES) ){
        attention("Quille de depart invalide");
        possible = FALSE;
    }

    if( (quilleDestination < 1) || (quilleDestination > NB_QUILLES) ){
        attention("Quille de destination invalide");
        possible = FALSE;
    }

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

void deplacerDisque(THanoi *hanoi, int quilleDepart, int quilleDestination){

    if(deplacementPossible(hanoi, quilleDepart, quilleDestination)){
        int aux = obtenirDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart);
        modifierDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart, quilleDepart);
        modifierDisque(hanoi, obtenirHauteurPlacement(hanoi, quilleDestination), quilleDestination, aux);

        // on supprime le disque qu'on a dupliqué
        modifierDisque(hanoi, obtenirHauteurDisqueAuSommet(hanoi, quilleDepart), quilleDepart, 0);
    }else{
        sautDeLigne(1);
        printf("Deplacement du disque de la quille %d a la quille %d IMPOSSIBLE", quilleDepart, quilleDestination);
        sautDeLigne(2);
    }
}

Bool HanoiResolu(THanoi *hanoi, int quilleDestinationFinale){

    Bool resolu = TRUE;

    int i = 1;

    while(hauteurValide(hanoi, i) && (resolu == TRUE)){
        if(obtenirDisque(hanoi, i, quilleDestinationFinale) != (obtenirNbDisques(hanoi) - i + 1)){
            resolu = FALSE;
        }
        i++;
    }

    return resolu;
}

void resolutionHanoiRecursif(THanoi *hanoi, int nbDisques, int quilleDepart, int quilleDestination){
    if(nbDisques == 1){
        deplacerDisque(hanoi, quilleDepart, quilleDestination);
        printf("\nDeplacement : %d -> %d\n", quilleDepart, quilleDestination);
        afficherHanoi(hanoi);
    }else{
        int quilleRestante = 6 - (quilleDepart + quilleDestination);
        
        resolutionHanoiRecursif(hanoi, nbDisques-1, quilleDepart, quilleRestante);

        deplacerDisque(hanoi, quilleDepart, quilleDestination); // TODO : corriger la fooction deplacerDisque our qu'on ait pas de soicis d'index (0=1)
        printf("\nDeplacement : %d -> %d\n", quilleDepart, quilleDestination);
        afficherHanoi(hanoi);
        resolutionHanoiRecursif(hanoi, nbDisques-1, quilleRestante, quilleDestination);
    }
}

void afficherInstructions(){
    messageTabule(1, "Pour déplacer un disque, saisissez le numero de la quille de depart et le numero de la quille de destination");
    sautDeLigne(1);

    messageTabule(1, "Pour quitter le jeu, saisissez : -1");
    sautDeLigne(1);
    messageTabule(1, "Pour recommencer la partie, saisissez : 0");
    sautDeLigne(1);
    messageTabule(1, "Pour afficher les instructions, saisissez : -2");
    sautDeLigne(1);
    messageTabule(1, "Pour afficher la correction, saisissez : -3");
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

void jouer(THanoi *hanoi){
    Bool partieEnCours = TRUE;
    int quilleDepart;
    int quilleDestination;

    // On afficehe un message de presentation et d'explication pour les règles du jeu
    // printf("Bienvenu à ce jeu des Tours de Hanoi!\nVoici les règles pour jouer :\n\n\t- Saisissez les numeros des quilles pour deplacer un disque\n\t- Saisissez 0 pour recommencer la partie\n\t- Saisissez un nombre negatif pour arrêter la partie\n\n");
    presentation();


    // initialisations des quilles
    initTHanoi(hanoi, demandeInitialisation());

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
        }else if((quilleDepart == 0) && (quilleDestination == 0)){
            if(demandeGlobale("Voulez vous jouer avec le même nombre de disques? ('o' pour oui et 'n' pour non) ")){
                sautDeLigne(1);
                initTHanoi(hanoi, obtenirNbDisques(hanoi));
            }else{
                initTHanoi(hanoi,demandeInitialisation());   
            }
            sautDeLigne(1);
            messageTabule(1, "Reinitialisation des quilles");
            sautDeLigne(1);
        }else if((quilleDepart == -1) && (quilleDestination == -1)){
            partieEnCours = FALSE;
        }else if((quilleDepart == -2) && (quilleDestination == -2)){
            sautDeLigne(1);
            afficherInstructions();
        }else if((quilleDepart == -3) && (quilleDestination == -3)){
            initTHanoi(hanoi, obtenirNbDisques(hanoi));
            resolutionHanoiRecursif(hanoi, obtenirNbDisques(hanoi), 1, NB_QUILLES);
        }else{
            sautDeLigne(1);
            messageTabule(1, "Saisie invalide !");
            sautDeLigne(1);
        }

    }while(partieEnCours && !HanoiResolu(hanoi, NB_QUILLES));

    if(HanoiResolu(hanoi, NB_QUILLES) && !((quilleDestination == -3) && (quilleDestination == -3))){
        afficherHanoi(hanoi);
        printf("Bravo! Vous avez gagné la partie\n");
    }else{
        printf("A bientot...\n");
    }
}