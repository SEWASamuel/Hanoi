#include<stdio.h>
#include "../include/bool.h"

void afficherBool(Bool b){
    if(b == TRUE){
        printf("TRUE\n");
    }else if(b == FALSE){
        printf("FALSE\n");
    }else{
        printf("Booleen invalide\n");
    }
}