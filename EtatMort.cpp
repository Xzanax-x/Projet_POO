#include "EtatMort.hpp"
// Implémentation de l'état "mort" d'une cellule.

bool EtatMort::estVivante() const {
    return false;  
    // Une cellule morte n'est jamais vivante : renvoie toujours false.
}

EtatCellule* EtatMort::cloner() const {
    return new EtatMort(*this);
    // Permet de dupliquer correctement l'état (copie polymorphique).
    // Utilisé lors des copies de cellules pour garantir une copie profonde.
}
