#include "operations.c"


int trouve_taille(char string[])
//Renvoie la taille d'une string (incluant le NULL terminal).
{
	int compteur = 0;
	for (; string[compteur] != '\000'; compteur++){}
	return compteur;
}


_Bool est_un_nbre(char input[])
//Renvoie 1 si "input" est un nombre et 0 si ce n'en est pas un.
{
	for (int compteur = 0; input[compteur] != '\000'; compteur++)
	{
		if (input[compteur] != '0' && input[compteur] != '1' && input[compteur] != '2' && input[compteur] != '3' && input[compteur] != '4' && input[compteur] != '5' && input[compteur] != '6' \
			&& input[compteur] != '7' && input[compteur] != '8' && input[compteur] != '9' && input[compteur] != '-' && input[compteur] != '.')
		{strcpy(erreur, "Seuls des chiffres séparés par des espaces sont acceptés"); return 0;}
	}
	return 1;
}


int selectionne_matrice(char input[])
//Trouve une matrice à sélectionner en fonction d'un mot reçu de l'utilisateur.
//Renvoie le numéro de la matrice sélectionnée, ou -1 en cas d'échec.
{
	int selection = -1; //témoin de sélection...

	for (int compteur = 0; compteur < 10; compteur++) //fouille dans les 10 matrices...
	{
		if (!strcmp(input, mat[compteur].nom)) //nom de matrice
		{selection = compteur; compteur = 10;}
	}

	//# de matrice:
	switch (input[0])
	{
	case '0':
		selection = 0;
		break;
	case '1':
		selection = 1;
		break;
	case '2':
		selection = 2;
		break;
	case '3':
		selection = 3;
		break;
	case '4':
		selection = 4;
		break;
	case '5':
		selection = 5;
		break;
	case '6':
		selection = 6;
		break;
	case '7':
		selection = 7;
		break;
	case '8':
		selection = 8;
		break;
	case '9':
		selection = 9;
		break;
	case '#':
		switch (input[1])
		{
		case '0':
			selection = 0;
			break;
		case '1':
			selection = 1;
			break;
		case '2':
			selection = 2;
			break;
		case '3':
			selection = 3;
			break;
		case '4':
			selection = 4;
			break;
		case '5':
			selection = 5;
			break;
		case '6':
			selection = 6;
			break;
		case '7':
			selection = 7;
			break;
		case '8':
			selection = 8;
			break;
		case '9':
			selection = 9;
			break;
		}
		break;
	}
	
	if (selection == -1)
	{strcpy(erreur, "Impossible d'identifier cette matrice. Soyez plus précis!\n");}
	
	if ((input[0] != '#' && (input[1] == '1' || input[1] == '2' || input[1] == '3' || input[1] == '4' || input[1] == '5' || input[1] == '6' || input[1] == '7' \
		|| input[1] == '8' || input[1] == '9' || input[1] == '0')) || input[0] == '#' && (input[2] == '0' || input[2] == '1' || input[2] == '2' || input[2] == '3' \
		|| input[2] == '4' || input[2] == '5' || input[2] == '6' || input[2] == '7' || input[2] == '8' || input[2] == '9'))
	{selection = -1; strcpy(erreur, "Ce programme contient uniquement 10 matrices (#0 à #9).\n");}

	return selection;
}


void enregistre_matrice(int num_mat)
//Enregistre une matrice dans un fichier txt correspondant à son numéro.
{
	FILE* fichier;
	char nom_fichier[30];
	
	if (mat[num_mat].taille_i <= 0 || mat[num_mat].taille_j <= 0)
	{printf("Erreur: Impossible d'enregistrer une matrice vide.\n"); return;}
	
	sprintf(nom_fichier, "sauvegarde_matrice_%d.txt", num_mat);
	fichier = fopen(nom_fichier, "w");

	fprintf(fichier, "%s\n%d x %d\n\n", mat[num_mat].nom, mat[num_mat].taille_i, mat[num_mat].taille_j);
	for (int compteur_i = 0; compteur_i < mat[num_mat].taille_i; compteur_i++)
	{
		for (int compteur_j = 0; compteur_j < mat[num_mat].taille_j; compteur_j++)
		{fprintf(fichier, "%f ", mat[num_mat].mat[compteur_i][compteur_j]);}
		fprintf(fichier, "\n");
	}

	fclose(fichier);
}


