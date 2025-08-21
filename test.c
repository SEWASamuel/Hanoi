#include <stdio.h>
#include <stdlib.h>
#include "include/bool.h"
#include "include/hanoi.h"
#include "include/evenements.h"
#include <time.h>

void afficherListeTests(){
    printf("voici la liste des tests :");
    sautDeLigne(2);

    messageTabule(1, "1 - Initialisation et affichage");
    sautDeLigne(1);
    messageTabule(1, "2 - Obtention de disque");
    sautDeLigne(1);
    messageTabule(1, "3 - Modification de disque");
    sautDeLigne(1);
    messageTabule(1, "4 - Verification de presence d'un disque");
    sautDeLigne(1);
    messageTabule(1, "5 - Obtentir le disque au sommet d'une quille");
    sautDeLigne(1);
    messageTabule(1, "6 - Savoir si le retrait d'un disque est possible sur une quille donee");
    sautDeLigne(1);
    messageTabule(1, "7 - Savoir si une quille est pleine");
    sautDeLigne(1);
    messageTabule(1, "8 - Obtenir la hauteur où on peut placer un disque sur une quille");
    sautDeLigne(1);
    messageTabule(1, "9 - deplacement d'un disque");
    sautDeLigne(1);
    messageTabule(1, "10 - Verifier si une partie a ete resolue");
    sautDeLigne(1);
    messageTabule(1, "11 - Jouer une partie");
    sautDeLigne(1);
    messageTabule(1, "12 - Faire resoudre le jeu de hanoi par la machine");
    sautDeLigne(1);
    messageTabule(1, "0 - quitter le programme");
    sautDeLigne(1);
}

void choixTest(THanoi *hanoi, Bool arret){
    if(!arret){
        afficherListeTests();

        int choix = demandeSaisieEntier("Veuilez choisir le test à effectuer : ");

        switch (choix)
        {
        case 0:
            printf("Sortie...");
            sautDeLigne(1);
            break;
        case 1:
            testInitialisationAffichage(hanoi);
            break;
        case 2:
            testObtenirDisque(hanoi);
            break;
        case 3:
            testModifierDisque(hanoi);
            break;
        case 4:
            testDisquePresent(hanoi);
            break;
        case 5:
            testHauteurDisqueAuSommet(hanoi);
            break;
        case 6:
            testRetraitDisquePossible(hanoi);
            break;
        case 7:
            testQuillePleine(hanoi);
            break;
        case 8:
            testObtenirHauteurPlacement(hanoi);
            break;
        case 9:
            testDeplacementDisque(hanoi);
            break;
        case 10:
            testVerifHanoiResolu(hanoi);
            break;
        case 11:
            testJouer(hanoi);
            break;
        case 12:
            testResoudreHanoiRecursivement(hanoi);
            break;
        default:
            printf("Saisie invalide");
            sautDeLigne(1);
            break;
        }
        
        choix = demandeGlobale("Continuer? ('o' pour oui, et 'n' pour non) ");
        sautDeLigne(1);
        
        choixTest(hanoi, choix == 0);
    }
}

void testInitialisationAffichage(THanoi *hanoi){
    annonce("TEST : initialisation et affichage d'un jeu de hanoi");

    initTHanoi(hanoi, demandeInitialisation());
    afficherHanoi(hanoi);
    
    sautDeLigne(2);
}

void testObtenirDisque(THanoi *hanoi){
    annonce("TEST : obtenir la taille d'un disque selon des coordonnées");

    initTHanoi(hanoi, demandeInitialisation());
    afficherHanoi(hanoi);

    messageTabule(1, "on fait le test sur les disques de la première quille");
    sautDeLigne(1);
    for(int i=1 ; i<= obtenirNbDisques(hanoi) ; i++){
        printf("la taille du disque de la quille 1 à la hauteur %d est : %d", i, obtenirDisque(hanoi, i, 1));
        sautDeLigne(2);
    }

    messageTabule(1, "on fait le test sur les disques de la deuxieme quille");
    sautDeLigne(1);
    for(int i=1 ; i<= obtenirNbDisques(hanoi) ; i++){
        printf("la taille du disque de la quille 2 à la hauteur %d est : %d", i, obtenirDisque(hanoi, i, 2));
        sautDeLigne(2);
    }

    messageTabule(1, "on fait le test sur les disques de la première quille");
    sautDeLigne(1);
    for(int i=1 ; i<= obtenirNbDisques(hanoi) ; i++){
        printf("la taille du disque de la quille 3 à la hauteur %d est : %d", i, obtenirDisque(hanoi, i, 3));
        sautDeLigne(2);
    }

    sautDeLigne(1);
}

