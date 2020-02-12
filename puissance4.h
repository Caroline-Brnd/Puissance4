#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int** creation_degrille();
int** initialiser(int ** grille);
void affichage_grille(int** grille);
void nomdejoueur(char* j1, char* j2);
void sauv(char* joueur);
void jouer();
void remplir_grille(int tour, char* j1, char* j2, int* grille);
int grille_pleine(int** grille);
int horizontale(int** grille, int gagne);
int verticale(int** grille, int gagne);
int diagonale_bas_haut(int** grille, int gagne);
int diagonale_haut_bas(int** grille, int gagne);