_Bool reprend_matrice(int num_mat)
//Reprend/ouvre une matrice depuis sa sauvegarde.
//Renvoie 0 (échec) ou 1 (réussite).
{
	FILE* fichier;
	char nom_fichier[30];

	sprintf(nom_fichier, "sauvegarde_matrice_%d.txt", num_mat);
	if ((fichier = fopen(nom_fichier, "r")) == NULL)
	{sprintf(erreur, "Erreur: Cette matrice n'a pas été enregistrée ou est introuvable."); return 0;}

	fscanf(fichier, "%s", mat[num_mat].nom);
	fscanf(fichier, "%d", &mat[num_mat].taille_i);
	fscanf(fichier, "%s", nom_fichier); //faut bien que je le mette quelque part (le "x" entre taille_i et taille_j)...
	fscanf(fichier, "%d", &mat[num_mat].taille_j);

	for (int compteur_i = 0; compteur_i < mat[num_mat].taille_i; compteur_i++)
	{
		for (int compteur_j = 0; compteur_j < mat[num_mat].taille_j; compteur_j++)
		{fscanf(fichier, "%f", &mat[num_mat].mat[compteur_i][compteur_j]);}
	}

	fclose(fichier);
	return 1;
}


void copier(int num_mat1, int num_mat2)
//Copie une matrice dans l'emplacement d'une autre.
//Reçoit le numéro de la matrice à copier, suivie de celui de la matrice destination.
{
	mat[num_mat2] = mat[num_mat1]; //Je n'aurais jamais cru que ça pouvait être aussi simple... (!!!)
}


_Bool remplit_matrice(int num_mat, int num_ligne, char ligne[])
//Remplit une ligne d'une matrice avec les nombres reçus en paramètre (dans la string "ligne").
//Retourne 0 en cas d'erreur, 1 en cas de succès.
//"ligne" doit être une string de nombres séparés par des espaces, "num_ligne" le numéro de la ligne de matrice à remplir, et "num_mat" le numéro de la matrice sélectionnée.
{
	char buffer[MAX_COL + 1][10]; //contiendra les "mots" entrés par l'utilisateur (le +1 sert à contenir le NULL final (10e mot) si on a 9 colonnes)
	float nbre[MAX_COL]; //contiendra les nombres entrés par l'utilisateur
	_Bool sortir_de_la_loop = 0;

	sprintf(buffer[0], "%s", strtok(ligne, " \t\n")); //trouve le premier "mot"

	if (!est_un_nbre(buffer[0])) //trouve si le 1er "mot" est un nombre...
	{return 0;} //...sinon, retourne 0. Le message d'erreur est déjà setté par "est_un_nbre".
	sscanf(buffer[0], "%f", &nbre[0]); //trouve la valeur numérique de ce nombre (maintenant qu'on sait que c'en est un...)

	if (num_ligne > 0 && mat[num_mat].taille_j == 1)
	{sortir_de_la_loop = 1;}

	for (int compteur = 1; compteur <= MAX_COL && !sortir_de_la_loop; compteur++)
	//Sépare les prochains "mots", puis trouve leur valeur numérique si ce sont des nombres (jusqu'à atteindre le nombre maximal de colonnes):
	{
		if (!num_ligne && compteur == MAX_COL)
		{sortir_de_la_loop = 1; /*strcpy(erreur, "Erreur: Trop de valeurs on été entrées dans cette ligne."); return 0;*/}
		
		if (!num_ligne)
		//Ajustement du nombre de colonnes si c'est la 1ère ligne:
		{mat[num_mat].taille_j = compteur;}
		
		if (!sortir_de_la_loop)
		//Trouvons le prochain "mot"...
		{sprintf(buffer[compteur], "%s", strtok(NULL, " \t\n"));}

		if (!strcmp(buffer[compteur], "(null)") && num_ligne > 0)
		//Fin de l'input avant la dernière valeur attendue:
		{
			if (!num_ligne)
			{mat[num_mat].taille_j = 0;}
			strcpy(erreur, "Erreur: Le nombre de valeurs n'est pas suffisant pour cette ligne.");
			return 0;
		}

		else if (!strcmp(buffer[compteur], "(null)"))
		//Fin de l'input alors que c'est la 1ère ligne:
		{sortir_de_la_loop = 1;}

		else if (!sortir_de_la_loop && !est_un_nbre(buffer[compteur]))
		//Le "mot" n'est pas un nombre:
		{if (!num_ligne) {mat[num_mat].taille_j = 0;} return 0;}

		if (!sortir_de_la_loop)
		{sscanf(buffer[compteur], "%f", &nbre[compteur]);} //et on en trouve la valeur numérique...

		if (compteur + 1 >= mat[num_mat].taille_j && num_ligne > 0)
		//Fin de la ligne (si ce n'est pas la 1ère)?
		{sortir_de_la_loop = 1;}
	}

	if (strtok(NULL, " \t\n") != NULL)
	//Trop de nombres:
	{if (!num_ligne) {mat[num_mat].taille_j = 0;} strcpy(erreur, "Erreur: Trop de valeurs ont été entrées dans cette ligne."); return 0;}

	//Si le code se rend jusqu'ici, c'est que tous les "mots" sont des nombres...
	//...donc on peut maintenant les copier dans la matrice voulue.
	//NOTE: Il faut absolument arrêter à "taille_j", car le reste de "nbre[]" est juste plein de cochonnerie qui ne veut rien dire.
	for (int compteur = 0; compteur < mat[num_mat].taille_j; compteur++)
	{mat[num_mat].mat[num_ligne][compteur] = nbre[compteur];}
	
	return 1;
}


