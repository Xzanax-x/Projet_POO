#pragma once
// Empêche les inclusions multiples du fichier.

#include <SFML/Graphics.hpp>
#include "Grille.hpp"
// RenduGraphique est responsable de l'affichage graphique de la grille via SFML.

class RenduGraphique {
private:
    sf::RenderWindow fenetre;   // Fenêtre SFML où la grille est affichée
    int tailleCellule;          // Taille en pixels d’une cellule à l’écran

public:
    RenduGraphique(int tailleCellule, int largeur, int hauteur);
    // Initialise la fenêtre et configure la taille de l'affichage.

    bool estOuverte() const;
    // Indique si la fenêtre graphique est encore ouverte.

    bool traiterEvenements();
    // Gère les événements SFML (ex : fermeture de la fenêtre).

    void afficher(const Grille& grille);
    // Dessine la grille : chaque cellule vivante est représentée à l'écran.
};
