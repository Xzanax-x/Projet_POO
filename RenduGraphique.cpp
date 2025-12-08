#include "RenduGraphique.hpp"

// Initialise la fenêtre SFML en fonction de la taille de la grille et des cellules.
RenduGraphique::RenduGraphique(int taille, int largeur, int hauteur)
    : fenetre(sf::VideoMode(largeur * taille, hauteur * taille), "Jeu de la vie"),
      tailleCellule(taille) {
    // Pas de limitation de framerate pour éviter des warnings sur certaines VM.
}

// Vérifie si la fenêtre graphique est toujours ouverte.
bool RenduGraphique::estOuverte() const {
    return fenetre.isOpen();
}

// Gère les événements SFML (ex : fermeture de la fenêtre).
bool RenduGraphique::traiterEvenements() {
    sf::Event event;
    while (fenetre.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            fenetre.close();
            return false;  // Signale que la fenêtre est fermée.
        }
    }
    return true;
}

// Affiche la grille à l’écran : chaque cellule vivante est dessinée comme un carré.
void RenduGraphique::afficher(const Grille& grille) {
    fenetre.clear();  // Efface l'écran avant un nouveau rendu.

    // Forme graphique représentant une cellule vivante.
    sf::RectangleShape formeCellule(
        sf::Vector2f(static_cast<float>(tailleCellule - 1),
                     static_cast<float>(tailleCellule - 1)));

    const auto& cellules = grille.obtenirCellules();
    int larg = grille.obtenirLargeur();
    int haut = grille.obtenirHauteur();

    // Parcourt la grille et dessine uniquement les cellules vivantes.
    for (int x = 0; x < larg; ++x) {
        for (int y = 0; y < haut; ++y) {
            if (cellules[x][y].estVivante()) {
                formeCellule.setFillColor(sf::Color(230, 180, 200)); // Couleur choisie
                formeCellule.setPosition(
                    static_cast<float>(x * tailleCellule),
                    static_cast<float>(y * tailleCellule)
                );
                fenetre.draw(formeCellule);  // Dessin de la cellule vivante.
            }
        }
    }

    fenetre.display();  // Rafraîchit l’affichage.
}
