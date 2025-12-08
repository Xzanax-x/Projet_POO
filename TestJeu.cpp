#include <iostream>
#include <vector>
#include "Jeu.hpp"
#include "RegleDeVie.hpp"
#include "Grille.hpp"

using namespace std;

// --------------------------------------------------
// MATRICE ATTENDUE POUR L'ITÉRATION 5
// Définie en dur pour valider le comportement du programme.
// --------------------------------------------------
vector<vector<int>> matriceAttendue5 = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,1,1,0,0,1,1,0,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,0,1,1,0,0,1,1,0,0},
    {0,0,0,0,1,1,0,0,0,0}
};

// --------------------------------------------------
// FONCTION DE COMPARAISON DE MATRICES
// Vérifie l'égalité stricte entre deux matrices 2D.
// --------------------------------------------------
bool matricesEgales(const vector<vector<int>>& a,
                    const vector<vector<int>>& b) {

    if (a.size() != b.size()) return false;        // Vérifie les dimensions
    if (a[0].size() != b[0].size()) return false;

    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[0].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;  // Vérifie chaque case
        }
    }
    return true;
}

// --------------------------------------------------
// PROGRAMME DE TEST UNITAIRE
// Exécute 5 itérations et compare avec la matrice attendue.
// --------------------------------------------------
int main() {
    try {
        Jeu jeu(10);                                // Jeu limité à 10 itérations
        jeu.chargerDepuisFichier("input.txt");      // Charge l'état initial

        Grille& grille = jeu.obtenirGrille();
        RegleDeVie regle;                           // Règle de Conway

        // Applique 5 mises à jour successives
        for (int i = 0; i < 5; ++i) {
            grille.mettreAJour(regle);
        }

        // Récupère la grille calculée
        vector<vector<int>> matriceObtenue = grille.obtenirMatriceEtats();

        // Compare la matrice obtenue avec la matrice attendue
        if (matricesEgales(matriceObtenue, matriceAttendue5)) {
            cout << "TEST OK : L’itération 5 est correcte." << endl;
            return 0;
        } else {
            cout << "TEST ECHEC : La matrice de l’itération 5 ne correspond pas à la matrice attendue." << endl;
            return 1;
        }

    } catch (exception& e) {
        // Gère les erreurs éventuelles (ex : fichier introuvable)
        cout << "ERREUR pendant le test : " << e.what() << endl;
        return 2;
    }
}
