#include "Jeu.hpp"
#include <fstream>
#include <SFML/System.hpp>
#include <cstdlib>  // system() pour créer un dossier en mode console

// Initialise le jeu avec un nombre maximum d’itérations.
Jeu::Jeu(int nbIter)
    : grille(), regle(), nbIterationsMax(nbIter) {}

// Charge l’état initial de la grille à partir d’un fichier texte.
void Jeu::chargerDepuisFichier(const std::string& chemin) {
    grille.initialiserDepuisFichier(chemin);
}

// Vérifie si deux matrices d’états sont identiques (motif stable).
bool Jeu::estStable(const std::vector<std::vector<int>>& precedent,
                    const std::vector<std::vector<int>>& courant) const {
    return precedent == courant;
}

// --- MODE CONSOLE ---
// Génère un dossier contenant un fichier pour chaque itération.
void Jeu::executerModeConsole(const std::string& fichierEntree) {
    std::string dossierSortie = fichierEntree + "_out";
    system(("mkdir -p " + dossierSortie).c_str());  // Création du dossier

    std::vector<std::vector<int>> precedent = grille.obtenirMatriceEtats();

    for (int iter = 0; iter < nbIterationsMax; ++iter) {
        // Création du fichier iter_X.txt
        std::string nomFichier = dossierSortie + "/iter_" + std::to_string(iter) + ".txt";
        std::ofstream out(nomFichier);

        // Écrit les dimensions de la grille
        out << grille.obtenirHauteur() << " " << grille.obtenirLargeur() << "\n";

        // Écrit l’état actuel de chaque cellule (0 ou 1)
        const auto& cellules = grille.obtenirCellules();
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            for (int x = 0; x < grille.obtenirLargeur(); ++x) {
                out << (cellules[x][y].estVivante() ? 1 : 0) << " ";
            }
            out << "\n";
        }

        // Mise à jour de la grille selon la règle de Conway
        grille.mettreAJour(regle);
        auto courant = grille.obtenirMatriceEtats();

        // Arrêt anticipé si la grille est stable
        if (estStable(precedent, courant)) {
            break;
        }

        precedent = courant;
    }
}

// --- MODE GRAPHIQUE (SFML) ---
// Affiche la grille et anime les itérations dans une fenêtre SFML.
void Jeu::executerModeGraphique() {
    RenduGraphique rendu(150, grille.obtenirLargeur(), grille.obtenirHauteur());

    std::vector<std::vector<int>> precedent = grille.obtenirMatriceEtats();
    int iter = 0;
    bool evolutionTerminee = false;
    const int DELAI_MS = 300;  // Délai entre deux frames

    while (rendu.estOuverte()) {
        if (!rendu.traiterEvenements()) break; // Gestion des événements SFML

        if (!evolutionTerminee && iter < nbIterationsMax) {
            rendu.afficher(grille);             // Affiche la grille
            sf::sleep(sf::milliseconds(DELAI_MS));

            grille.mettreAJour(regle);          // Évolution d’une génération
            auto courant = grille.obtenirMatriceEtats();

            // Détection d’un motif stable
            if (estStable(precedent, courant)) {
                evolutionTerminee = true;
            }

            precedent = courant;
            ++iter;
        } else {
            // Lorsque l’évolution est terminée, on continue d’afficher la grille finale
            rendu.afficher(grille);
            sf::sleep(sf::milliseconds(DELAI_MS));
        }
    }
}

// Accès à la grille (modifiable)
Grille& Jeu::obtenirGrille() {
    return grille;
}

// Accès à la grille (lecture seule)
const Grille& Jeu::obtenirGrille() const {
    return grille;
}
