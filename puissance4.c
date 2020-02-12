#include "puissance4.h"

//Demande des noms des Joueurs
void nomdejoueur(char* j1, char* j2){
    printf("Joueur 1, veuillez entrer votre nom: \n");
    scanf("%s", j1);
    printf("\nJoueur 2, veuillez entrer votre nom: \n");
    scanf("%s", j2);
    printf("\nLe joueur 1 : %s a les O et le joueur 2 : %s a les X \n\n", j1, j2);
}


//Affichage de la grille
int** creation_degrille(){
    int i;
    int** grille=malloc(7*sizeof(int*)); //7 car sinon erreur segmentation (6 + 1)
    for(i = 1; i < 8; i++){
        grille[i]=malloc(8*sizeof(int)); //8 car sinon erreur segmentation (7 + 1) 
    }
    return grille;
}

int** initialiser(int** grille){
    int i, j;
    for(i = 1; i < 7; i++){
        for(j = 1; j < 8; j++){
            grille[i][j] = 0;
        }
    }
    return grille;
}

void affichage_grille(int** grille){
  int i,j;
  printf("\n");
  for(i = 1; i < 7; i++){
    for(j = 1; j < 8; j++){
      if(j == 7){
        if(grille[i][j] == 1){
          printf("|O|\n");
        }
        else if(grille[i][j] == 2){
          printf("|X|\n");
        }
        else{
          printf("|_|\n"); 
        }       
      }
      else{
        if(grille[i][j] == 1){
          printf("|O");
        }
        else if(grille[i][j] == 2){
          printf("|X");
        }
        else if(grille[i][j] == 0){
          printf("|_");
        }
      }
    }
  }
  printf(" 1 2 3 4 5 6 7 \n");
  printf("________________ \n");
}


//Sauvegarde des scores
void sauv(char* joueur){
    FILE* fresult=NULL;
    fresult = fopen("score.txt","a");
    fprintf(fresult,"%s\n", joueur);
}


//Remplissage de la grille
void remplir(int tour, char* j1, char* j2, int** grille){
    int colonne;
    if((tour & 1) == 1){
        printf(" \n %s, veuillez entrer le numéro de la colonne (entre 1 et 7) dans laquelle vous voulez jouer : ", j1);
        scanf("%d", &colonne);

        while(grille[1][colonne] == 1 || grille[1][colonne] == 2){
            printf("ERREUR : La colonne que vous demandez est pleine, veuillez entrer une autre colonne :");
            scanf("%d", &colonne);
        }

        int i = 6;
        while((grille[i][colonne] == 1 ||  grille[i][colonne] == 2) && i>1){
            i--;
        }
        grille[i][colonne] = 1;
    }
    else{
        printf(" \n %s, veuillez entrer le numero de la colonne (entre 1 et 7) dans laquelle vous voulez jouer : ", j2);
        scanf("%d", &colonne);

        while(grille[1][colonne] == 1 ||  grille[1][colonne] == 2){
          printf("ERREUR : La colonne que vous demandez est pleine, veuillez entrer une autre colonne : \n");
          scanf("%d", &colonne);
        }

        int i = 6;
        while((grille[i][colonne] == 1  ||  grille[i][colonne] == 2) && i>1){
            i--;
        }
        
        grille[i][colonne] = 2;
        printf("\n");
    }
}
 

