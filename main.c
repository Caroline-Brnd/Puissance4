#include "puissance4.h"

int main(){
    char* j1 = malloc(20*sizeof(char));
    char* j2 = malloc(20*sizeof(char));
    printf("\n         ** Bienvenue dans le jeu Puissance4 **");
    int choix;
    printf("\n\n\n  Appuyer sur : \n 1- Nouvelle Partie (2 Joueurs) \n 2- Scores précedents \n 3- Quitter \n");
    scanf("%d", &choix);
    switch(choix){
        case 1:{
            jouer();
            break;
        }
        case 2:{
            printf("La liste des gagnants de ce Puissance 4 : \n");
            FILE* fresult=NULL;
            fresult = fopen("score.txt","r");
            int carac;  
            if (fresult != NULL){
                carac = fgetc(fresult);
                while (carac != EOF){
                    printf("%c", carac); 
                    carac = fgetc(fresult);
                }
            }
            break;
        }
        case 3:{
            printf("\n         ** Au revoir, merci d'avoir jouer **\n");
            exit(EXIT_SUCCESS);
            break;
        }
        default :{
            printf("Veuillez entrer les chiffres 1, 2, 3, ou 4 s'il vous plait");
            break;
        }
    }
    return 0;
}