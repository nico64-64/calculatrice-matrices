# calculatrice-matrices

Une calculatrice de matrices de base pour le Terminal.

Programmée en C par Nicolas Audette.

## Installation
Vous pouvez utiliser les binaires de la release 1.0 ou construire vous-même le programme.

Pour construire le programme, compilez-le (sur Linux) avec la commande `gcc calc-mat.c -o calc-mat -lm`.

Démarrez le programme depuis un terminal avec `./calc-mat` (ou `calc-mat.exe` sur Windows).

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

## Version Windows
Vous devez spécifier à votre terminal d'utiliser la page de code 65001 (unicode/UTF-8) pour que le texte s'affiche correctement.
Entrez `chcp 65001` avant de démarrer le programme.
