#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/evenements.h"

void erreur(char *message){
    fprintf(stderr, "Erreur : %s \n", message);
}

void erreurQuitter(char *message){
    fprintf(stderr, "Erreur : %s \n", message);
    exit(1);
}

void sautDeLigne(int n){
    for(int i = 0 ; i < n ; i++){
        printf("\n");
    }
}

void etoile(int n){
    for(int i = 0 ; i < n ; i++){
        printf("*");
    }
}

void messageTabule(int n, char *message){
    for(int i = 0 ; i<n ; i++){
        printf("\t");
    }
    printf("%s\n", message);
}

void annonce(char *message){
    sautDeLigne(1);
    etoile(70);
    sautDeLigne(1);
    printf("\t%s", message);
    sautDeLigne(1);
    etoile(70);
    sautDeLigne(2);
}

int demandeSaisieEntier(char *message){
    int a;
    printf("%s ", message);
    scanf("%d", &a);

    return a;
}
