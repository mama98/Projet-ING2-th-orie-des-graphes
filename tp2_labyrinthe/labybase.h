#ifndef LABYBASE_H_INCLUDED
#define LABYBASE_H_INCLUDED

#include "sommet.h"

#include <vector>
#include <string>
#include <iostream>

class Labybase
{
    /// Ces attributs sont utilisables directement par la classe
    /// dérivée Labyrinthe : vous n'avez pas besoin d'un "get_sommets"...
    protected:
        // L'ensemble des sommets du graphe
        std::vector<Sommet> m_sommets;

        // Combien il y en a, même valeur que m_sommets.size()
        int m_ordre;

        // L'indice (dans le vecteur m_sommets) des sommets entrée et sortie
        int m_entree;
        int m_sortie;

    /// Méthodes publiques utilisables
    public:

        // Construit un labyrinthe sur la base du nom de fichier
        Labybase(const std::string& nom_fichier);

        // Affiche graphiquement le labyrinthe avec des X au niveau des sommets marqués
        void afficher() const;

        // Retourne une chaîne de format (lig,col) représentant la position du sommet d'indice idx
        std::string coords(int idx) const;

        // Retourne une référence (l'objet est modifiable) au sommet d'indice idx
        Sommet &get_sommet(int idx);

        // Retourne l'ordre du graphe, càd. le nombre de sommets
        int get_ordre() const;

        // Met à false l'attribut m_marque de tous les sommets du graphe
        void reset_marquages();


    /// Les méthodes suivantes concernent la classe de Labybase
    /// vous n'avez PAS à les utiliser pour dérouler les
    /// algos de parcours à implémenter dans la classe Labyrinthe
    private:
        void verif_acces(int idx) const;
        void verif_acces(int lig, int col) const;
        int index(int lig, int col) const;
        int ligne(int idx) const;
        int colonne(int idx) const;
        int index_haut(int idx) const;
        int index_bas(int idx) const;
        int index_gauche(int idx) const;
        int index_droite(int idx) const;

    /// Les attributs suivants concernent la classe de Labybase
    /// vous n'avez PAS à les utiliser pour dérouler les
    /// algos de parcours à implémenter dans la classe Labyrinthe
    private:
        int m_nblig, m_nbcol;
};


#endif // LABYBASE_H_INCLUDED