void affiche_nbre(float valeur)
//Affiche un nombre en le paddant avec des espaces si nécessaire.
//Note: Si un nombre semblant être un entier est affiché avec des décimales vides, ce n'est pas un vrai entier, mais plutôt un nombre décimal qui devient un entier lorsque "arrondi" à 2 chiffres après la virgule.
{
	int valeur_entiere = floor(valeur); //cette valeur ne sera pas utilisée si elle n'est pas égale à la vraie valeur (je sais que floor != round!)
	
	if (valeur - valeur_entiere < 0.00001) //entier
	{
		if (valeur >= 0 && valeur < 10) //1 chiffre (6 padding)
		{printf("   %d    ", valeur_entiere);}
		else if ((valeur >= 0 && valeur < 100) || (valeur > -10 && valeur < 0)) //2 chiffres (5 padding)
		{printf("  %d    ", valeur_entiere);}
		else if ((valeur >= 0 && valeur < 1000) || (valeur > -100 && valeur < 0)) //3 chiffres (4 padding)
		{printf(" %d    ", valeur_entiere);}
		else //4 chiffres (3 padding)
		{printf("%d    ", valeur_entiere);}
	}
	else //nombre à virgule tronqués à la 2e décimale (.xx)
	{
		if (valeur >= 0 && valeur < 10) //1 chiffre (3 padding)
		{printf("   %.2f ", valeur);}
		else if ((valeur >= 0 && valeur < 100) || (valeur > -10 && valeur < 0)) //2 chiffres (2 padding)
		{printf("  %.2f ", valeur);}
		else if ((valeur >= 0 && valeur < 1000) || (valeur > -100 && valeur < 0)) //3 chiffres (1 padding)
		{printf(" %.2f ", valeur);}
		else //4 chiffres (pas de padding)
		{printf("%.2f ", valeur);}
	}
}


