#ifndef HANOI_H
#define HANOI_H
#define NB_DISQUES 3 // correspond à la taille des quilles
#define NB_QUILLES 3 // correspond au nombre de quilles
#include "bool.h"
#include "sequence.h"

/**
 * Structure de données des tours de Hanoi, ses prmitivess et des fonctions
 */

// on va utiliser cette structure sn forme de matrice pour représenter le jeu du hanoi (les 3 tiges)
typedef struct Matrix{
    int objet[NB_DISQUES][NB_QUILLES];
}Matrice, THanoi;

// but : mettre une valeur dans une case de la matrice
void modifierCaseHanoi(THanoi *hanoi, int ligne, int colonne, int valeur);

// but : initialiser la matrice représentant la tour de hanoi
void initTHanoi(THanoi *hanoi);

// but : afficher l'objet dans la console
void afficherHanoi(THanoi *hanoi);

// but : savoir si un disque est present sur une quille
Bool disquePresent(THanoi *hanoi, int colonne);

// but : obtenir le niveau auquel on peut retirer un disque selon la colonne(quille) passée en paramètre
int hauteurRetraitQuillePossible(THanoi *hanoi, int colonne);

// but : obtenir le niveau auquel on peut placer un disque selon la colonne(quille) passée en paramètre
int hauteurPlacementQuillePossible(THanoi *hanoi, int colonne);

// savoir si un disque "a" est plus petit qu'un disque "b"
Bool plusPetit(int a, int b);

Bool quilleVide(THanoi *hanoi, int numQuille);

// but : verifier qu'on peut deplacer un disque donné à une destinstion donnée
Bool deplacementPossible(THanoi *hanoi, int quilleDepart, int quilleDestination);

// but : deplacer le disque d'une quille à une autre
void deplacerDisque(THanoi *hanoi, int quilleDepart, int quilleDestination);

// but : vérifier si le jeu du hanoi est résolu
Bool HanoiResolu(THanoi *hanoi);

// but : resoudre un jeu de tours de hanoi avec 3 disques et 3 quilles
void resolutionHanoiManuelle3x3(THanoi *hanoi);

// but : executer un deplacement sur l'objet du hanoi à partir d'une variable de type : struct Deplacement
void executerDeplacement(THanoi *hanoi, struct Deplacement *depl);

// but : executer une sequence de deplacements sur l'objet du hanoi à partir d'une variable de type : struct Sequence
void executerSequence(THanoi *hanoi, struct Sequence *sequence);

// but : resoudre une partie de tours de Hanoi automatiquement
void ResolutionHanoiRecursif(THanoi * hanoi, int nbQuilles, int quilleDepart, int quilleDestination);

// but : renvoyer une sequence permettant la resolution d'un jau de hanoi
//toujours initialiser le paramètre "arret" à : vrai
struct Sequence* ResolutionHanoiRecursifSequence(THanoi * hanoi, struct Sequence *sequence, int nbQuilles, int quilleDepart, int quilleDestination, Bool arret);

// but : faire jouer l'utilisateur
void jouer(THanoi *hanoi);

#endif