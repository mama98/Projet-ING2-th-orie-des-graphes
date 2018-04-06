#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include "Sommet.h"
#include "Arete.h"

class Graphe

{
 public:
     Arete m_mat;
     int m_ordre;
     Arete *arbre;
     int m_ref;
     int m_aretes;
     ///Pour Djikstra
        int **m_adj;

     Graphe();
    std::vector<Arete> m_AR;
     ~Graphe();
     void Kruskal();
     void Djikstra();
     void Lire_fichier_Djikstra( std::string filename);
     void sauvegarder(std::string filename);
     void allouer (int aretes);
     void Lire_fichier(std::string filename);
     void afficher();

};

#endif // GRAPHE_H_INCLUDED