void testModifierDisque(THanoi *hanoi){
    annonce("TEST : modification d'une case");
    
    initTHanoi(hanoi, demandeInitialisation());
    messageTabule(1, "Le jeu de hanoi initialise, on mettre le deuxième disque de la première quille à 0");
    modifierDisque(hanoi, 2, 1, 0);
    afficherHanoi(hanoi);

    messageTabule(1, "Le jeu de hanoi initialise, on mettre le premier disque de la deuxième quille à 5");
    modifierDisque(hanoi, 1, 2, 5);
    afficherHanoi(hanoi);

    sautDeLigne(2);
}

// but : retourner un entier aleatoire entre 0 et l'entier passé en paramètre
int entierAleatoire0(int coef){
    return (rand() % (coef + 1));
}

// but : retourner un entier aleatoire entre 1 et l'entier passé en paramètre
int entierAleatoire1(int coef){
    return ((rand() % coef) + 1);
}

void testDisquePresent(THanoi *hanoi){
    annonce("TEST : savoir si au moins un disque est present sur une quille");

    initTHanoi(hanoi, demandeInitialisation());
    afficherHanoi(hanoi);

    sautDeLigne(1);
    messageTabule(1, "la fonction disquePresent devrait renvoyer vrai pour la premiere quille");
    messageTabule(1, "et faux pour les autres");
    sautDeLigne(2);

    for(int i=1 ; i<=NB_QUILLES ; i++){
        printf("il y a au moins un disque sur la quille %d : ", i); afficherBool(disquePresent(hanoi, i)); sautDeLigne(1);
    }
    sautDeLigne(2);

    messageTabule(1, "On va refaire le test après avoir modifié le jeu de hanoi aleatoirement");
    modifierDisque(hanoi, entierAleatoire1(obtenirNbDisques(hanoi)), entierAleatoire1(NB_QUILLES-1) + 1, entierAleatoire1(obtenirNbDisques(hanoi))); // on mets un entier aleatoire entre 2 et NB_QUILLES pour que la quille 1 ne soit pas modifiée
    afficherHanoi(hanoi);
    for(int k=1 ; k<=NB_QUILLES ; k++){
        printf("il y a au moins un disque sur la quille %d : ", k) ; afficherBool(disquePresent(hanoi, k)); sautDeLigne(1);
    }

    sautDeLigne(1);
}

// but : initaialiser un jeu de hanoi de façon alatoire
void initTHanoiAleatoire(THanoi *hanoi, Bool DejaInitialise){

    if(DejaInitialise){
        initTHanoiVide(hanoi, obtenirNbDisques(hanoi));
    }else{
        initTHanoiVide(hanoi, demandeInitialisation());
    }
    
    for(int i=1 ; i<=NB_QUILLES ; i++){
        for(int j=1 ; j<=entierAleatoire0(obtenirNbDisques(hanoi)) ; j++){
            modifierDisque(hanoi, j, i, rand()%obtenirNbDisques(hanoi)+1);
        }
    }
}

void testHauteurDisqueAuSommet(THanoi *hanoi){
    annonce("TEST : on teste la fonction obteirHauteurDisqueAuSommet");
    initTHanoiAleatoire(hanoi, FALSE);

    afficherHanoi(hanoi);

    for(int i=1 ; i<= NB_QUILLES ; i++){
        printf("La hauteur de la quille %d est de : %d\n", i, obtenirHauteurDisqueAuSommet(hanoi,i));sautDeLigne(1);
    }

    sautDeLigne(2);
}