void afficher(int num_mat)
//Affiche une matrice à l'écran.
{
	//Nom, numéro et taille de la matrice:
	printf("Matrice %s (#%d) (%dx%d):\n", mat[num_mat].nom, num_mat, mat[num_mat].taille_i, mat[num_mat].taille_j);
	
	if (mat[num_mat].taille_i > 0 && mat[num_mat].taille_j > 0)
	{
		//Première Ligne:
		printf(" _");
		for (int compteur = 0; compteur < mat[num_mat].taille_j; compteur++)
		{printf("        ");}
		printf("_\n| ");
		for (int compteur = 0; compteur < mat[num_mat].taille_j; compteur++)
		{affiche_nbre(mat[num_mat].mat[0][compteur]);}
		printf(" |\n");
		
		//Lignes intermédiaires:
		for (int compteur_i = 1; compteur_i < mat[num_mat].taille_i - 1; compteur_i++)
		{
			printf("| ");
			for (int compteur_j = 0; compteur_j < mat[num_mat].taille_j; compteur_j++)
			{affiche_nbre(mat[num_mat].mat[compteur_i][compteur_j]);}
			printf(" |\n");
		}
		
		//Dernière Ligne:
		if (mat[num_mat].taille_i >= 2)
		{
			printf("|_");
			for (int compteur_j = 0; compteur_j < mat[num_mat].taille_j; compteur_j++)
			{affiche_nbre(mat[num_mat].mat[mat[num_mat].taille_i - 1][compteur_j]);}
			printf("_|\n");
		}
	} //if taille positive
}


