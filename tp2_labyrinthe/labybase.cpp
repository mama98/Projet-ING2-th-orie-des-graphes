#include "labyrinthe.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


Labybase::Labybase(const std::string& nom_fichier)
{

    /// Tentative d'ouverture du fichier
    std::ifstream fic(nom_fichier.c_str());
    if ( !fic.is_open() )
        throw "Probleme ouverture fichier !";

    /// Construction de la matrice textuelle "image" du fichier
    std::vector<std::string> image;
    unsigned large_img = 0;
    unsigned haut_img  = 0;
    while ( fic.good() )
    {
        std::string ligne;
        getline(fic, ligne);

        if ( large_img && large_img!=ligne.size() )
            throw "Mauvais format fichier (1) !";

        large_img=ligne.size();

        image.push_back(ligne);
        ++haut_img;
    }

    /// Vérification de la taille de la matrice textuelle image
    if (large_img<3 || large_img%2==0 || haut_img<3 || haut_img%2==0 )
        throw "Mauvais format fichier (2) !";

    /// Calcul de la taille de la matrice de sommets => ordre du graphe
    m_nbcol = (large_img-1)/2;
    m_nblig = ( haut_img-1)/2;
    m_ordre = m_nblig * m_nbcol;

    /// Construction des sommets du Labybase à partir de la matrice textuelle image
    m_entree = m_sortie = -1;
    int idx=0;
    for (int lig=0; lig<m_nblig; ++lig)
        for (int col=0; col<m_nbcol; ++col)
        {
            // Ajout d'un sommet (vecteur m_sommets)
            Sommet s;

            // Ligne Image et Colonne Image
            int li = 2*lig+1;
            int ci = 2*col+1;

            // Détection des sommets d'entrée et de sortie
            if ( image[li][ci]=='I' ) m_entree = idx;
            if ( image[li][ci]=='O' ) m_sortie = idx;

            // Ajout des positions des sommets adjacents,
            // dans l'ordre haut, droite, bas, gauche
            if ( image[li-1][ci] == ' ' ) s.ajouter_adjacent( index_haut(idx) );
            if ( image[li][ci+1] == ' ' ) s.ajouter_adjacent( index_droite(idx) );
            if ( image[li+1][ci] == ' ' ) s.ajouter_adjacent( index_bas(idx) );
            if ( image[li][ci-1] == ' ' ) s.ajouter_adjacent( index_gauche(idx) );

            m_sommets.push_back(s);
            ++idx;
        }
}
/// Note : la gestion de fichiers corrompus est encore très partielle

void Labybase::afficher() const
{
    /// Reconstitution d'une matrice textuelle image (représentation graphique du graphe)

    // Calcul de la taille de la matrice textuelle image
    int large_img = 2*m_nbcol + 1;
    int haut_img  = 2*m_nblig + 1;

    // Déclarer et initialiser la "matrice" avec haut_img chaines de large_img espaces
    std::vector<std::string> image( haut_img, std::string(large_img, ' ') );

    // Fabrication de la "grille" à partir d'un patron périodique
    char patron[2][2] = {   {'+', '-'},
                            {'|', ' '} };

    for (int li=0; li<haut_img; ++li)
        for (int ci=0; ci<large_img; ++ci)
            image[li][ci] = patron[li%2][ci%2];


    /// Reset des cases image du labyrinthe
    for (int lig=0; lig<m_nblig; ++lig)
        for (int col=0; col<m_nbcol; ++col)
        {
            const Sommet& s = m_sommets[ index(lig, col) ];
            int li = 2*lig+1;
            int ci = 2*col+1;

            char c = ' ';

            if ( s.est_marque() )
                c = 'X';

            if ( s.get_carac() )
                c = s.get_carac();

            image[li][ci] = c;
        }

    /// Passages autour des cases marquées 'X' ou avec affichage
    for (int lig=0; lig<m_nblig; ++lig)
        for (int col=0; col<m_nbcol; ++col)
        {
            const Sommet &s = m_sommets[ index(lig, col) ];
            int li = 2*lig+1;
            int ci = 2*col+1;

            // Si ça passe vers le bas alors on efface le mur '-'
            if ( lig+1<m_nblig && s.est_adjacent_a( index(lig+1, col) ) )
                    image[li+1][ci] = image[li][ci]==image[li+2][ci] ? image[li][ci] : ' ';

            // Si ça passe vers la droite alors on efface le mur '|'
            if ( col+1<m_nbcol && s.est_adjacent_a( index(lig, col+1) ) )
                    image[li][ci+1] = image[li][ci]==image[li][ci+2] ? image[li][ci] : ' ';
        }


    /// Entrée et sortie
    image[2*ligne(m_entree)+1][2*colonne(m_entree)+1]='I';
    image[2*ligne(m_sortie)+1][2*colonne(m_sortie)+1]='O';


    /// Affichage de l'image finale
    std::cout << std::endl;
    for (const auto & ligne : image)
        std::cout << ligne << std::endl;

}

std::string Labybase::coords(int idx) const
{
    std::ostringstream oss;
    oss << "(" << ligne(idx) << "," << colonne(idx) << ")";
    return oss.str();
}

Sommet &Labybase::get_sommet(int idx)
{
    verif_acces(idx);
    return m_sommets[idx];
}

int Labybase::get_ordre() const
{
    return m_ordre;
}

void Labybase::reset_marquages()
{
    for (auto& s : m_sommets)
        s.set_marque(false);
}

void Labybase::verif_acces(int idx) const
{
    if ( idx<0 || idx>=get_ordre() )
        throw "Acces idx hors cadre !";
}

void Labybase::verif_acces(int lig, int col) const
{
    if ( lig<0 || lig>=m_nblig || col<0 || col>=m_nbcol )
        throw "Acces lig col hors cadre !";
}

int Labybase::index(int lig, int col) const
{
    verif_acces(lig, col);
    return m_nbcol*lig + col;
}

int Labybase::ligne(int idx) const
{
    verif_acces(idx);
    return idx/m_nbcol;
}

int Labybase::colonne(int idx) const
{
    verif_acces(idx);
    return idx%m_nbcol;
}

int Labybase::index_haut(int idx) const
{
    idx-=m_nbcol;
    verif_acces(idx);
    return idx;
}

int Labybase::index_bas(int idx) const
{
    idx+=m_nbcol;
    verif_acces(idx);
    return idx;
}

int Labybase::index_gauche(int idx) const
{
    --idx;
    verif_acces(idx);
    return idx;
}

int Labybase::index_droite(int idx) const
{
    ++idx;
    verif_acces(idx);
    return idx;
}
