#include <stdio.h>
#include <stdlib.h>

#include "../include/sequence.h"
#include "../include/evenements.h"
#include "../include/bool.h"
#include "../include/hanoi.h"

// CONSTRUCTEURS

struct Deplacement* nouveauDeplacement(int dep, int dest){
    // declaration du deplacement
    struct Deplacement *depl = (struct Deplacement *)malloc(sizeof(struct Deplacement));

    // ici, on verifie si l'allocation de la memoire a bien été effectuée
    if(depl == NULL){
        erreurQuitter("nouveauDeplacament (allocation de memoire echouee)");
    }

    // on verifie que les coordonnees du deplacement soient justes
    if(dep < 1 || dest < 1 || dep > NB_QUILLES ||dest > NB_QUILLES){
        erreurQuitter("NouveauDeplacement (numero de depart ou de destination incorrect)");
    }

    // ici, on initialise les valeurs du deplacement et le pointeur vers le prochain noeud
    depl->dep = dep;
    depl->dest = dest;
    depl->Prochain = NULL;
    return depl;
}

// GETTERS

int obtenirDep(struct Deplacement *noeud){
    return noeud->dep;
}

int obtenirDest(struct Deplacement *noeud){
    return noeud->dest;
}

struct Deplacement* obtenirProchain(struct Deplacement *noeud){
    return noeud->Prochain;
}

// SETTERS

void modifierDep(struct Deplacement *noeud, int entier){
    noeud->dep = entier;
}

void modifierDest(struct Deplacement *noeud, int entier){
    noeud->dest = entier;
}

void modifierProchain(struct Deplacement *noeud, struct Deplacement *prochain){
    noeud->Prochain = prochain;
}

// METHODES

Bool deplacementVide(struct Deplacement *depl){
    return (depl == NULL);
}

Bool estDernierDeplacement(struct Deplacement *depl){
    return deplacementVide(obtenirProchain(depl));
}

void afficherDeplacement(struct Deplacement *depl){
    if(deplacementVide(depl)){
        //erreurQuitter("afficherDeplacement (deplacement vide)"); 
        erreur("afficherDeplacement (deplacement vide)"); // pas besoin de forcément quitter le programme
    }
    printf("%d -> %d\n", obtenirDep(depl), obtenirDest(depl));
}

void libererDeplacementSeul(struct Deplacement * depl){
    free(depl);
}

// CONSTRUCTEURS

struct Sequence* nouvelleSequence(struct Deplacement *depl){
    // alloction de memoire
    struct Sequence *sequence = (struct Sequence*)malloc(sizeof(struct Sequence));
    // ici, on vérifie si l'allocation de memoire a bien été effectuée
    if(sequence == NULL){
        erreurQuitter("nouvelleSequence");
    }

    // initialisation du premier noeud/deplacement et de la taille
    sequence->premierDeplacement = depl;
    sequence->taille = 1;
}

struct Sequence* nouvelleSequenceVide(){
    // allocation de memoire
    struct Sequence *sequence = (struct Sequence *) malloc(sizeof(struct Sequence));
    // ici, on vérifie si l'allocation de mémoire a bien été effectuée
    if(sequence == NULL){
        erreurQuitter("NouvelleSequenceVide");
    }

    // initialisation du premier noeud/deplacement et de la taille
    sequence->premierDeplacement = NULL;
    sequence->taille = 0;
}

// GETTERS

struct Deplacement* obtenirPremierDeplacement(struct Sequence *sequence){
    return sequence->premierDeplacement;
}

int obtenirTaille(struct Sequence *sequence){
    return sequence->taille;
}

// SETTERS

void modifierPremierDeplacement(struct Sequence *sequence, struct Deplacement *noeudDepl){
    sequence->premierDeplacement = noeudDepl;
}

void modifierTailleSequence(struct Sequence *sequence, int taille){
    sequence->taille = taille;
}

// METHODES