//Pour jouer
void jouer(){
    int choix_fin;
    char* j1 = malloc(20*sizeof(char));
    char* j2 = malloc(20*sizeof(char));
    int tour = 1;
    int** grille = creation_degrille();
    affichage_grille(grille);
    int plein = 0;
    int gagne = 0;
    nomdejoueur(j1,j2);
    initialiser(grille);
    while(plein == 0 && gagne == 0){
      plein = grille_pleine(grille);
      remplir(tour,j1,j2,grille); 
      affichage_grille(grille);
      gagne = horizontale(grille,gagne);
      gagne = verticale(grille,gagne);
      gagne = diagonale_haut_bas(grille,gagne);
      gagne = diagonale_bas_haut(grille,gagne);
      tour++;
    }
    if(gagne == 1){
        printf("\nBravo à %s \n",j1);
        sauv(j1);
        printf("\nSi vous voulez continuer à jouer appuyer sur 1 sinon pour arrêter appuyer sur 2\n");
        scanf("%d", &choix_fin);
        if(choix_fin == 1){
            jouer();
        }
        else{
            printf("\n         ** Au revoir, merci d'avoir jouer **\n");
            exit(EXIT_SUCCESS);
        }
    } 
    if(gagne == 2){
        printf("\nBravo à %s \n",j2);
        sauv(j2);
        printf("\nSi vous voulez continuer à jouer appuyer sur 1 sinon pour arrêter appuyer sur 2\n");
        scanf("%d", &choix_fin);
        if(choix_fin == 1){
            jouer();
        }
        else{
            printf("\n         ** Au revoir, merci d'avoir jouer **\n");
            exit(EXIT_SUCCESS);
        }
    }
    if(gagne == 0){
        printf("\nEgalité\n");
        printf("\nSi vous voulez continuer à jouer appuyer sur 1 sinon pour arrêter appuyer sur 2\n");
        scanf("%d", &choix_fin);
        if(choix_fin == 1){
            jouer();
        }
        else{
            printf("\n         ** Au revoir, merci d'avoir jouer **\n");
            exit(EXIT_SUCCESS);
        }
    }
}


//Savoir si la grille est pleine (Haut de colonne)
int grille_pleine(int** grille){
    int colonne;
    int haut = 0;
    int plein = 0;
    for(colonne = 1; colonne < 7; colonne++){
        if(grille[1][colonne] == 1 || grille[1][colonne] == 2){
            haut = haut+1;
        }
    }
    if(haut == 7){
        plein = 1;
    }
    return plein;
}


