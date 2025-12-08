#pragma once
// Empêche les inclusions multiples.

#include <vector>
#include <string>
#include "Cellule.hpp"
#include "Regle.hpp"
// La grille contient un ensemble de cellules et applique une règle d’évolution.

class Grille {
private:
    int largeur;                                   // Nombre de colonnes
    int hauteur;                                   // Nombre de lignes
    std::vector<std::vector<Cellule>> cellules;    // Matrice 2D de cellules

public:
    Grille();                                      // Constructeur par défaut
    Grille(int larg, int haut);                    // Constructeur avec dimensions
    Grille(const Grille& autre);                   // Copie profonde
    Grille& operator=(const Grille& autre);        // Affectation profonde
    ~Grille() = default;                           // Pas d’allocation dynamique directe

    void initialiserDepuisFichier(const std::string& chemin);
    // Lit un fichier et construit la grille avec les bons états.

    int obtenirLargeur() const { return largeur; } // Accès largeur
    int obtenirHauteur() const { return hauteur; } // Accès hauteur

    int compterVoisinesVivantes(int x, int y) const;
    // Comptage des cellules vivantes autour d’une position (x,y).

    void mettreAJour(const Regle& regle);
    // Applique la règle d’évolution à toute la grille (une génération).

    const std::vector<std::vector<Cellule>>& obtenirCellules() const;
    // Permet l’accès en lecture aux cellules (pour l’affichage, etc.)

    std::vector<std::vector<int>> obtenirMatriceEtats() const;
    // Retourne une matrice d'entiers indiquant l’état (0/1) de chaque cellule.
};
