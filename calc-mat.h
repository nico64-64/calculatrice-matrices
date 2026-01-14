#include <stdio.h>
#include <string.h>
#include <math.h>


#define VERSION "1.0"

#define MAX_COL 9 //Nombre maximal de colonnes par matrice (n)
#define MAX_LIGNES 9 //Nombre maximal de lignes par matrice (m)

struct matrice
//Struct contenant les informations d'une matrice:
{
	char nom[40]; //nom de la matrice
	float mat[MAX_LIGNES][MAX_COL]; //la matrice elle-même [i] [j]
	int taille_i; //nbre de lignes (m)
	int taille_j; //nbre de colonnes (n)
};

struct matrice mat[11]; //contient les matrices du programme (la matrice 1 est réservée aux résultats des calculs et les matrices 10 et 11 aux besoins internes des opérations)
char erreur[150] = "Aucune Erreur"; //contient le message d'erreur d'un opérateur, qui sera affiché à l'écran au besoin


//Fonctions:

//calc-mat.c:
void affiche_nbre (float valeur);
void afficher (int num_mat);
void copier (int num_mat1, int num_mat2);
void enregistre_matrice (int num_mat);
_Bool est_un_nbre (char input[]);
int main ();
_Bool remplit_matrice (int num_mat, int num_ligne, char ligne[]);
_Bool reprend_matrice (int num_mat);
int selection_matrice (char input[]);
int trouve_taille (char string[]);

//operations.c:
_Bool additionner (int num_mat1, int num_mat2, _Bool soustraction);
int cof (struct matrice mat_input, int i, int j);
int determinant (int num_mat);
int det_interne (struct matrice mat_input);
_Bool inverser (int num_mat);
_Bool mult_m (int num_mat1, int num_mat2);
_Bool mult_s (int num_mat, float scalaire);
_Bool puissance (int num_mat, int exposant);
_Bool transposer (int num_mat);