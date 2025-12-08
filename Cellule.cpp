#include "Cellule.hpp"      // Inclusion du header de la classe Cellule
#include "EtatMort.hpp"     // Pour pouvoir créer un état mort par défaut
#include "EtatVivant.hpp"   // Pour gérer le cas où l’état est vivant

// --- Constructeur par défaut ---
// Initialise la cellule en position (0,0) avec un état mort.
// On crée explicitement un nouvel EtatMort, ce qui respecte le polymorphisme.
Cellule::Cellule()
    : x(0), y(0), etat(new EtatMort()) {}

// --- Constructeur personnalisé ---
// Permet d'initialiser une cellule avec une position (x_, y_)
// et un état déjà fourni sous forme de pointeur polymorphique.
Cellule::Cellule(int x_, int y_, EtatCellule* e)
    : x(x_), y(y_), etat(e) {}

// --- Constructeur de copie ---
// Copie profonde : on recopie les coordonnées,
// mais pour l’état on duplique l'objet réel grâce à cloner(),
// afin que chaque Cellule ait sa propre instance d'état.
Cellule::Cellule(const Cellule& autre)
    : x(autre.x), y(autre.y), etat(nullptr) {

    // Si l'autre cellule a un état, on le clone.
    if (autre.etat) {
        etat = autre.etat->cloner();   // Copie polymorphique
    } else {
        etat = new EtatMort();         // Par sécurité, on met un état mort
    }
}

// --- Opérateur d'affectation (=) ---
// Idem que le constructeur de copie, mais pour une cellule déjà existante.
// On évite les auto-copies et on gère proprement la mémoire.
Cellule& Cellule::operator=(const Cellule& autre) {
    if (this != &autre) {              // Vérifie qu'on n'affecte pas l'objet à lui-même
        x = autre.x;
        y = autre.y;

        delete etat;                   // Libère l’ancien état pour éviter les fuites
        etat = autre.etat
               ? autre.etat->cloner()  // Copie profonde via cloner()
               : new EtatMort();
    }
    return *this;
}

// --- Destructeur ---
// Libère l’état pour éviter les fuites mémoire.
// On détruit ici ce que l’on a alloué dans les constructeurs.
Cellule::~Cellule() {
    delete etat;
}

// --- Méthode estVivante() ---
// Retourne vrai si l’état existe et si cet état indique que la cellule est vivante.
// L'appel est délégué à l'objet EtatCellule pour respecter le polymorphisme.
bool Cellule::estVivante() const {
    return etat && etat->estVivante();
}

// --- Accesseur obtenirEtat() ---
// Renvoie directement le pointeur vers l’état (sans copie).
// Utile pour permettre à Grille ou à Regle d'interroger l’état courant.
EtatCellule* Cellule::obtenirEtat() const {
    return etat;
}

// --- Méthode definirEtat() ---
// Permet de changer l’état de la cellule.
// On supprime l'ancien état uniquement s'il est différent du nouvel objet,
// afin d'éviter un delete inutile ou dangereux.
void Cellule::definirEtat(EtatCellule* e) {
    if (etat != e) {
        delete etat;   // Libère l’ancien état
        etat = e;      // Remplace par le nouvel état (polymorphique)
    }
}
