#ifndef LABYRINTHE_H_INCLUDED
#define LABYRINTHE_H_INCLUDED

#include "labybase.h"

/// La classe Labyrinthe est celle que vous devez compléter
/// en lui ajoutant des méthodes (parcours_DFS, parcours_BFS ...)
class Labyrinthe : public Labybase
{
    public:

        // Construit un labyrinthe sur la base du nom de fichier
        Labyrinthe(const std::string& nom_fichier);

        // Exemple de parcours/affichage de tous les sommets du graphe dans l'ordre de leur indice
        void affichage_donnees();

        /// ICI VOS METHODES ...
        void composantes_connexes();
};

#endif // LABYRINTHE_H_INCLUDED
