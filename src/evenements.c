#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/evenements.h"
#include "../include/hanoi.h"

void attention(char *message){
    printf("\nAttention : %s \n", message);
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

char demandeSaisieCaractere(char *message){
    char c;
    printf("%s ", message);
    getchar();
    scanf("%c", &c);

    return c;
}

Bool demandeGlobale(char *message){
    char choix;

    do{
        printf("%s ", message);
        getchar();
        scanf("%c", &choix);

        if( (choix == 'o') || (choix =='O')){
            return TRUE;
        }else if( (choix == 'n') || (choix == 'N')){
            return FALSE;
        }else{
            printf("Veuillez Saisir 'o' ou 'n\n");
        }
    }while( ( !(choix == 'o') || (choix == 'O') || (choix == 'n') || (choix == 'N') ) );
}

int demandeInitialisation(){
    int nbDisques;
    do{
        nbDisques = demandeSaisieEntier("Veuillez saisir le nombre de disques pour l'initialisation des quilles : ");
    }while((nbDisques < 1) || (nbDisques > NB_MAX_DISQUES));
    
    return nbDisques;
}