# Projet_POO
GUIDE D’UTILISATION DE L’APPLICATION – JEU DE LA VIE

Ce projet propose une implémentation complète du Jeu de la vie de Conway en C++. L’application fonctionne selon deux modes : un mode console qui génère les itérations dans des fichiers texte, et un mode graphique utilisant la bibliothèque SFML pour afficher l’évolution de la grille en temps réel.

1. Pré-requis

Pour utiliser l’application, les éléments suivants doivent être installés sur la machine :

Un compilateur compatible C++17 (g++)

La bibliothèque SFML (version graphique)

L’outil de compilation make

Sur une distribution Linux (Ubuntu, Mint…), SFML peut être installé via la commande :

sudo apt-get install libsfml-dev

2. Compilation du projet

Le projet est fourni avec un Makefile permettant de compiler l’ensemble des fichiers source.

Pour compiler le programme :

make

Pour supprimer les fichiers objets générés :

make clean

Une fois la compilation terminée, un exécutable nommé « main » est créé.

3. Exécution de l'application

La commande générale pour exécuter l’application est la suivante :

./main fichier_entree mode nombreIterations

Deux modes sont disponibles :

A. Mode console
Ce mode génère un dossier contenant le résultat de chaque itération sous forme de fichiers texte.

Exemple :

./main input.txt console 50

L’exécution crée le dossier :
input.txt_out
qui contient les fichiers :
iter_0.txt, iter_1.txt, iter_2.txt, …

Chaque fichier représente une génération.

B. Mode graphique
Ce mode ouvre une fenêtre SFML permettant d’observer l’évolution du Jeu de la vie.

Exemple :

./main input.txt gui 100

La fenêtre reste affichée jusqu’à fermeture manuelle.
L’évolution s’arrête automatiquement si :

Le nombre d’itérations demandé est atteint

La grille devient stable

4. Format du fichier d’entrée

Le fichier d’entrée doit suivre le format suivant :

largeur hauteur
lignes comportant des 0 et des 1

Motif oscillateur “Blinker”:

5 5
1 1 1 1 1
1 0 0 0 1
1 0 1 0 1
1 0 0 0 1
1 1 1 1 1


Dans ce format :
1 = cellule vivante
0 = cellule morte

5. Architecture générale

L’application repose sur une architecture orientée objet organisée autour des éléments suivants :

La classe Jeu, qui gère le déroulement du programme et l’enchaînement des itérations.

La classe Grille, qui représente la grille complète et assure la mise à jour de l’ensemble des cellules.

La classe Cellule, qui représente une cellule individuelle.

L’interface EtatCellule, permettant de définir les comportements des cellules.

Les classes EtatVivant et EtatMort, dérivées de CellState.

L’interface Regle, représentant le calcul d’évolution.

La classe RegleDeVie, qui applique les règles du Jeu de la vie.

La classe RenduGraphique, chargée de l’affichage SFML.

Cette architecture garantit un découplage clair entre la logique métier et l’affichage.

6. Fonctionnement du mode graphique

En mode graphique :

Chaque cellule est affichée à l’écran selon sa position.

La mise à jour de la grille est effectuée automatiquement selon un délai prédéfini (environ 150 ms).

La fenêtre reste active jusqu’à ce qu’elle soit fermée.

Les cellules vivantes sont affichées visuellement, tandis que les cellules mortes ne sont pas dessinées.


7. Remarques techniques

Un message tel que “vertical sync not supported” peut apparaître sur certaines machines virtuelles ; il n’empêche pas l’exécution du programme.

L’affichage graphique varie selon la taille de la grille et du zoom appliqué.

Le code respecte les règles du polymorphisme, de l’héritage, des interfaces et des principes de conception orientée objet.
