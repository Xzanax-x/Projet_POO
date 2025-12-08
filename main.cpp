#include <iostream>
#include <string>
#include "Jeu.hpp"
// Point d'entrée du programme : sélection du mode et lancement du jeu.

int main(int argc, char* argv[]) {

    // Vérifie que l'utilisateur a fourni au moins 2 arguments :
    // - le fichier d'entrée
    // - le mode d'exécution (console ou gui)
    if (argc < 3) {
        std::cerr << "Usage : " << argv[0]
                  << " <fichier_entree> <mode> [nbIterations]\n";
        std::cerr << "mode = console | gui\n";
        return 1; // Arguments insuffisants → arrêt du programme.
    }

    std::string fichierEntree = argv[1]; // Chemin du fichier initial
    std::string mode = argv[2];          // Mode souhaité par l'utilisateur
    int nbIter = 100;                    // Valeur par défaut : 100 itérations

    // Si l'utilisateur fournit un 3e argument, on l'interprète comme nb d’itérations.
    if (argc >= 4) {
        nbIter = std::stoi(argv[3]);
    }

    try {
        Jeu jeu(nbIter);                             // Création de l'objet Jeu
        jeu.chargerDepuisFichier(fichierEntree);     // Chargement de la grille initiale

        // Sélection du mode d'exécution
        if (mode == "console") {
            jeu.executerModeConsole(fichierEntree);  // Mode texte
        } else if (mode == "gui") {
            jeu.executerModeGraphique();             // Mode graphique SFML
        } else {
            std::cerr << "Mode inconnu : " << mode
                      << " (utiliser console ou gui)\n";
            return 1; // Mode non reconnu
        }

    } catch (const std::exception& e) {
        // Capture et affichage des erreurs (ex : fichier introuvable)
        std::cerr << "Erreur : " << e.what() << "\n";
        return 1;
    }

    return 0; // Fin du programme sans erreur
}
