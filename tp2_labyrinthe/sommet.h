#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>

class Sommet
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Labybase;
    friend class Labyrinthe;

    private:

        // Liste des sommets adjacents
        // ( techniquement : vecteur des indices des adjacents )
        std::vector<int> m_adjacents;

        // Combien il y a d'adjacents, m�me valeur que m_adjacents.size()
        int m_nbadjacents;

        // Bool�en marqu� pour les algos de parcours
        bool m_marque;

        // Caract�re � afficher (m�thode afficher de labyrinthe)
        // Caract�re '\0' par d�faut (rien)
        char m_carac;

    public:

        // Pour que Labybase fonctionne il faut un constructeur de Sommet par d�faut
        Sommet();

        // Il est possible de ne pas utiliser ces
        // accesseurs dans les m�thodes de la classe
        // amie Labyrinthe : l'acc�s direct aux attributs
        // est l�gitime.
        const std::vector<int>& get_adjacents() const;
        bool est_marque() const;
        void set_marque(bool marque);
        char get_carac() const;
        void set_carac(char c);

        // Les m�thodes suivantes ne sont en principe
        //utiles que pour la classe de base Labybase
        void ajouter_adjacent(int idx);
        bool est_adjacent_a(int idx) const;
};


#endif // SOMMET_H_INCLUDED
