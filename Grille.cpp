#include "Grille.hpp"
#include <fstream>
#include <stdexcept>
#include "EtatVivant.hpp"
#include "EtatMort.hpp"
#include "Regle.hpp"


// Constructeur par défaut : grille vide
Grille::Grille()
    : largeur(0), hauteur(0) {}

// Constructeur avec dimensions : initialise toutes les cellules à l'état mort
Grille::Grille(int larg, int haut)
    : largeur(larg), hauteur(haut),
      cellules(larg, std::vector<Cellule>(haut, Cellule(0, 0, new EtatMort()))) {}

// Constructeur de copie : copie profonde des cellules
Grille::Grille(const Grille& autre)
    : largeur(autre.largeur), hauteur(autre.hauteur),
      cellules(autre.largeur, std::vector<Cellule>(autre.hauteur)) {

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            cellules[x][y] = autre.cellules[x][y];
        }
    }
}

// Opérateur d'affectation : recopie dimensions et contenu de la grille
Grille& Grille::operator=(const Grille& autre) {
    if (this != &autre) {
        largeur = autre.largeur;
        hauteur = autre.hauteur;
        cellules.assign(largeur, std::vector<Cellule>(hauteur));

        for (int x = 0; x < largeur; ++x) {
            for (int y = 0; y < hauteur; ++y) {
                cellules[x][y] = autre.cellules[x][y];
            }
        }
    }
    return *this;
}

// Initialise la grille à partir d'un fichier texte (dimensions + états 0/1)
void Grille::initialiserDepuisFichier(const std::string& chemin) {
    std::ifstream in(chemin);
    if (!in) {
        throw std::runtime_error("Impossible d'ouvrir le fichier d'entree : " + chemin);
    }

    int hFichier, lFichier;
    in >> hFichier >> lFichier;

    hauteur = hFichier;
    largeur = lFichier;

    cellules.clear();
    cellules.resize(largeur, std::vector<Cellule>(hauteur));

    // Lecture de chaque cellule et création de l'état correspondant (vivant/mort)
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int v = 0;
            in >> v;
            EtatCellule* e = (v == 1)
                             ? static_cast<EtatCellule*>(new EtatVivant())
                             : static_cast<EtatCellule*>(new EtatMort());
            cellules[x][y] = Cellule(x, y, e);
        }
    }
}

// Compte le nombre de voisines vivantes autour de la cellule (x, y)
int Grille::compterVoisinesVivantes(int x, int y) const {
    int compteur = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // ignore la cellule elle-même
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur) {
                if (cellules[nx][ny].estVivante()) {
                    ++compteur;
                }
            }
        }
    }
    return compteur;
}

// Applique une règle d'évolution à toute la grille (une génération)
void Grille::mettreAJour(const Regle& regle) {
    std::vector<std::vector<Cellule>> prochaineGrille = cellules;

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            int nbVoisines = compterVoisinesVivantes(x, y);
            EtatCellule* etatCourant = cellules[x][y].obtenirEtat();
            EtatCellule* nouvelEtat = regle.calculerProchainEtat(etatCourant, nbVoisines);
            prochaineGrille[x][y].definirEtat(nouvelEtat);
        }
    }

    // Remplace la grille actuelle par la nouvelle génération
    cellules.swap(prochaineGrille);
}

// Accès en lecture à la matrice de cellules
const std::vector<std::vector<Cellule>>& Grille::obtenirCellules() const {
    return cellules;
}

// Retourne une matrice d'entiers 0/1 représentant l'état de chaque cellule
std::vector<std::vector<int>> Grille::obtenirMatriceEtats() const {
    std::vector<std::vector<int>> matrice(hauteur, std::vector<int>(largeur, 0));
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            matrice[y][x] = cellules[x][y].estVivante() ? 1 : 0;
        }
    }
    return matrice;
}
