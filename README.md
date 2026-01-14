# calculatrice-matrices

Une calculatrice de matrices de base pour le Terminal.

Programmée en C par Nicolas Audette.

## Installation
Compilez le programme avec la commande `gcc calc-mat.c -o calc-mat -lm`.

Démarrez le programme depuis un terminal avec `./calc-mat`.

Ce programme se compile aussi facilement pour Windows, puisque stdio.h, string.h et math.h sont les seules "dépendances" du programme.

## Utilisation
Une fois le programme démarré, entrez la commande `aide` pour afficher la liste des commandes acceptées.

Vous pouvez entrer `créer NUM` pour créer la matrice NUM, où NUM est un chiffre de 1 à 9. Entrez ensuite `afficher NUM` pour en voir le contenu.

Vous pouvez enregistrer vos matrices en entrant `enregistrer NUM`, afin de pouvoir les réutiliser plus tard (avec `ouvrir NUM`).

Les opérations suivantes sont supportées:
- Addition / Soustraction
- Multiplication matricielle
- Multiplication par un scalaire
- Puissance
- Inversion
- Transposition
- Déterminant