Bool sequenceVide(struct Sequence *sequence){
    /**
     * ici, on retourne vrai on est sur au moins un de ces 3 cas, soit :
     * - Le pointeur sur la sequence = NULL
     * - le premier deplacemenr de la sequence = NULL
     * - la taille de la sequence = 0
     */
    if((sequence == NULL) || (deplacementVide(obtenirPremierDeplacement(sequence))) || (obtenirTaille(sequence) == 0)){
        // // affichages pour les test due la console
        // if(sequence == NULL){
        //     printf("le pointeur sur la sequence est nulle\n");
        // }
        // if(deplacementVide(obtenirPremierDeplacement(sequence))){
        //     printf("le premier deplacement est vide\n");
        // }
        // if(obtenirTaille(sequence) == 0){
        //     printf("la taille de la sequence est = 0\n");
        // }

        return TRUE;
    }else{
        return FALSE;
    }
}

struct Deplacement* obtenirDernierDeplacement(struct Sequence *sequence){
    if(sequenceVide(sequence)){
        return NULL;
    }else{
        struct Deplacement *i = obtenirPremierDeplacement(sequence);
        while(! deplacementVide(obtenirProchain(i))){
            i = obtenirProchain(i);
        }
        return i;
    }

}

void incrementertaille(struct Sequence *sequence){
    sequence->taille += 1;
}

void decrementerTaille(struct Sequence *sequence){
    sequence->taille -= 1;
}

void ajouterDeplacement(struct Sequence *sequence, int dep, int dest){
    if(sequenceVide(sequence)){
        modifierPremierDeplacement(sequence, nouveauDeplacement(dep, dest));
    }else{
        modifierProchain(obtenirDernierDeplacement(sequence), nouveauDeplacement(dep, dest));
    }

    incrementertaille(sequence);
}

struct Deplacement* defilerSequence(struct Sequence *sequence){
    // ici, on verifie si la sequence n'est pas vide
    if(sequenceVide(sequence)){
        erreurQuitter("defilerSequence(sequence vide)");
        return NULL; //TODO : pour le warning
    }

    // On stocke le premier deplacment pour le retourner plus tard
    struct Deplacement *premier = obtenirPremierDeplacement(sequence);
    // on met le deuxième deplacement en première place
    modifierPremierDeplacement(sequence, obtenirProchain(obtenirPremierDeplacement(sequence)));
    // on peut delier le deplacment qu'on a stocké(le premier) à celui qui le suit pour :
    // - ne plus avoir acces au deplacement suivant après avoir été défilé
    // - eviter de libérer par accident les deplacements de la sequence lorsq'on libère le premier deplacement
    modifierProchain(premier, NULL);
    decrementerTaille(sequence);
    return premier;
}

void afficherSequenceIteratif(struct Sequence *sequence){
    // ici, on verifie si la sequence est vide
    if(sequenceVide(sequence)){
        erreur("afficherSequenceIteratif (sequence vide)");
    }

    //ici : on affiche la taille de la sequence
    printf("sequence de taille : %d", obtenirTaille(sequence));
    sautDeLigne(2);
    int compteur = 1;
    struct Deplacement *index = obtenirPremierDeplacement(sequence);
    while(!deplacementVide(index)){
        printf("[deplacement %d] : ", compteur);
        afficherDeplacement(index);
        index = obtenirProchain(index);
        compteur++;
    }
}

void afficherSequenceRecursif(struct Deplacement *premierDeplacement){
    // ici, on verifie si le deplacement n'est pas vide
    if(deplacementVide(premierDeplacement)){
        erreur("afficherSequenceRecursif (premierDeplacement vide)");
    }

    /**
     * les cas d'arrêt :
     * - aucun deplacement ne suit le deplacmeent actuel
     */

    if(!deplacementVide(premierDeplacement)){
        printf("[Deplacement] : ");
        afficherDeplacement(premierDeplacement);
        afficherSequenceRecursif(obtenirProchain(premierDeplacement));
    }
}

void libererDeplacements(struct Deplacement *depl){
    if(!deplacementVide(obtenirProchain(depl))){
        libererDeplacements(obtenirProchain(depl));
    }
    libererDeplacementSeul(depl);
}

void libererSequence(struct Sequence *sequence){
    // ici, on libere tous les deplacements de la sequence
    libererDeplacements(obtenirPremierDeplacement(sequence));;

    // ici, on libere la sequence
    free(sequence);
}