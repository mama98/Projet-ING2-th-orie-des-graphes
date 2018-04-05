#ifndef LABYBASE_H_INCLUDED
#define LABYBASE_H_INCLUDED

#include "sommet.h"

#include <vector>
#include <string>
#include <iostream>

class Labybase
{
    /// Ces attributs sont utilisables directement par la classe
    /// d�riv�e Labyrinthe : vous n'avez pas besoin d'un "get_sommets"...
    protected:
        // L'ensemble des sommets du graphe
        std::vector<Sommet> m_sommets;

        // Combien il y en a, m�me valeur que m_sommets.size()
        int m_ordre;

        // L'indice (dans le vecteur m_sommets) des sommets entr�e et sortie
        int m_entree;
        int m_sortie;

    /// M�thodes publiques utilisables
    public:

        // Construit un labyrinthe sur la base du nom de fichier
        Labybase(const std::string& nom_fichier);

        // Affiche graphiquement le labyrinthe avec des X au niveau des sommets marqu�s
        void afficher() const;

        // Retourne une cha�ne de format (lig,col) repr�sentant la position du sommet d'indice idx
        std::string coords(int idx) const;

        // Retourne une r�f�rence (l'objet est modifiable) au sommet d'indice idx
        Sommet &get_sommet(int idx);

        // Retourne l'ordre du graphe, c�d. le nombre de sommets
        int get_ordre() const;

        // Met � false l'attribut m_marque de tous les sommets du graphe
        void reset_marquages();


    /// Les m�thodes suivantes concernent la classe de Labybase
    /// vous n'avez PAS � les utiliser pour d�rouler les
    /// algos de parcours � impl�menter dans la classe Labyrinthe
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
    /// vous n'avez PAS � les utiliser pour d�rouler les
    /// algos de parcours � impl�menter dans la classe Labyrinthe
    private:
        int m_nblig, m_nbcol;
};


#endif // LABYBASE_H_INCLUDED