void testRetraitDisquePossible(THanoi *hanoi){

    annonce("TEST : on va tester la fonction retraitDisque possible");
    initTHanoiAleatoire(hanoi, FALSE);

    afficherHanoi(hanoi);

    for(int i=1 ; i<=NB_QUILLES ; i++){
        printf("On peur retirer un disque de la quille %d : ", i); afficherBool(retraitDisquePossible(hanoi, i)); sautDeLigne(1);
    }

    sautDeLigne(1);
}

void testQuillePleine(THanoi *hanoi){
    annonce("TEST : on va tester la fonction : quillePleine");
    initTHanoiAleatoire(hanoi, FALSE);
    afficherHanoi(hanoi);

    for(int i=1 ; i<=NB_QUILLES ; i++){
        printf("la quille %d est pleine : ", i); afficherBool(quillePleine(hanoi, i)); sautDeLigne(1);
    }

    sautDeLigne(2);
}

void testObtenirHauteurPlacement(THanoi *hanoi){
    annonce("TEST : on va tester la fonction obtenirHauteurPlacement");
    initTHanoiAleatoire(hanoi, FALSE);
    afficherHanoi(hanoi);

    for(int i=1 ; i<=NB_QUILLES ; i++){
        printf("La hauteur de placement pour la quille %d est : %d", i, obtenirHauteurPlacement(hanoi, i)); sautDeLigne(1);
    }

    sautDeLigne(1);
}

// but : executer un deplacement aleatoire
void deplacementAleatoire(THanoi *hanoi){
    int quilleDepart = entierAleatoire1(NB_QUILLES);
    int quilleDestination = entierAleatoire1(NB_QUILLES);
    printf("\ndeplacement aleatoire genere : %d -> %d\n", quilleDepart, quilleDestination);
    deplacerDisque(hanoi, quilleDepart, quilleDestination);
}

void testDeplacementDisque(THanoi *hanoi){
    annonce("TEST : on va tester la fonction deplacementPossible");
    initTHanoiAleatoire(hanoi, FALSE);
    afficherHanoi(hanoi);

    int nbDeplacements = demandeSaisieEntier("Veuillez saisir le nombre de deplacemente aleatoires a effectuer");
    for(int i=0 ; i<nbDeplacements ; i++){
        sautDeLigne(1);
        printf("\tDeplacement %d : \n", i+1);
        sautDeLigne(1);
        deplacementAleatoire(hanoi);
        afficherHanoi(hanoi);
        sautDeLigne(1);
    }
}

// but : initialiser un jeu de hanoi deja resolu
void initTHanoiResolu(THanoi *hanoi, int quilleDestination){
    initTHanoiVide(hanoi, demandeInitialisation());

    for(int i=1 ; i<=obtenirNbDisques(hanoi) ; i++){
        modifierDisque(hanoi, i, quilleDestination, obtenirNbDisques(hanoi)-i+1);
    }
}

void testVerifHanoiResolu(THanoi *hanoi){
    annonce("TEST : on va tester la fonction qui verifie si un hanoi est resolu");

    messageTabule(1, "on va realiser un test sur un jeu de hanoi initialise déjà resolu");
    initTHanoiResolu(hanoi, NB_QUILLES);
    afficherHanoi(hanoi);
    printf("le henoi ci dessus est résolu : "); afficherBool(HanoiResolu(hanoi,NB_QUILLES)); sautDeLigne(2);
    
    messageTabule(1, "on va realiser un test sur un jeu de hanoi initialise aleatoirement");
    initTHanoiAleatoire(hanoi, TRUE);
    afficherHanoi(hanoi);
    printf("le jeu de Hanoi ci dessus est résolu : "); afficherBool(HanoiResolu(hanoi,NB_QUILLES)); sautDeLigne(2);
}

void testJouer(THanoi *hanoi){
    annonce("TEST : on va realiser un test sur la fonction : jouer (entiers)");
    jouer(hanoi);
}

void testResoudreHanoiRecursivement(THanoi *hanoi){
    initTHanoi(hanoi, demandeInitialisation());
    afficherHanoi(hanoi);
    resolutionHanoiRecursif(hanoi, obtenirNbDisques(hanoi), 1, NB_QUILLES);
}

void main(void){
    srand(time(NULL));

    THanoi hanoi;
    THanoi *pHanoi = &hanoi;

    choixTest(pHanoi, FALSE);

    exit(0);
}