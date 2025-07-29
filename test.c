#include <stdio.h>
#include <stdlib.h>
#include "include/bool.h"
#include "include/sequence.h"
#include "include/hanoi.h"
#include "include/evenements.h"
#define NB_TESTS 12

void afficherMenu(){
    sautDeLigne(1);
    printf("Voici la liste des tests : ");
    sautDeLigne(2);
    messageTabule(1,"1 - Affichage d'un jeu de tour de hanoi initialisé\n");
    messageTabule(1,"2 - La hauteur de placement sur une quille\n");
    messageTabule(1,"3 - Deplacement d'une quille\n");
    messageTabule(1,"4 - Resolution d'un jeu de tours de hanoi 3x3 avec une sequence de deplacements predefini\n");
    messageTabule(1,"5 - Verification d'une quille vide\n");
    messageTabule(1,"6 - Vérification d'un hanoi resolu\n");
    messageTabule(1,"7 - Execution d'un deplacement extrait d'une donnée de type \"Deplacement\"\n");
    messageTabule(1,"8 - Cration d'une sequence\n");
    messageTabule(1,"9 - Affichage d'une donnee de type \"Sequence\" (iteratif)\n");
    messageTabule(1,"10 - Affichage d'une donnee de type \"Sequence\" (recursif)\n");
    messageTabule(1,"11 - Defilement d'une donnee de type \"Sequence\"\n");
    messageTabule(1,"12 - Execution d'une sequence de deplacement e partir d'une donnee de type \"Deplacement\"\n");
    messageTabule(1,"13 - Creation d'une sequence pour resoudre un jeu de hanoi (recursif)\n");
    messageTabule(1,"14 - Resolution d'un jeu de tours de hanoi 3x3 de façon récursive\n");
    
}

void choixTest(THanoi *hanoi){
    afficherMenu();
    int choix;
    do{
        sautDeLigne(1);
        choix = demandeSaisieEntier("Veuillez saisir le nombre du test que vous voulez effectuer\n(0 pour reafficher la liste | -1 pour quiter)\n\t-> : ");

        switch (choix)
        {
            case -1:
                printf("A plus");
                sautDeLigne(1);
                break;
            case 0:
                afficherMenu();
                break;
            case 1:
                testAffichageHanoi(hanoi);
                break;
            case 2:
                testHauteurPlacementQuillePossible(hanoi);
                break;
            case 3:
                testDeplacementQuille(hanoi);
                break;
            case 4:
                testResolutionHanoiManuelle(hanoi);
                break;
            case 5:
                testQuilleVide(hanoi);
                break;
            case 6:
                testHanoiResolu(hanoi);
                break;
            case 7:
                testExecuterTypeDeplacement(hanoi);
                break;
            case 8:
                testCreationSequence(hanoi);
                break;
            case 9:
                testAfficherSequenceIteratif();
                break;
            case 10:
                testAffficherSequenceRecursif();
                break;
            case 11:
                testDefilerSequence();
                break;
            case 12:
                testExecuterSequence(hanoi);
                break;
            case 13:
                testCreerSequenceResolutionHanoi(hanoi);
                break;
            case 14:
                testResoudreHanoiRecursif(hanoi);
                break;
            default:
                printf("nombre invalide ! Veuillez resaiisir un nombre valide");
                sautDeLigne(2);
                break;
        }
    }while(choix != -1);
}

void testAffichageHanoi(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("TEST : affichage de la tour de hanoi");
    afficherHanoi(hanoi);
}

void testHauteurPlacementQuillePossible(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("TEST : hauteurPlacementQuillePossible");
    afficherHanoi(hanoi);
    printf("voici la hauteur de la quille 1 : %d\n", hauteurPlacementQuillePossible(hanoi,0));
    printf("voici la hauteur de la quille 2 : %d\n", hauteurPlacementQuillePossible(hanoi,1));
    printf("voici la hauteur de la quille 3 : %d\n", hauteurPlacementQuillePossible(hanoi,2));
}

