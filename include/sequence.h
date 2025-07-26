#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "hanoi.h"
#include "evenements.h"

#define TRUE 1
#define FALSE 0

/**
 * Structure do donnee pour une sequence de deplacement, ses primitives et des fonctions
 */

// on va utiliser cette structure pour constituer un noeud d'une File
struct Deplacement{
    int dep;
    int dest;
    struct Deplacement *Prochain;
};

// CONSTRUCTEURS

// but : allouer de la memoire pour un noeud et l'initialiser
struct Deplacement* nouveauDeplacement(int dep, int dest);

// GETTERS

int obtenirDep(struct Deplacement *noeud);

int obtenirDest(struct Deplacement *noeud);

struct Deplacement* obtenirProchain(struct Deplacement *noeud);

// SETTERS

void modifierDep(struct Deplacement *noeud, int entier);

void modifierDest(struct Deplacement *noeud, int entier);

void modifierProchain(struct Deplacement *noeud, struct Deplacement *prochain);

// METHODES

Bool deplacementVide(struct Deplacement *depl);

// but : savoir si le deplacement passé en paramètre n'est pas suivi d'un autre deplacement
Bool estDernierDeplacement(struct Deplacement *depl);

// but : afficher les elements du deplacement sur la console
void afficherDeplacement(struct Deplacement *depl);

// but : libérer la mémoire pour un seul deplacement (attention au pointeur du deplacement suivant)
void libererDeplacementSeul(struct Deplacement * depl);

// on va utliser cette structure pour constituer une pile de noeuds (noeuds squ'on a contitué auparavant)
struct Sequence{
    struct Deplacement *premierDeplacement;
    int taille;
};

// CONSTRUCTEURS

// but : initialiser une sequence avec un deplacement
struct Sequence* nouvelleSequence(struct Deplacement *depl);

// but : initialiser une sequence vide
struct Sequence* nouvelleSequenceVide();

// GETTERS

struct Deplacement* obtenirPremierDeplacement(struct Sequence *sequence);

int obtenirTaille(struct Sequence *sequence);

// SETTERS

void modifierPremierDeplacement(struct Sequence *sequence, struct Deplacement *noeudDepl);

void modifierTailleSequence(struct Sequence *sequence, int taille);

// METHODES

Bool sequenceVide(struct Sequence *sequence);

struct Deplacement* obtenirDernierDeplacement(struct Sequence *sequence);

// but : incrementer l'attribut "taille" d'une sequence de 1
void incrementertaille(struct Sequence *sequence);

// but : decrementer l'attribut "taille" d'une sequence de 1
void decrementerTaille(struct Sequence *sequence);

// ajoiter un noeud/deplacement a la fin de la pile/sequence
void ajouterDeplacement(struct Sequence *sequence, int dep, int dest);

// but : defiler une sequence : retirer le premier deplacement de la sequence et le retourner
struct Deplacement* defilerSequence(struct Sequence *sequence);

// but : afficher tous les deplacement de la sequence de façon iterative
void afficherSequenceIteratif(struct Sequence *sequence);

// but : afficher tous les deplacement de la sequence de façon récursive
void afficherSequenceRecursif(struct Deplacement *premierDeplacement);

// but : libérer la mémoire d'un déplacement et ceux qui les suivenst
void libererDeplacements(struct Deplacement *depl);

// but : liberer la memoire d'une sequence
void libererSequence(struct Sequence *sequence);

#endif