#include "grman/grman.h"
#include <iostream>
#include "sommet.h"
#include "graph.h"
#include <allegro.h>


using namespace std;
int main()
{

    string d;
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
    BITMAP *page, *decor, *f1, *f2, *f3, *m1, *m2, *m3, *m4;
    int fin;

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;


   // string fichier;
   // cout<<" nom de fichier : trophique1.txt"<<endl;
   // cin>>fichier;

    //g.Lire_fichier(fichier);
   // g.afficher_fichier();
   /// g.make_example();



    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {


        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

    g.menu();

    }


    grman::fermer_allegro();


    return 0;
}
END_OF_MAIN();


