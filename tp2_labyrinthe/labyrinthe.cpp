#include "labyrinthe.h"

// Construit un labyrinthe sur la base du nom de fichier
// appelle directement le constructeur de la classe mère
Labyrinthe::Labyrinthe(const std::string& nom_fichier) :
    Labybase(nom_fichier)
{   }

// Exemple de parcours de tous les sommets du graphe dans l'ordre de leur indice
void Labyrinthe::affichage_donnees()
{
    std::cout << std::endl;

    std::cout << "Le labyrinthe a " << m_ordre << " sommets" << std::endl;

    std::cout << "Le sommet entree est a l'indice " << m_entree
                  << " coords" << coords(m_entree) << std::endl;

    std::cout << "Le sommet sortie est a l'indice " << m_sortie
                  << " coords" << coords(m_sortie) << std::endl;

    std::cout << std::endl << "Liste de tous les sommets : " << std::endl;
    for (int idx=0; idx<m_ordre; ++idx)
    {
        Sommet& s = m_sommets[idx];

        std::cout << "sommet indice " << idx << " coords" << coords(idx)
                    << (s.m_marque ? " X" : "  ") << (s.m_carac ? s.m_carac : ' ') << " adjacents: ";

        /// POUR REALISER LES ALGORITHMES DE PARCOURS VOUS DEVEZ BIEN COMPRENDRE CES 3 LIGNES
        for (int a=0; a<s.m_nbadjacents; ++a)
        {
            int ida = s.m_adjacents[a];
            std::cout << ida << " ";
        }

        if (s.m_nbadjacents==0)
            std::cout << "Aucun";

        std::cout << std::endl;
    }
    std::cout << std::endl;

    /**
    // La même chose avec des accesseurs et une boucle for in (selon votre préférence)
    std::cout << std::endl << "Liste de tous les sommets : " << std::endl;
    for (int idx=0; idx<get_ordre(); ++idx)
    {
        Sommet& s = get_sommet(idx);

        std::cout << "sommet indice " << idx << " coords" << coords(idx)
                    << (s.est_marque() ? " X" : "  ") << (s.get_carac() ? s.get_carac() : ' ') << " adjacents: ";

        for ( auto ida : s.get_adjacents() )
            std::cout << ida << " ";

        if ( s.get_adjacents().size()==0 )
            std::cout << "Aucun";

        std::cout << std::endl;
    }
    std::cout << std::endl;
    */

}


/// ICI VOS METHODES ...

void Labyrinthe::composantes_connexes() //méthode permettant d'afficher les composantes connexes du graphe
{
    std::vector<int> sommets_connexes; //vecteur de sommet stockant une composantes connexe
    for(int i=0;i<m_ordre;i++)
    {
        sommets_connexes.clear();
        if(get_sommet(i).est_marque()==0) //remplissage du vecteur et marquage des sommets parcourus
        {
            get_sommet(i).set_marque(1);
            sommets_connexes.push_back(i);

            for(int j=0;j<sommets_connexes.size();j++) //parcours des sommets adjacents aux sommets remplis dans le vecteur
            {
                for(int k=0;k<get_sommet(sommets_connexes[j]).get_adjacents().size();k++)
                {
                    if(get_sommet(get_sommet(sommets_connexes[j]).get_adjacents()[k]).est_marque()==0)
                    {
                        sommets_connexes.push_back(get_sommet(sommets_connexes[j]).get_adjacents()[k]);
                        get_sommet(get_sommet(sommets_connexes[j]).get_adjacents()[k]).set_marque(1);
                    }
                }
            }
        }

        if(sommets_connexes.size()!=0)
        {
            std::cout<<"Une composantes connexe du labyrinthe est: "; //affichage de toutes les composantes connexes
            for(int i=0;i<sommets_connexes.size();i++)
            {
                std::cout<<sommets_connexes[i]<<" ";

            }
        std::cout<<std::endl;
        }
    }
}