int main()
//Affiche le texte d'ouverture et gère la main loop du programme.
{
	_Bool quitter = 0; //indique si l'utilisateur veut fermer le programme
	char input[200] = "pas d'input..."; //contient l'input entré par l'utilisateur
	char cmd[7][40]; //contient l'input de l'utilisateur séparé en mots (6 mots max, soit de 1 à 6 (pourquoi 1??!))
	int selection[2]; //indique quelle(s) matrice(s) l'utlisateur a choisie(s)
	float scalaire = 0; //utilisé par diverses commandes pour stocker un scalaire.

	//Texte de bienvenue:
	printf("\n                          |--------------------------|\n");
	printf("                          | Calculatrice de Matrices |\n");
	printf("                          |       version %s        |\n", VERSION);
	printf("                          |--------------------------|\n\n");
	
	printf("Chaque matrice est indentifiée par un numéro de 1 à 9 (et parfois aussi un nom).\n");
	printf("Le résultat des calculs est stocké dans la matrice #0.\nLes opérations sur cette matrice sont permises, mais non-recommandées.\n");
	printf("Entrer \"aide\" pour consulter la liste et la description des commandes.\n");
	printf("Programmé en C par Nicolas Audette.\n\n");
	printf("Entrez une première commande:\n--> ");

	//Préparation de la matrice résultat:
	strcpy(mat[0].nom, "Résultat");

	//Main loop:
	while (!quitter)
	{
		//Prend la commande de l'utilisateur:
		fgets(input, 200, stdin);

		//Sépare la commande en mots:
		sprintf(cmd[0], "%s", strtok(input, " \t\n"));
		for (int compteur = 1; compteur < 7; compteur++)
		{sprintf(cmd[compteur], "%s", strtok(NULL, " \n"));}

		//Enlève le mot "matrice" s'il est présent (il ne sert à rien):
		if (!strcmp(cmd[1], "matrice") || !strcmp(cmd[1], "mat") || !strcmp(cmd[1], "matrices") || !strcmp(cmd[1], "matrix"))
		{
			for (int compteur = 2; compteur < 7; compteur++)
			{strcpy(cmd[compteur-1], cmd[compteur]);}
		}


		//Exécute la commande (si c'en est une):

		if (!strcmp(cmd[0], "afficher") || !strcmp(cmd[0], "voir") || !strcmp(cmd[0], "consulter") || !strcmp(cmd[0], "montrer") || !strcmp(cmd[0], "v"))
		//Affichage d'une matrice:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Que voulez-vous voir?\n");}
			
			else if (!strcmp(cmd[1], "tout") || !strcmp(cmd[1], "toutes") || !strcmp(cmd[1], "tous"))
			{
				for (int compteur = 1; compteur < 10; compteur++)
				{afficher(compteur); printf("\n");}
			}

			else //on cherche le nom ou le # d'une matrice
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la bonne matrice

				if (selection[0] == -1)
				{printf("%s", erreur);}

				else
				//Affichage de la matrice:
				{afficher(selection[0]);}
			} //else (cherche nom ou # de matrice)
		}

		else if (!strcmp(cmd[0], "créer") || !strcmp(cmd[0], "creer") || !strcmp(cmd[0], "remplir") || !strcmp(cmd[0], "nouvelle") || !strcmp(cmd[0], "nouveau") || !strcmp(cmd[0], "n"))
		//Remplissage d'une matrice:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Quelle matrice voulez-vous remplir?\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à remplir

				if (selection[0] < 0)
				{printf("%s", erreur);}

				else if (!selection[0])
				{printf("La matrice 0 est reservée aux résultats des calculs.\n");}

				else
				{
					printf("Entrez vos valeurs ligne par ligne, separées par des espaces.\nVos valeurs peuvent être des nombres entiers ou décimaux, positifs ou négatifs.\nEntrer une ligne vide pour terminer.\n* Utilisez le point, pas la virgule! *\n* Maximum 9x9! *\n");

					for (int compteur = 0; compteur < MAX_LIGNES; compteur++)
					{
						printf("\n%d) ", compteur + 1);
						fgets(input, 100, stdin);
						if (compteur == MAX_LIGNES - 1)
						{mat[selection[0]].taille_i = MAX_LIGNES;}
						if (!strcmp(input, "\n"))
						{mat[selection[0]].taille_i = compteur; compteur = MAX_LIGNES;}
						else if (!remplit_matrice(selection[0], compteur, input))
						{printf("%s\n", erreur); compteur--;}
					}

					printf("\nVoulez-vous nommer cette matrice? (un nom sans espace est préférable)\nEntrer ce nom maintenant, ou une ligne vide pour laisser le nom vide.\n");
					fgets(mat[selection[0]].nom, sizeof(mat[selection[0]].nom), stdin);
					mat[selection[0]].nom[trouve_taille(mat[selection[0]].nom) - 1] = '\000';
				}
			}
		}

		else if (!strcmp(cmd[0], "copier") || !strcmp(cmd[0], "copie") || !strcmp(cmd[0], "cp") || !strcmp(cmd[0], "c"))
		//Copie une matrice dans une autre:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Entrer la matrice à copier, puis la matrice de destination.\n");}

			else
			{
				if (!strcmp(cmd[1], "--renommer") || !strcmp(cmd[1], "-r") || !strcmp(cmd[1], "-rn") || !strcmp(cmd[1], "--rn"))
				{strcpy(input, cmd[2]); /*sert ici de buffer...*/ strcpy(cmd[1], cmd[3]); strcpy(cmd[2], cmd[4]);}
				else
				{strcpy(input, "-NE_PAS_RENOMMER-");}
				
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à copier
				selection[1] = selectionne_matrice(cmd[2]); //trouve la matrice destination
				if (selection[0] < 0)
				{printf("Matrice à copier: %s", erreur);}
				else if (selection[1] < 0)
				{printf("Matrice destination: %s", erreur);}
				else
				{
					copier(selection[0], selection[1]);
					if (strcmp(input, "-NE_PAS_RENOMMER-") != 0)
					{strcpy(mat[selection[1]].nom, input);}
				}
			}
		}

		else if (!strcmp(cmd[0], "enregistrer") || !strcmp(cmd[0], "sauvegarder") || !strcmp(cmd[0], "enr") || !strcmp(cmd[0], "sauv") || !strcmp(cmd[0], "s"))
		//Enregistrement d'une matrice:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Quelle matrice voulez-vous enregistrer?\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à enregistrer
				if (selection[0] > 0)
				{enregistre_matrice(selection[0]);}
				else if (!selection[0])
				{printf("La matrice 0 est réservée aux résultats des calculs.\nPour enregistrer un résultat, copiez le dans une autre matrice et enregistrez celle-ci.\n");}
				else
				{printf("%s", erreur);}
			}
		}

		else if (!strcmp(cmd[0], "reprendre") || !strcmp(cmd[0], "charger") || !strcmp(cmd[0], "ouvrir") || !strcmp(cmd[0], "ouv") || !strcmp(cmd[0], "o"))
		//Reprise/ouverture d'une matrice préenregstrée:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Quelle matrice voulez-vous reprendre? (utiliser le numéro)\n");}
			
			else if (!strcmp(cmd[1], "tout") || !strcmp(cmd[1], "toutes") || !strcmp(cmd[1], "tous"))
			{
				for (int compteur = 1; compteur < 10; compteur++)
				{reprend_matrice(compteur);}
			}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à ouvrir/reprendre
				if (selection[0] > 0)
				{
					if (reprend_matrice(selection[0]))
					{afficher(selection[0]);}
					else
					{printf("%s\n", erreur);}
				}
				else if (!selection[0])
				{printf("La matrice 0 est reservée aux résultats des calculs et ne peut donc pas être sauvegardée ni ouverte.\n");}
				else
				{printf("%s", erreur);}
			}
		}

		else if (!strcmp(cmd[0], "additionner") || !strcmp(cmd[0], "addition") || !strcmp(cmd[0], "add") || !strcmp(cmd[0], "+"))
		//Addition de 2 matrices:
		{
			if (!strcmp(cmd[2], "et") || !strcmp(cmd[2], "&") || !strcmp(cmd[2], "+"))
			{
				for (int compteur = 3; compteur < 7; compteur++)
				{strcpy(cmd[compteur-1], cmd[compteur]);}
			}

			if (!strcmp(cmd[1], "(null)"))
			{printf("Quelles matrices voulez-vous additionner?\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la 1ère matrice à additionner
				selection[1] = selectionne_matrice(cmd[2]); //trouve la 2e matrice à additionner
				if (selection[0] < 0)
				{printf("Première matrice: %s", erreur);}
				else if (selection[1] < 0)
				{printf("Deuxième matrice: %s", erreur);}
				else if (!additionner(selection[0], selection[1], 0))
				{printf("%s\n", erreur);}
				else
				{afficher(0);}
			}
		}

		else if (!strcmp(cmd[0], "soustraire") || !strcmp(cmd[0], "soustraction") || !strcmp(cmd[0], "-"))
		//Soustraction de 2 matrices:
		{
			if (!strcmp(cmd[2], "et") || !strcmp(cmd[2], "&") || !strcmp(cmd[2], "-"))
			{
				for (int compteur = 3; compteur < 7; compteur++)
				{strcpy(cmd[compteur-1], cmd[compteur]);}
			}

			if (!strcmp(cmd[1], "(null)"))
			{printf("Quelles matrices voulez-vous soustraire?\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à laquelle soustraire
				selection[1] = selectionne_matrice(cmd[2]); //trouve la matrice à soustraire
				if (selection[0] < 0)
				{printf("Première matrice: %s", erreur);}
				else if (selection[1] < 0)
				{printf("Deuxième matrice: %s", erreur);}
				else if (!additionner(selection[0], selection[1], 1))
				{printf("%s\n", erreur);}
				else
				{afficher(0);}
			}
		}

		else if (!strcmp(cmd[0], "transposer") || !strcmp(cmd[0], "transposé") || !strcmp(cmd[0], "transposée") || !strcmp(cmd[0], "t"))
		//Transposition d'une matrice:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Quelle matrice voulez-vous transposer?\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à transposer
				if (selection[0] < 0)
				{printf("%s", erreur);}
				transposer(selection[0]);
				afficher(0);
			}
		}

		else if (!strcmp(cmd[0], "multiplication_s") || !strcmp(cmd[0], "mult_s") || !strcmp(cmd[0], "m_s") || !strcmp(cmd[0], "ms") || !strcmp(cmd[0], "x"))
		//Mtliplication d'une matrice par un scalaire:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Svp entrer une matrice suivie d'un scalaire.\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à mutliplier
				if (selection[0] < 0)
				{printf("%s", erreur);}
				else if (!est_un_nbre(cmd[2]))
				{printf("%s pour le scalaire.\n", erreur);}
				else
				{
					sscanf(cmd[2], "%f", &scalaire);
					if (!mult_s(selection[0], scalaire))
					{printf("%s\n", erreur);}
					else
					{afficher(0);}
				}
			}
		}

		else if (!strcmp(cmd[0], "multiplication_m") || !strcmp(cmd[0], "mult_m") || !strcmp(cmd[0], "m_m") || !strcmp(cmd[0], "mm") || !strcmp(cmd[0], "*"))
		//Mutliplie 2 matrices ensemble.
		{
			if (!strcmp(cmd[2], "et") || !strcmp(cmd[2], "&") || !strcmp(cmd[2], "*") || !strcmp(cmd[2], "x"))
			{
				for (int compteur = 3; compteur < 7; compteur++)
				{strcpy(cmd[compteur-1], cmd[compteur]);}
			}

			if (!strcmp(cmd[1], "(null)"))
			{printf("Quelles matrices voulez-vous multiplier?\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la 1ère matrice à multiplier
				selection[1] = selectionne_matrice(cmd[2]); //trouve la 2e matrice à multiplier
				if (selection[0] < 0)
				{printf("Première matrice: %s", erreur);}
				else if (selection[1] < 0)
				{printf("Deuxième matrice: %s", erreur);}
				else if (!mult_m(selection[0], selection[1]))
				{printf("%s\n", erreur);}
				else
				{afficher(0);}
			}
		}

		else if (!strcmp(cmd[0], "puissance") || !strcmp(cmd[0], "exposant") || !strcmp(cmd[0], "exp") || !strcmp(cmd[0], "^"))
		//Trouve la puissance d'une matrice:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Svp entrer une matrice suivie d'un scalaire (l'exposant).\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]); //trouve la matrice à mutliplier
				if (selection[0] < 0)
				{printf("%s", erreur);}
				else if (!est_un_nbre(cmd[2]))
				{printf("%s pour l'exposant.\n", erreur);}
				else
				{
					sscanf(cmd[2], "%f", &scalaire);
					if (scalaire - floor(scalaire) > 0.000001 || scalaire <= 0)
					{printf("Les exposants négatifs, nuls ou décimaux ne sont pas supportés.\nVous pouvez toutefois essayer d'inverser cette matrice, ce qui équivaut à en calculer la puissance -1.\n");}
					else
					{
						if (!puissance(selection[0], scalaire))
						{printf("%s\n", erreur);}
						else
						{afficher(0);}
					}
				}
			}
		}

		else if (!strcmp(cmd[0], "déterminant") || !strcmp(cmd[0], "determinant") || !strcmp(cmd[0], "dét") || !strcmp(cmd[0], "det") || !strcmp(cmd[0], "d"))
		//Trouve le déterminant de la matrice:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Svp entrer le nom ou le numéro d'une matrice).\n");}

			else
			{
				selection[0] = selectionne_matrice(cmd[1]);
				if (selection[0] < 0)
				{printf("%s", erreur);}
				else
				{
					scalaire = determinant(selection[0]);
					if (scalaire == -2555)
					{printf("%s\n", erreur);}
					else
					{printf("Déterminant = %f\n", scalaire);}
				}
			}
		}
		
		else if (!strcmp(cmd[0], "inverser") || !strcmp(cmd[0], "inverse") || !strcmp(cmd[0], "inv") || !strcmp(cmd[0], "i"))
		//Inverse la matrice:
		{
			if (!strcmp(cmd[1], "(null)"))
			{printf("Svp entrer le nom ou le numéro d'une matrice).\n");}
			
			else
			{
				selection[0] = selectionne_matrice(cmd[1]);
				if (selection[0] < 0)
				{printf("%s\n", erreur);}
				else
				{
					if (!inverser(selection[0]))
					{printf("%s\n", erreur);}
					else
					{afficher(0);}
				}
			}
		}

		else if (!strcmp(cmd[0], "aide") || !strcmp(cmd[0], "?") || !strcmp(cmd[0], "liste") || !strcmp(cmd[0], "ls") || !strcmp(cmd[0], "cmd") || !strcmp(cmd[0], "cmds"))
		//Affiche la liste des commandes:
		{
			printf("\nListe des commandes:\n");
			printf(" COMMANDES      | EXPLICATIONS & PARAMÈTRES\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" afficher       | Affiche une matrice.\n");
			printf(" consulter      |  > 'tout' ou 'toutes'   OU\n");
			printf(" voir / v       |  > 'X', où X = numéro ou nom de la matrice\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" créer          | Crée une nouvelle matrice.\n");
			printf(" nouvelle / n   |  > 'X', où X = numéro (1 à 9) de la matrice (pas le nom!)\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" copier         | Copie une matrice dans un autre emplacement.\n");
			printf(" cp             |  > 'X Y', où X = matrice à copier, Y = destination   OU\n");
			printf(" c              |  > '-r X Y Z', où X = nom de la nouvelle matrice,\n");
			printf("                |                   Y = numéro ou nom de la matrice à copier,\n");
			printf("                |            Z = numéro de la matrice à écraser (pas le nom!)\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" sauvegarder    | Sauvegarde une matrice afin de pouvoir la reprendre\n");
			printf(" enregistrer    | n'importe quand (même si le programme est arrêté).\n");
			printf(" sauv / enr / s |  > 'X', où X = numéro (1 à 9) ou nom de la matrice\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" ouvrir         | Recrée une matrice à partir de sa sauvegarde.\n");
			printf(" charger / ouv  |  > 'tout' ou 'toutes'   OU\n");
			printf(" reprendre / o  |  > 'X', où X = numéro (1 à 9) de la matrice (pas le nom!)\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" additionner    | Additionne 2 matrices.\n");
			printf(" add / +        |  > 'X Y', où X et Y = numéros ou noms des matrices\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" soustraire     | Soustrait la deuxième matrice à la première.\n");
			printf(" -              |  > 'X Y', où X et Y = numéros ou noms des matrices\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" transposer     | Transpose une matrice.\n");
			printf(" t              |  > 'X', où X = numéro ou nom de la matrice\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" mult_s         | Multiplie une matrice par un scalaire.\n");
			printf(" ms             |  > 'X Y', où X = numéro ou nom de la matrice\n");
			printf(" x              |              Y = scalaire\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" mult_m         | Multiplie la première matrice par la deuxième.\n");
			printf(" mm / *         |  > 'X Y', où X et Y = numéros ou noms des matrices\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" puissance      | Trouve une certaine puissance d'une matrice.\n");
			printf(" exposant       |  > 'X Y', où X = numéro ou nom de la matrice\n");
			printf(" exp / ^        |              Y = scalaire (*entier positif seulement!*)\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" déterminant    | Calcule le déterminant d'une matrice.\n");
			printf(" dét / det / d  |  > 'X', où X = numéro ou nom de la matrice\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" inverser       | Trouve la matrice inverse d'une matrice.\n");
			printf(" inv / i        |  > 'X', où X = numéro ou nom de la matrice\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" aide / liste   | Affiche ce message.\n");
			printf("----------------|-------------------------------------------------------------\n");
			printf(" quitter / q    | Ferme le programme.\n");
			
			printf("\nSauf spécification contraire:\n");
			printf("  > Les numéros de matrice sont les chiffres de 0 à 9.\n");
			printf("  > Les scalaires peuvent être des nombres entiers ou décimaux, \n");
			printf("    positifs ou négatifs.\n");
			printf("  > L'ordre des paramètres doit être respecté et ceux-ci doivent toujours\n");
			printf("    être précédés par leur commande. (exemple: \"+ 1 2\", et non \"1 + 2\")\n");
		}

		else if (!strcmp(cmd[0], "quitter") || !strcmp(cmd[0], "q") || !strcmp(cmd[0], "fermer"))
		//Fermeture du programme:
		{quitter = 1; printf("\n");}

		else if (!strcmp(cmd[0], "(null)")) {} //il ne se passe rien

		else
		{printf("Ce n'est pas une commande valide.\n");}

		//Prépare le prochain input:
		if (!quitter)
		{printf("\n--> ");}
	} //while !quitter (main loop)
}
