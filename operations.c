#include "calc-mat.h"


_Bool additionner (int num_mat1, int num_mat2, _Bool soustraction)
//Additionne ou soustrait 2 matrices.
//Doit recevoir (dans l'ordre) les numéros des 2 matrices et 0 pour additionner ou 1 pour soustraire.
//Retourne 0 en cas d'erreur ou 1 en cas de succès.
{
	if (mat[num_mat1].taille_i != mat[num_mat2].taille_i || mat[num_mat1].taille_j != mat[num_mat2].taille_j)
	{strcpy(erreur, "Impossible d'additionner 2 matrices de dimensions différentes."); return 0;}

	//Préparation de la matrice résulat:
	mat[0].taille_i = mat[num_mat1].taille_i;
	mat[0].taille_j = mat[num_mat1].taille_j;

	if (soustraction)
	{
		for (int compteur_i = 0; compteur_i < mat[0].taille_i; compteur_i++)
		{
			for (int compteur_j = 0; compteur_j < mat[0].taille_j; compteur_j++)
			{mat[0].mat[compteur_i][compteur_j] = mat[num_mat1].mat[compteur_i][compteur_j] - mat[num_mat2].mat[compteur_i][compteur_j];}
		}
	}

	else
	{
		for (int compteur_i = 0; compteur_i < mat[0].taille_i; compteur_i++)
		{
			for (int compteur_j = 0; compteur_j < mat[0].taille_j; compteur_j++)
			{mat[0].mat[compteur_i][compteur_j] = mat[num_mat1].mat[compteur_i][compteur_j] + mat[num_mat2].mat[compteur_i][compteur_j];}
		}
	}

	return 1;
}


_Bool transposer (int num_mat)
//Transpose une matrice.
//Reçoit le numéro de la matrice à transposer, renvoit toujours 1 (Y peut pas avoir d'erreur!).
{
	//Préparation de la matrice résulat:
	mat[0].taille_i = mat[num_mat].taille_j;
	mat[0].taille_j = mat[num_mat].taille_i;

	//Transposition:
	for (int compteur_i = 0; compteur_i < mat[num_mat].taille_i; compteur_i++)
	{
		for (int compteur_j = 0; compteur_j < mat[num_mat].taille_j; compteur_j++)
		{mat[0].mat[compteur_j][compteur_i] = mat[num_mat].mat[compteur_i][compteur_j];}
	}

	return 1;
}


_Bool mult_s (int num_mat, float scalaire)
//Multiplie une matrice par un scalaire.
//Reçoit le numéro de la matrice et la valeur du scalaire, renvoit toujours 1.
{
	mat[0].taille_i = mat[num_mat].taille_i;
	mat[0].taille_j = mat[num_mat].taille_j;

	for (int compteur_i = 0; compteur_i < mat[num_mat].taille_i; compteur_i++)
	{
		for (int compteur_j = 0; compteur_j < mat[num_mat].taille_j; compteur_j++)
		{mat[0].mat[compteur_i][compteur_j] = mat[num_mat].mat[compteur_i][compteur_j] * scalaire;}
	}

	return 1;
}


_Bool mult_m (int num_mat1, int num_mat2)
//Mutliplie deux matrices ensemble.
//Reçoit les numéros des 2 matrices, renvoie 1 en cas de succès ou 0 en cas d'erreur.
{
	if (mat[num_mat1].taille_j != mat[num_mat2].taille_i)
	{strcpy(erreur, "Impossible de multiplier ces matrices. Svp s'assurer que le nombre de colonnes de la première est égal au nombre de lignes de la deuxième."); return 0;}

	mat[0].taille_i = mat[num_mat1].taille_i;
	mat[0].taille_j = mat[num_mat2].taille_j;

	for (int compteur_i = 0; compteur_i < mat[0].taille_i; compteur_i++)
	{
		for (int compteur_j = 0; compteur_j < mat[0].taille_j; compteur_j++)
		{
			mat[0].mat[compteur_i][compteur_j] = 0;
			for (int compteur_k = 0; compteur_k < mat[0].taille_i; compteur_k++)
			{mat[0].mat[compteur_i][compteur_j] += mat[num_mat1].mat[compteur_i][compteur_k] * mat[num_mat2].mat[compteur_k][compteur_j];}
		}
	}

	return 1;
}


_Bool puissance (int num_mat, int exposant)
//Calcule la puissance (nbre reçu en paramètre) d'une matrice (numéro reçu en paramètre).
//Renvoie 1 en cas de succès ou 0 en cas d'échec.
{
	if (mat[num_mat].taille_i != mat[num_mat].taille_j)
	{strcpy(erreur, "Erreur: Il est impossible de mutliplier une matrice par elle-même lorsqu'elle n'est pas carrée."); return 0;}

	if (exposant == 0)
	//Définit la matrice résultat comme étant la matrice identité:
	{
		for (int compteur_i = 0; compteur_i < mat[0].taille_i; compteur_i++)
		{
			for (int compteur_j = 0; compteur_j < mat[0].taille_j; compteur_j++)
			{
				if (compteur_i == compteur_j)
				{mat[0].mat[compteur_i][compteur_j] = 1;}
				else
				{mat[0].mat[compteur_i][compteur_j] = 0;}
			}
		}
		strcpy(mat[0].nom, "résultat");
		return 1;
	}
	
	if (exposant == 1)
	//Copie la matrice reçue dans la matrice résultat:
	{copier(num_mat, 0); strcpy(mat[0].nom, "resultat"); return 1;}

	//Gère tous les exposants supérieurs à 1:
	copier(num_mat, 10);
	for (int compteur = 1; compteur < exposant; compteur++) //donc si l'exposant est 1, il ne se sera tout simplement rien passé
	{
		if (!mult_m(num_mat, 10))
		{return 0;}
		copier(0, 10); //copie le résultat dans la matrice 10 (interne)
	}
	strcpy(mat[0].nom, "resultat");

	return 1;
}


