#include "EtatVivant.hpp"
// Implémentation de l'état "vivant" d'une cellule.

bool EtatVivant::estVivante() const {
    return true;
    // Une cellule vivante renvoie toujours true.
}

EtatCellule* EtatVivant::cloner() const {
    return new EtatVivant(*this);
    // Permet de dupliquer l'état de manière polymorphique.
    // Utilisé pour garantir une copie profonde lors de la copie d'une cellule.
}

