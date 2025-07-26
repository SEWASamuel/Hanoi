#include <stdio.h>
#include <stdlib.h>
#include "include/bool.h"
#include "include/sequence.h"
#include "include/hanoi.h"
#include "include/evenements.h"

void testAffichageHanoi(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("TEST : affichage de la tour de hanoi");
    afficherHanoi(hanoi);
}

void testHauteurPlacementQuillePossible(THanoi *hanoi){
    initTHanoi(hanoi);

    afficherHanoi(hanoi);
    annonce("test de : hauteurPlacementQuillePossible");
    printf("voici la hauteur de la quille 1 : %d\n", hauteurPlacementQuillePossible(hanoi,0));
    printf("voici la hauteur de la quille 2 : %d\n", hauteurPlacementQuillePossible(hanoi,1));
    printf("voici la hauteur de la quille 3 : %d\n", hauteurPlacementQuillePossible(hanoi,2));
}

void testDeplacementQuille(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("Test d'un deplacement de la quille 1 a la quille 2 (possible)");
    int dep = demandeSaisieEntier("Veuillez saisir la quille de depart : ")-1;
    int dest = demandeSaisieEntier("Veuillez saisir la quille de destination : ")-1;
    deplacerDisque(hanoi, dep, dest);
    afficherHanoi(hanoi);
}

void testResolutionHanoiManuelle(THanoi *hanoi){
    initTHanoi(hanoi);

    annonce("test de resolution du jeu manuellement");
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
    
    annonce("test : hanoiResolu");
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
    annonce("test d'une partie");
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

    annonce("Test : deplacement");
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

    annonce("Test : creation sequence");

    struct Sequence *seq = nouvelleSequenceVide();

    initSeqPre(seq);

    printf("la taille de la sequence est : %d\n", obtenirTaille(seq));
}

void testAfficherSequenceIteratif(){
    annonce("Test : afficher une sequence iterativement");

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
    annonce("Test : afficher une sequence recursivement");

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
    annonce("Test : defiler une sequence");

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
    annonce("Test : executer une sequence de deplacements");
    sautDeLigne(1);

    initTHanoi(hanoi);

    struct Sequence *seq = nouvelleSequenceVide();
    initSeqPre(seq);

    executerSequence(hanoi, seq);
}


void main(void){

    // main est un test

    THanoi hanoi;
    THanoi *pHanoi = &hanoi;

    testAffichageHanoi(pHanoi);
    testHauteurPlacementQuillePossible(pHanoi);
    testDeplacementQuille(pHanoi);
    testResolutionHanoiManuelle(pHanoi);
    testQuilleVide(pHanoi);
    testHanoiResolu(pHanoi);
    testExecuterTypeDeplacement(pHanoi);
    testCreationSequence(pHanoi);
    testAfficherSequenceIteratif();
    testAffficherSequenceRecursif();
    testDefilerSequence();
    testExecuterSequence(pHanoi);

    exit(0);
}