int cof (struct matrice mat_input, int i, int j)
//Calcule et renvoie le cofacteur d'une valeur au sein d'une matrice.
//Reçoit en paramètres la matrice et les indices/coordonnées de la "case"/valeur.
//Renvoie -2555 en cas d'erreur.
{
	struct matrice mat_locale;
	_Bool depasse = 0;
	
	if (mat_input.taille_i < 2 || mat_input.taille_j < 2)
	{strcpy(erreur, "Erreur: Impossible de trouver le cofacteur d'une matrice qui n'est pas au moins 2x2."); puts(erreur); return -2555;}
	
	mat_locale.taille_i = mat_input.taille_i - 1;
	mat_locale.taille_j = mat_input.taille_j - 1;
	
	for (int ci = 0; ci < mat_input.taille_i; ci++)
	{
		if (ci == i)
		{depasse = 1; continue;}
		
		for (int cj = 0; cj < mat_input.taille_j; cj++)
		{
			if (cj < j)
			{mat_locale.mat[ci - depasse][cj] = mat_input.mat[ci][cj];}
			else if (cj > j)
			{mat_locale.mat[ci - depasse][cj - 1] = mat_input.mat[ci][cj];}
		}
	}
	
	if ((i + j) % 2 != 0)
	{return -det_interne(mat_locale);}
	else
	{return det_interne(mat_locale);}
}


int det_interne (struct matrice mat_input)
//Calcule et renvoie le déterminant de la matrice reçue en paramètre.
//Ne doit normalement pas être appelé par autre chose que les fonctions cof et determinant.
//Utiliser la fonction determinant pour effectuer l'opération normale sur une matrice normale.
{
	int det = 0;
	
	if (mat_input.taille_i <= 2)
	{
		mat[10] = mat_input;
		return determinant(10);
	}
	
	//mat[11] = mat_input;
	//afficher(11);
	
	for (int j = 0; j < mat_input.taille_j; j++) //nous utiliserons i = 0 comme colonne de référence
	{
		det += mat_input.mat[0][j] * cof(mat_input, 0, j);
		//printf("mat[%d][%d] = %d\n", 0, j, cof(mat_input, 0, j));
	}
	
	return det;
}


int determinant (int num_mat)
//Calcule et renvoie le déterminant de la matrice dont il a reçu le numéro en paramètre.
//Renvoie -2555 en cas d'erreur.
{
	int det = 0;
	
	if (mat[num_mat].taille_i <= 0 || mat[num_mat].taille_j <= 0)
	{strcpy(erreur, "Erreur: Impossible de calculer le déterminant d'une matrice vide."); return -2555;}
	
	else if (mat[num_mat].taille_i != mat[num_mat].taille_j)
	{strcpy(erreur, "Erreur: Impossible de calculer le déterminant d'une matrice qui n'est pas carrée."); return -2555;}
	
	else if (mat[num_mat].taille_i == 1)
	//Trouve tout de suite le déterminant si la matrice ne contient qu'un seul nbre:
	{det = mat[num_mat].mat[0][0];}
	
	else if (mat[num_mat].taille_i == 2)
	//Calcule le déterminant si c'est une matrice 2x2:
	{det = mat[num_mat].mat[0][0] * mat[num_mat].mat[1][1] - mat[num_mat].mat[0][1] * mat[num_mat].mat[1][0];}
	
	else
	//Calcule le déterminant si c'est une matrice plus grande que 2x2:
	{det = det_interne(mat[num_mat]);}
	
	return det;
}


_Bool inverser (int num_mat)
//Calcule la matrice inverse de la matrice dont le numéro est fourni en paramètre.
//Renvoie 1 en cas de succès et 0 en cas d'échec.
{
	int det;
	
	if (mat[num_mat].taille_i <= 0 || mat[num_mat].taille_j <= 0)
	{strcpy(erreur, "Erreur: Impossible d'inverser une matrice vide."); return 0;}
	
	if (mat[num_mat].taille_i != mat[num_mat].taille_j)
	{strcpy(erreur, "Erreur: Impossible d'inverser une matrice qui n'est pas carrée."); return 0;}
	
	det = determinant(num_mat);
	if (det == 0)
	{strcpy(erreur, "Cette matrice n'est pas inversible (déterminant = 0)."); return 0;}
	
	copier(num_mat, 0);
	
	//Création de la matrice des cofacteurs:
	for (int i = 0; i < mat[num_mat].taille_i; i++)
	{
		for (int j = 0; j < mat[num_mat].taille_j; j++)
		{mat[0].mat[i][j] = cof(mat[num_mat], i, j);}
	}
	
	//Transformation en matrice adjacente:
	transposer(0);
	
	//Transformation en matrice inverse:
	mult_s(0, (float) 1/det); //PROBLÈME: J'ai besoin de floats!
	strcpy(mat[0].nom, "Résultat");
	return 1;
}