void testDeplacementQuille(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("TEST d'un deplacement saisi par l'utilisateur");
    afficherHanoi(hanoi);
    int dep = demandeSaisieEntier("Veuillez saisir la quille de depart : ")-1;
    int dest = demandeSaisieEntier("Veuillez saisir la quille de destination : ")-1;
    deplacerDisque(hanoi, dep, dest);
    afficherHanoi(hanoi);
}

void testResolutionHanoiManuelle(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("TEST de resolution du jeu manuellement");
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

// Test de la fonction : quilleVide
void testQuilleVide(THanoi *hanoi){
    annonce("TEST : testQuilleVide");
    initTHanoi(hanoi);

    afficherHanoi(hanoi);
    printf("La quille 1 est vide :");
    afficherBool(quilleVide(hanoi, 0));
    printf("La quille 2 est vide :");
    afficherBool(quilleVide(hanoi, 1));
    printf("La quille 3 est vide :");
    afficherBool(quilleVide(hanoi, 2));
}

// Test de la fonction : hanoiResolu
void testHanoiResolu(THanoi *hanoi){
    initTHanoi(hanoi);
    
    annonce("TEST : hanoiResolu");
    afficherHanoi(hanoi);

    if(HanoiResolu(hanoi)){
        printf("Hanoi valde!\n");
    }else{
        printf("Hanoi NON valide!\n");
    }

    resolutionHanoiManuelle3x3(hanoi);

    if(HanoiResolu(hanoi)){
        printf("Hanoi valde!\n");
    }else{
        printf("Hanoi NON valide!\n");
    }
}

// Test d'une partie
void testJouer(THanoi *hanoi){
    annonce("TEST d'une partie");
    jouer(hanoi);
}

// but : initialiser une sequence predefinie
void initSeqPre(struct Sequence *seq){
    ajouterDeplacement(seq,1,3);
    // afficherDeplacement(obtenirDernierDeplacement(seq));
    ajouterDeplacement(seq,1,2);
    // afficherDeplacement(obtenirDernierDeplacement(seq));
    ajouterDeplacement(seq,3,2);
    // afficherDeplacement(obtenirDernierDeplacement(seq));
    ajouterDeplacement(seq,1,3);
    // afficherDeplacement(obtenirDernierDeplacement(seq));
    ajouterDeplacement(seq,2,1);
    // afficherDeplacement(obtenirDernierDeplacement(seq));
    ajouterDeplacement(seq,2,3);
    // afficherDeplacement(obtenirDernierDeplacement(seq));
    ajouterDeplacement(seq,1,3);
    // afficherDeplacement(obtenirDernierDeplacement(seq));
}

// test de la creation de deplacements
void testExecuterTypeDeplacement(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("TEST : deplacement");
    struct Deplacement *depl = nouveauDeplacement(1,3);
    afficherDeplacement(depl);
    struct Deplacement *dep2 = nouveauDeplacement(1,2);
    afficherDeplacement(dep2);
    struct Deplacement *dep3 = nouveauDeplacement(3,2);
    afficherDeplacement(dep3);
    struct Deplacement *dep4 = nouveauDeplacement(1,3);
    afficherDeplacement(dep4);
    struct Deplacement *dep5 = nouveauDeplacement(2,1);
    afficherDeplacement(dep5);
    struct Deplacement *dep6 = nouveauDeplacement(2,3);
    afficherDeplacement(dep6);
    struct Deplacement *dep7 = nouveauDeplacement(1,3);
    afficherDeplacement(dep7);

    afficherHanoi(hanoi);
    executerDeplacement(hanoi, depl);
    executerDeplacement(hanoi, dep2);
    executerDeplacement(hanoi, dep3);
    executerDeplacement(hanoi, dep4);
    executerDeplacement(hanoi, dep5);
    executerDeplacement(hanoi, dep6);
    executerDeplacement(hanoi, dep7);
    struct Deplacement *deplFaux = nouveauDeplacement(1,4); // censé signaler une erreur dans la console
}

// test : création d'une sequence sous forme de pile de deplacements
void testCreationSequence(){

    annonce("TEST : creation sequence");

    struct Sequence *seq = nouvelleSequenceVide();

    initSeqPre(seq);

    printf("la taille de la sequence est : %d\n", obtenirTaille(seq));
}

void testAfficherSequenceIteratif(){
    annonce("TEST : afficher une sequence iterativement");

    messageTabule(1, "Creation d'une sequence vide");
    sautDeLigne(1);

    struct Sequence *seq = nouvelleSequenceVide();
    messageTabule(1, "test sur une sequence vide");
    sautDeLigne(1);
    afficherSequenceIteratif(seq);
    sautDeLigne(2);

    messageTabule(1, "ajout de deplacements dans la sequence");
    initSeqPre(seq);
    sautDeLigne(2);

    messageTabule(1, "affichage de la sequence");
    sautDeLigne(1);
    afficherSequenceIteratif(seq);
}

void testAffficherSequenceRecursif(){
    annonce("TEST : afficher une sequence recursivement");

    messageTabule(1, "test sur une sequence vide");
    sautDeLigne(1);
    struct Sequence *seq = nouvelleSequenceVide();
    afficherSequenceRecursif(obtenirPremierDeplacement(seq));
    sautDeLigne(2);

    messageTabule(1, "test sur une sequence remplie");
    initSeqPre(seq);
    sautDeLigne(2);
}

void testDefilerSequence(){
    annonce("TEST : defiler une sequence");

    struct Sequence *seq = nouvelleSequenceVide();
    initSeqPre(seq);

    messageTabule(1, "Voici la sequence initialisee\n");
    afficherSequenceIteratif(seq);
    sautDeLigne(2);

    messageTabule(1, "on depile la sequence\n");
    struct Deplacement *depl = defilerSequence(seq);
    printf("voici le deplacement qu'on a defile : "); afficherDeplacement(depl);
    sautDeLigne(1);
    afficherSequenceIteratif(seq);
}

void testExecuterSequence(THanoi *hanoi){
    annonce("TEST : executer une sequence de deplacements");
    sautDeLigne(1);

    initTHanoi(hanoi);

    struct Sequence *seq = nouvelleSequenceVide();
    initSeqPre(seq);

    executerSequence(hanoi, seq);
}

void testCreerSequenceResolutionHanoi(THanoi *hanoi){
    annonce("TEST : creer une sequence permettant de rsoudre un jeu de hanoi 3x3");
    sautDeLigne(1);

    initTHanoi(hanoi);

    afficherSequenceIteratif(ResolutionHanoiRecursifSequence(hanoi, nouvelleSequenceVide(), 3, 1, 3, TRUE));
}

void testResoudreHanoiRecursif(THanoi *hanoi){
    annonce("TEST : resoudre un jeu de hanoi recursivement");
    sautDeLigne(1);

    messageTabule(1, "On fera passer les disques de la quille 1 à la quille 3");

    initTHanoi(hanoi);

    ResolutionHanoiRecursif(hanoi,3,1,3);
}


void main(void){

    // main est un test

    THanoi hanoi;
    THanoi *pHanoi = &hanoi;

    // testAffichageHanoi(pHanoi);
    // testHauteurPlacementQuillePossible(pHanoi);
    // testDeplacementQuille(pHanoi);
    // testResolutionHanoiManuelle(pHanoi);
    // testQuilleVide(pHanoi);
    // testHanoiResolu(pHanoi);
    // testExecuterTypeDeplacement(pHanoi);
    // testCreationSequence(pHanoi);
    // testAfficherSequenceIteratif();
    // testAffficherSequenceRecursif();
    // testDefilerSequence();
    // testExecuterSequence(pHanoi);
    // testResoudreHanoiRecursif(pHanoi);
    // testCreerSequenceResolutionHanoi(pHanoi);

    choixTest(pHanoi);

    exit(0);
}