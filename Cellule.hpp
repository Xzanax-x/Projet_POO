#pragma once
// Empêche les inclusions multiples du fichier.

#include "EtatCellule.hpp"
// La cellule manipule un pointeur vers l'état de manière polymorphique.

class Cellule {
private:
    int x;                     // Coordonnée horizontale
    int y;                     // Coordonnée verticale
    EtatCellule* etat;         // État de la cellule (vivante/morte), via polymorphisme

public:
    Cellule();                                     // Constructeur par défaut : cellule morte en (0,0)
    Cellule(int x, int y, EtatCellule* e);         // Constructeur personnalisé
    Cellule(const Cellule& autre);                 // Copie profonde (utilise cloner())
    Cellule& operator=(const Cellule& autre);      // Affectation : copie profonde + gestion mémoire
    ~Cellule();                                    // Libère l’état (évite les fuites)

    bool estVivante() const;                       // Indique si la cellule est vivante

    void definirEtat(EtatCellule* e);              // Change l’état en détruisant l’ancien
    EtatCellule* obtenirEtat() const;              // Renvoie l’état actuel

    int obtenirX() const { return x; }             // Accès à la position X
    int obtenirY() const { return y; }             // Accès à la position Y
};
