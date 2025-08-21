#ifndef HANOI_H
#define HANOI_H
#define NB_MAX_DISQUES 20 // correspnd eu nombre maxinal de disques
#define NB_QUILLES 3 // correspond au nombre de quilles
#include "bool.h"

/**
 * Structure de données des tours de Hanoi, ses prmitivess et des fonctions
 */

// on va utiliser cette structure sn forme de matrice pour représenter le jeu du hanoi (les 3 tiges)
typedef struct Matrice{
    int objet[NB_MAX_DISQUES][NB_QUILLES];
    int nbDisques;
}THanoi;

// but : obtenir le nombre de disques d'une structure de type THanoi
int obtenirNbDisques(THanoi *hanoi);

// but : modifier l'attribut "nbDisques" d'une structure de type THanoi
void modifierNbDisques(THanoi *hanoi, int nb);

// CONVERSIONS

    // MATRICE -> HANOI

int ligneToHauteur(THanoi *hanoi, int ligne);

int colonneToQuille(int colonne);

    // HANOI -> MATRICE 

int hauteurToLigne(THanoi *hanoi, int hauteur);

int quilleToColonne(int quille);

// PRIMITIVES

// but : obtenir la valeur de d'une cese de la matrice
int obtenirDisque(THanoi *hanoi, int hauteur, int quille);

// but : mettre une valeur dans une case de la matrice
void modifierDisque(THanoi *hanoi, int hauteur, int quille, int valeur);

// but : initialiser la matrice représentant seulement avec des cases vides
void initTHanoiVide(THanoi *hanoi, int nbDisques);

// but : initialiser la matrice représentant la tour de hanoi
void initTHanoi(THanoi *hanoi, int nbDisques);

// but : afficher l'objet dans la console
void afficherHanoi(THanoi *hanoi);

// but : savoir si un disque est present sur une quille
Bool disquePresent(THanoi *hanoi, int quille);

// but : savoir si on est dans un niveau de hauteur valide (c-à-d entre 1 et le nombre total de disque, soit la hauteur max de disques sur une quille
Bool hauteurValide(THanoi *hanoi, int n);

// but : obtenir le niveau auquel on peut retirer un disque selon la colonne(quille) passée en paramètre
int obtenirHauteurDisqueAuSommet(THanoi *hanoi, int quille);

// but : savoir si on peut retirer un disque d'une quille
Bool retraitDisquePossible(THanoi *hanoi, int quille);

// but : savoir si une quille est pleine
Bool quillePleine(THanoi *hanoi, int quille);

// but : obtenir le niveau auquel on peut placer un disque selon la colonne(quille) passée en paramètre
int obtenirHauteurPlacement(THanoi *hanoi, int quille);

// savoir si un disque "a" est plus petit qu'un disque "b"
Bool plusPetit(int a, int b);

// but : verifier qu'on peut deplacer un disque donné à une destinstion donnée
Bool deplacementPossible(THanoi *hanoi, int quilleDepart, int quilleDestination);

// but : deplacer le disque d'une quille à une autre
void deplacerDisque(THanoi *hanoi, int quilleDepart, int quilleDestination);

// but : vérifier si le jeu du hanoi est résolu
Bool HanoiResolu(THanoi *hanoi, int quilleDestinationFinale);

// but : resoudre une partie de tours de Hanoi automatiquement
void resolutionHanoiRecursif(THanoi * hanoi, int nbDisques, int quilleDepart, int quilleDestination);//CORRIGER

//but : afficher les instructions du jeu pour l'utilisateur
void afficherInstructions();
    
/** but : presenter le jeu et afficher les instructions dans la console pour l'utilisateu
 * Le caractèra en paramètre servira pour les inctructions, comme pour la fonction : afficherInstructions
 */
void presentation();

// but : faire jouer l'utilisateur (avec une saisie d'entiers)
void jouer(THanoi *hanoi);

#endif