//Puissance 4 Horizontale
int horizontale(int** grille, int gagne){
    int ligne;
    int colonne;
    for(ligne = 1; ligne < 7; ligne++){
    	for(colonne = 1; colonne < 5; colonne++){
        	if(grille[ligne][colonne] == grille[ligne][colonne+1] && grille[ligne][colonne] == grille[ligne][colonne+2] && grille[ligne][colonne] == grille[ligne][colonne+3]){
            	if(grille[ligne][colonne] == 1)
                	gagne = 1;
            	else if(grille[ligne][colonne] == 2)
                	gagne = 2;
        	}
        }
        for(colonne = 4; colonne < 8; colonne++){
            if(grille[ligne][colonne] == grille[ligne][colonne-1] && grille[ligne][colonne] == grille[ligne][colonne-2] && grille[ligne][colonne] == grille[ligne][colonne-3]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
        for(colonne = 2; colonne < 6; colonne++){
            if(grille[ligne][colonne] == grille[ligne][colonne-1] && grille[ligne][colonne] == grille[ligne][colonne+1] && grille[ligne][colonne] == grille[ligne][colonne+2]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
        for(colonne = 3; colonne < 7; colonne++){
            if(grille[ligne][colonne] == grille[ligne][colonne-2] && grille[ligne][colonne] == grille[ligne][colonne-1] && grille[ligne][colonne] == grille[ligne][colonne+1]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
  return gagne;
}


//Puissance 4 Verticale
int verticale(int** grille, int gagne){
    int ligne;
    int colonne;
    for(colonne = 1; colonne < 8; colonne++){
    	for(ligne = 1; ligne < 4; ligne++){
        	if(grille[ligne][colonne] == grille[ligne+1][colonne] && grille[ligne][colonne] == grille[ligne+2][colonne] && grille[ligne][colonne] == grille[ligne+3][colonne]){
            	if(grille[ligne][colonne] == 1)
                	gagne = 1;
            	else if(grille[ligne][colonne] == 2)
                	gagne = 2;
        	}
        }
        for(ligne = 3; ligne < 6; ligne++){
            if(grille[ligne][colonne] == grille[ligne][colonne-1] && grille[ligne][colonne] == grille[ligne-2][colonne] && grille[ligne][colonne] == grille[ligne-1][colonne]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
        	}
        }
        for(ligne = 2; ligne < 5; ligne++){
            if(grille[ligne][colonne] == grille[ligne][colonne-1] && grille[ligne][colonne] == grille[ligne+1][colonne] && grille[ligne][colonne] == grille[ligne+2][colonne]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
        	}
        }
        for(ligne = 4; ligne < 7; ligne++){
            if(grille[ligne][colonne] == grille[ligne][colonne-2] && grille[ligne][colonne] == grille[ligne-2][colonne] && grille[ligne][colonne] == grille[ligne-3][colonne]){
                if(grille[ligne][colonne]== 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
        	}
        }
    }
  return gagne;
}


//Puissance 4 Diagonale bas haut
int diagonale_bas_haut(int** grille, int gagne){
    int ligne;
    int colonne;
    for(ligne = 4; ligne < 7; ligne++){
        for(colonne = 1; colonne < 5; colonne++){ 
            if(grille[ligne][colonne] == grille[ligne-1][colonne+1] && grille[ligne][colonne] == grille[ligne-2][colonne+2] && grille[ligne][colonne] == grille[ligne-3][colonne+3]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] ==2)
                    gagne = 2;
            }
        }
    }
    for(colonne = 2; colonne < 6; colonne++){
        for(ligne = 3; ligne < 6; ligne++){
            if(grille[ligne][colonne] == grille[ligne+1][colonne-1] && grille[ligne][colonne] == grille[ligne-1][colonne+1] && grille[ligne][colonne] == grille[ligne-2][colonne-2]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
    for(colonne = 3; colonne < 7; colonne++){ 
        for(ligne = 2; ligne < 5; ligne++){
            if(grille[ligne][colonne] == grille[ligne+1][colonne-1] && grille[ligne][colonne] == grille[ligne+2][colonne-2] && grille[ligne][colonne] == grille[ligne-1][colonne+1]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
    for(colonne = 4; colonne < 8; colonne++){
        for(ligne = 1; ligne < 4; ligne++){
            if(grille[ligne][colonne] == grille[ligne+1][colonne-1] && grille[ligne][colonne] == grille[ligne+2][colonne-2] && grille[ligne][colonne] == grille[ligne+3][colonne-3]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
  return gagne;
}


//Puissance 4 Diagonale haut bas
int diagonale_haut_bas(int** grille, int gagne){
    int ligne;
    int colonne;
    for(ligne = 1; ligne < 4; ligne++){
        for(colonne = 1; colonne < 5; colonne++){
            if(grille[ligne][colonne] == grille[ligne+1][colonne+1] && grille[ligne][colonne] == grille[ligne+2][colonne+2] && grille[ligne][colonne] == grille[ligne+3][colonne+3]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
    for(colonne = 2; colonne < 6; colonne++){
        for(ligne = 2; ligne < 5; ligne++){
            if(grille[ligne][colonne] == grille[ligne+1][colonne+1] && grille[ligne][colonne] == grille[ligne-1][colonne-1] && grille[ligne][colonne] == grille[ligne+2][colonne+2]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
    for(colonne = 3; colonne < 7; colonne++){
        for(ligne = 3; ligne < 6; ligne++){
            if(grille[ligne][colonne] == grille[ligne-1][colonne-1] && grille[ligne][colonne] == grille[ligne+1][colonne+1] && grille[ligne][colonne] == grille[ligne-2][colonne-2]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
    for(colonne = 4; colonne < 8; colonne++){
        for(ligne = 4; ligne < 7; ligne++){
            if(grille[ligne][colonne] == grille[ligne-1][colonne-1] && grille[ligne][colonne] == grille[ligne-2][colonne-2] && grille[ligne][colonne] == grille[ligne-3][colonne-3]){
                if(grille[ligne][colonne] == 1)
                    gagne = 1;
                else if(grille[ligne][colonne] == 2)
                    gagne = 2;
            }
        }
    }
  return gagne;
}