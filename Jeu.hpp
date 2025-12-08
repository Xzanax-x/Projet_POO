#pragma once
// Empêche plusieurs inclusions du fichier.

#include <string>
#include <vector>
#include "Grille.hpp"
#include "Regle.hpp"
#include "RegleDeVie.hpp"
#include "RenduGraphique.hpp"
// Le Jeu coordonne la grille, la règle d'évolution et les modes d'exécution.

class Jeu {
private:
    Grille grille;            // Grille contenant l'ensemble des cellules
    RegleDeVie regle;         // Règle appliquée à chaque génération (Conway)
    int nbIterationsMax;      // Limite d'itérations de la simulation

public:
    Jeu(int nbIter = 100);    // Initialise le jeu avec un nombre max d'itérations

    void chargerDepuisFichier(const std::string& chemin);
    // Charge l'état initial de la grille depuis un fichier texte.

    void executerModeConsole(const std::string& fichierEntree);
    // Produit les états successifs dans des fichiers texte.

    void executerModeGraphique();
    // Lance l'affichage SFML et anime l'évolution du jeu.

    Grille& obtenirGrille();                  // Accès modifiable à la grille
    const Grille& obtenirGrille() const;      // Accès en lecture seule

private:
    bool estStable(const std::vector<std::vector<int>>& precedent,
                   const std::vector<std::vector<int>>& courant) const;
    // Vérifie si deux générations consécutives sont identiques (motif stable).
};
