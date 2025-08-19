#ifndef EVENEMENTS_H
#define EVENEMENTS_H
#include "bool.h"

// but : afficher un message d'attention personnalisé dans la console
void attention(char *message);

// but : en plus d'afficher le message d'erreur dans la console, on quitte le programme
void erreurQuitter(char *message);

// but : faire des sauts de ligne dans la console n fois
void sautDeLigne(int n);

// but : afficher une etoile dans la console n fois 
void etoile(int n);

// but : affichage d'un message précéde d'un nombre n de tabulations
void messageTabule(int n, char *message);

// but : mettre un peu de graphisme sur des titres pour afficher les dans la console
void annonce(char *message);

// but : faire saisir un entier à l'utilisateur
int demandeSaisieEntier(char *message);

// but : faire saisir un caractère à l"utilisateur
char demandeSaisieCaractere(char *message);

// but : faire une demande globale à l'utilisateur (lui faire choisir entre oui et non)
Bool demandeGlobale(char *message);

// but : demander à l'utilisateur de saisir le nombre de disques pour initialiser un jeu de Hanoi
int demandeInitialisation();

#endif
