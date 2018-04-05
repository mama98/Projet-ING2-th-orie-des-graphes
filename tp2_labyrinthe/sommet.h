#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>

class Sommet
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Labybase;
    friend class Labyrinthe;

    private:

        // Liste des sommets adjacents
        // ( techniquement : vecteur des indices des adjacents )
        std::vector<int> m_adjacents;

        // Combien il y a d'adjacents, même valeur que m_adjacents.size()
        int m_nbadjacents;

        // Booléen marqué pour les algos de parcours
        bool m_marque;

        // Caractère à afficher (méthode afficher de labyrinthe)
        // Caractère '\0' par défaut (rien)
        char m_carac;

    public:

        // Pour que Labybase fonctionne il faut un constructeur de Sommet par défaut
        Sommet();

        // Il est possible de ne pas utiliser ces
        // accesseurs dans les méthodes de la classe
        // amie Labyrinthe : l'accès direct aux attributs
        // est légitime.
        const std::vector<int>& get_adjacents() const;
        bool est_marque() const;
        void set_marque(bool marque);
        char get_carac() const;
        void set_carac(char c);

        // Les méthodes suivantes ne sont en principe
        //utiles que pour la classe de base Labybase
        void ajouter_adjacent(int idx);
        bool est_adjacent_a(int idx) const;
};


#endif // SOMMET_H_INCLUDED
