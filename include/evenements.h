#ifndef EVENEMENTS_H
#define EVENEMENTS_H

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

// but : faie saisir un entier à l'utilisateur
int demandeSaisieEntier(char *message);

#endif
