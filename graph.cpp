#include "graph.h"
#include <fstream>
using namespace std;
/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
   /// m_top_box.set_bg_color(BLEU);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;
    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}


/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(120,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(878,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    /// creation de la toolbox
    m_top_box.add_child(m_deleteS);
    m_deleteS.add_child(m_text_deleteS);
    m_deleteS.set_dim(115,40);
    m_deleteS.set_posx(0);
    m_deleteS.set_posy(0);
    m_deleteS.set_bg_color(ROUGE);
    m_text_deleteS.set_message("  SUPPRIMER S ");

    m_top_box.add_child(m_deleteA);
    m_deleteA.add_child(m_text_deleteA);
    m_deleteA.set_dim(115,40);
    m_deleteA.set_posx(0);
    m_deleteA.set_posy(40);
    m_deleteA.set_bg_color(ROUGECLAIR);
    m_text_deleteA.set_message("  SUPPRIMER A ");

    m_top_box.add_child(m_addS);
    m_addS.add_child(m_text_addS);
    m_addS.set_dim(115,40);
    m_addS.set_posx(0);
    m_addS.set_posy(80);
    m_addS.set_bg_color(BLEU);
    m_text_addS.set_message("  AJOUTER S ");

    m_top_box.add_child(m_addA);
    m_addA.add_child(m_text_addA);
    m_addA.set_dim(115,40);
    m_addA.set_posx(0);
    m_addA.set_posy(120);
    m_addA.set_bg_color(BLEUCLAIR);
    m_text_addA.set_message("  AJOUTER A ");

    m_top_box.add_child(m_save);
    m_save.add_child(m_text_save);
    m_save.set_dim(115,40);
    m_save.set_posx(0);
    m_save.set_posy(160);
    m_save.set_bg_color(ORANGE);
    m_text_save.set_message("  SAUVEGARDER  ");

    m_top_box.add_child(m_connexe);
    m_connexe.add_child(m_text_connexe);
    m_connexe.set_dim(115,40);
    m_connexe.set_posx(0);
    m_connexe.set_posy(200);
    m_connexe.set_bg_color(VIOLETCLAIR);
    m_text_connexe.set_message("  CONNEXE  ");

    m_top_box.add_child(m_evolution);
    m_evolution.add_child(m_text_evolution);
    m_evolution.set_dim(115,40);
    m_evolution.set_posx(0);
    m_evolution.set_posy(240);
    m_evolution.set_bg_color(VERT);
    m_text_evolution.set_message("  EVOLUTION ");

    m_top_box.add_child(m_reinitialisation);
    m_reinitialisation.add_child(m_text_reinitialisation);
    m_reinitialisation.set_dim(115,40);
    m_reinitialisation.set_posx(0);
    m_reinitialisation.set_posy(280);
    m_reinitialisation.set_bg_color(KAKICLAIR);
    m_text_reinitialisation.set_message("  REINITIALISER  ");

    m_top_box.add_child(m_return);
    m_return.add_child(m_text_return);
    m_return.set_dim(115,40);
    m_return.set_posx(0);
    m_return.set_posy(320);
    m_return.set_bg_color(VERTCLAIR);
    m_text_return.set_message("  RETOUR  ");

    m_top_box.add_child(m_exit);
    m_exit.add_child(m_text_exit);
    m_exit.set_dim(115,40);
    m_exit.set_posx(0);
    m_exit.set_posy(360);
    m_exit.set_bg_color(BLANC);
    m_text_exit.set_message("QUITTER");

}

void Graph ::Lire_fichier(string filename )
{
    /// ouverture du fichier en lecture
    ifstream fichier(filename.c_str(), ios::in);
    //int* temp=nullptr;
    string image;
    int indice_som =0;
    int x,y;
    int indice_edge;
    int som_in=0,som_out=0;
    int poids;
    double quantite;
    /// test d'ouverture de fichier
    if(fichier)
    {
        //temp=new int[m_ordre];
        m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
        fichier>>m_ordre;  /// on lit la première valeur du fichier qui est l'ordre.
        fichier>>m_aretes;
        for(int i=0; i<m_ordre; i++)
        {
            fichier>> indice_som>>quantite>> x >> y >>image;
            add_interfaced_vertex(indice_som, quantite, x, y,image);
        }
        int k=0;

        for(int j=0; j< m_aretes; j++)
        {
            fichier>>indice_edge>>som_in>>som_out>>poids;
            add_interfaced_edge(indice_edge, som_in, som_out, poids);
        }

        fichier.close();
    }
    else
    {
        cerr<<"Erreur. Ouverture de fichier impossible"<<endl;
    }
}

void Graph::Remplir_vect()
{
    vector<int> m_ligne;

    for(int b=0; b<m_ordre; b++)
    {
        m_ligne.push_back(0);
    }
    for(int a=0; a<m_ordre; a++)
    {
        m_vect.push_back(m_ligne);
    }

    for(int i=0; i<m_ordre; i++) //parcours de l'ordre (lignes de m_vec)
    {
        cout<<m_ordre<<endl;
        for(int r=0; r<m_ordre; r++) //parcours des éléments de la matrice
        {
            if(i==m_edges[r].get_from()) //si correspondance entre le départ de l'arête et le numéro de la ligne de m-vect
            {
                for(int j=0; j<m_ordre; j++)
                {
                    if(j==m_edges[i].get_to()) //on recherche la bonne colonne associée à l'arrivée
                    {
                        m_vect[i][j]=m_edges[i].m_weight;//on insère le poids de l'arête sur la ligne à la bonne colonn
                    }

                }
            }
        }
    }

    for(int y=0; y<m_ordre; y++)
    {
        for(int t=0; t<m_ordre; t++)
        {
            cout<<m_vect[y][t]<<" ";
        }
        cout<<endl;
    }

}
BITMAP * load_bitmap_check(char *nomImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage,NULL);
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}

void Graph :: menu()
{
    BITMAP  *page=NULL,*choix0=NULL,*choix1=NULL,*choix2=NULL,*choix3=NULL,*choix4=NULL;


    page=create_bitmap(SCREEN_W,SCREEN_H);
    choix0=load_bitmap("pics/darwin.bmp",NULL);


    blit( page,screen,0,0,0,0,SCREEN_W,SCREEN_H);



    choix1=load_bitmap("pics/darwin_t1.bmp",NULL);
    choix2=load_bitmap("pics/darwin_t2.bmp",NULL);
    choix3=load_bitmap("pics/darwin_t3.bmp",NULL);
    choix4=load_bitmap("pics/darwin_q.bmp",NULL);

    int choix=0;

    while(choix != 4 || !mouse_b&1 )
    {
        if( 403<=mouse_x && mouse_x<=858 && 51<=mouse_y && mouse_y<=163 )
        {
            choix=1;
            draw_sprite(page,choix1,0,0);
        }
        else if (465<=mouse_x && mouse_x<=922 && 207<= mouse_y && mouse_y<=324)
        {
            choix=2;
            draw_sprite(page,choix2,0,0);
        }
        else if ( 517<= mouse_x && mouse_x<= 965 && 381 <= mouse_y && mouse_y <=495)
        {
            choix=3;
            draw_sprite(page,choix3,0,0);
        }
        else if ( 618 <= mouse_x && mouse_x <= 951 && 628<= mouse_y && mouse_y<= 747)
        {
            choix=4;
            draw_sprite(page,choix4,0,0);
        }


        else
        {
            choix=0;
            draw_sprite(page,choix0,0,0);
        }



        draw_sprite(screen,page,0,0);
        rest(20);
        clear_bitmap(page);


        if(mouse_b&1 && choix<=4 && choix>=1)
        {
            switch(choix)
            {
            case 1:
            {
                choix=4;
                m_fichier="trophique1.txt";
                Lire_fichier(m_fichier);
                break;
            }
            case 2:
            {
                choix=4;
                m_fichier="trophique2.txt";
                Lire_fichier(m_fichier);
                break;
            }
            case 3:
            {
                choix=4;
                m_fichier="trophique3.txt";
                Lire_fichier(m_fichier);
                break;
            }
            case 4:
            {
                exit(1);
            }

            }

        }

    }
}

void Graph:: ajouterS()
{
    string image;
    int lien1,poids;
    double quantite;
    cout<<"le nom de l'animal a ajouter (ex:loup.bmp)"<<endl;
    cin>> image;

    cout<<"Saisir la taille de sa population:"<<endl;       ///blindage des valeurs trouvé sur: https://cpp.developpez.com/faq/cpp/?page=Manipulation-de-la-console#Comment-verifier-les-valeurs-saisies-avec-cin
    while ( ! ( cin >> quantite ) )
    {
        if ( cin.fail() )
        {
            cout << "Saisie incorrecte, recommencez : ";
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
    }
    cout<<" Veuillez saisir l'indice de l'image liee: "<<endl;
    cout<<"lien 1 :"<<endl;
    while ( ! ( cin >> lien1 ) )
    {
        if ( cin.fail() )
        {
            cout << "Saisie incorrecte, recommencez : ";
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
    }
    cout<<"poids de l'arc :"<<endl;
    while ( ! ( cin >> poids ) )
    {
        if ( cin.fail() )
        {
            cout << "Saisie incorrecte, recommencez : ";
            cin.clear();
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
    }
    int  a=m_vertices.size()+1;

    add_interfaced_vertex(0,quantite,0,0,image);
    for(map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        if(it->second.m_interface->m_img.get_pic_name()==image)
        {
            add_interfaced_edge(0,it->first,lien1,poids);
        }
    }
}

void Graph::AjouterA()
{
    int ind1,ind2;
    cout<<"saisir l'indice du prédateur à relier du graphe"<<endl;
    cin>>ind1;
    cout<<"saisir l'indice de la proie  à relier du graphe"<<endl;
    cin>>ind2;

    add_interfaced_edge(0, ind1,ind2, 0);

}

void Graph::supprimerA()
{
    int ind1,ind2;
    cout<<"saisir l'indice du predateur de l'arete que vous souhaitez supprimer"<<endl;
    cin>>ind1;
    cout<<"saisir l'indice de la proie de l'arete que vous souhaiitez supprimer"<<endl;
    cin>>ind2;

    for(map<int, Edge>::iterator et=m_edges.begin(); et!=m_edges.end(); et++)
    {
        if(et->second.get_from()==ind1 && et->second.get_to()==ind2)
        {
            test_remove_edge(et->first);
            break;
        }
    }

}

void Graph::supprimerS(int eidx)
{
    int num ;
    vector <int> vect_ind;

    for(map<int, Edge>::iterator et=m_edges.begin(); et!=m_edges.end(); et++)
    {
        if(et->second.get_from()==eidx || et->second.get_to()==eidx)
        {
            vect_ind.push_back(et->first);
        }
    }
    for(auto elem: vect_ind)
    {
        test_remove_edge(elem);
    }

    for(map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->first;
        it->second;
        if(it->first==eidx)
        {
            Vertex &remed=m_vertices.at(eidx);
            if(m_interface && remed.m_interface)
            {
                m_interface->m_main_box.remove_child(remed.m_interface->m_top_box);
            }
            m_vertices.erase( eidx );
            break;

        }
    }



}


void Graph::test_remove_edge(int eidx)
{
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
//         EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
//         m_interface->m_main_box.add_child(ei->m_top_edge);
//         m_edges[idx] = Edge(weight, ei);
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );
    m_nb_arcs--;
}

void Graph::retour()
{
    Graph g;
     g.menu();
    while(!m_interface->m_return.clicked())
    {
        g.update();
       grman::mettre_a_jour();


    }
}

void Graph::reinitialisation(string num)
{
        string backup;
        string nom;
        string extension;
        backup="backup";
        extension=".txt";
        nom=backup+num+extension;
        cout<<nom<<endl;
    ifstream fichier(nom);  // Flux de lecture
    ofstream flux(m_fichier); // Flux d'ecriture

   if(fichier)      ///Code de copier/coller trouvé sur https://openclassrooms.com/forum/sujet/copier-coller-un-fichier-avec-un-programme-en-c
   {
      string ligne;

      while(getline(fichier, ligne))
      {
            if(flux)
            {
                flux << ligne << endl;
            }
            else
            {
                cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
            }
      }
   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }



}

void Graph::Menu_afficher()
{
    BITMAP*page;
    BITMAP*decor;

    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    decor=load_bitmap("darwin.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver darwin.bmp");
        exit(EXIT_FAILURE);
    }

    while (!key[KEY_ESC])
    {
        // effacer buffer en appliquant décor  (pas de clear_bitmap)
        blit(decor,page,0,0,400,300,SCREEN_W,SCREEN_H);


        // affichage du buffer à l'écran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // la petite pause...
        rest(10);
    }

}

void Edge::set_fleches(float f)
{
    m_interface->m_top_edge.set_fleches(f);
}
void Graph::set_fleches()
{
    for(auto& elem : m_edges)
    {
        elem.second.set_fleches(elem.second.m_weight);
    }
}


void Graph::evolution()
{

    int k=0;


    std::map<int,Vertex>::iterator it3;

    int s=0;

    /// cherche de la proie (it3)
    for( std::map<int,Vertex>:: iterator it= m_vertices.begin(); it!=m_vertices.end(); it++) /// parcours tous les sommets
    {
        it->second.m_value; /// second -> vertex qui ont un attribut m_value

        for(std::map<int, Edge>:: iterator it2=m_edges.begin(); it2!=m_edges.end(); it2++) /// parcours des arcs
        {

            if(it->first == it2->second.m_from)/// arete de la proie qui vient evrs le predateur
            {
                s=it2->second.m_to;

                it3=m_vertices.find(s);

            }

            for( std::map<int,Vertex>::iterator it4=m_vertices.begin(); it4!=m_vertices.end(); it4++)
            {
                if(it4->first==s)
                {
                    k+=it2->second.m_weight*it4->second.m_value;
                }


            }
            it->second.m_value+=0.4*it->second.m_value*(1-(it->second.m_value/k)) ;
            for( std::map<int,Edge>::iterator it4 = m_edges.begin(); it4!=m_edges.end(); it4++) /// proie
            {
                if(it->first==it2->second.m_from)/// arete du predateur qui vient evrs le predateur
                {
                    it->second.m_value-=it2->second.m_weight*it4->second.m_weight;

                }

            }

        }
    }

}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;


    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    int a=m_interface->update();

    if(a==1)
    {

        int eidx;
        cout<<" Veuillez saisir l'indice du sommet a supprimer"<<endl;
        cin>> eidx;
        supprimerS(eidx);///suppression
    }
    if(a==2)
    {
        supprimerA();
    }
    if(a==3)
    {
        ajouterS(); ///ajouter
    }

    if(a==4)
    {
        AjouterA();
    }
    if(a==5)
    {
        Sauvegarder_fichier(m_fichier);

    }
    if(a==6)
    {
        //connexe
    }
    if(a==7)
    {
         m_evolution=true;
        evolution();
    }
    if(a==8)
    {
      if(m_fichier=="trophique1.txt")
      reinitialisation("1");
      if(m_fichier=="trophique2.txt")
      reinitialisation("2");
      if(m_fichier=="trophique3.txt")
      reinitialisation("3");
    }
    if(a==9)
    {
        retour();
    }

    if(a==10)
    {
        exit(1);
    }

    m_interface->update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

         this->set_fleches();

}

int GraphInterface::update()
{
    if(m_deleteS.clicked())
    {
        return 1;
    }
    if(m_deleteA.clicked())
    {
        return 2;
    }
    if(m_addS.clicked())
    {
        return 3;
    }
    if(m_addA.clicked())
    {
        return 4;
    }
    if(m_save.clicked())
    {
        return 5;
    }
    if(m_connexe.clicked())
    {
        return 6;
    }
     if(m_evolution.clicked())
    {
        return 7;
    }
      if(m_reinitialisation.clicked())
    {
        return 8;
    }
      if(m_return.clicked())
    {
        return 9;
    }
     if(m_exit.clicked())
    {
        return 10;
    }
}


void Graph::Sauvegarder_fichier(string filename )
{

    /// ouverture du fichier en écriture
    std::ofstream file(filename );

    /// test d'ouverture de fichier
    if(file)
    {
        file << m_vertices.size() << endl;
        file << m_edges.size()<< endl;

        for(map<int, Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            file<< it->first <<" "<<it->second.m_value << " "<<it->second.m_interface->m_top_box.get_posx() << " "<<it->second.m_interface->m_top_box.get_posy()<< " "<<it->second.m_interface->m_img.get_pic_name()<<endl;
        }
        for(map<int, Edge>::iterator et=m_edges.begin(); et!=m_edges.end(); et++)
        {
            file<<et->first<<" "<< et->second.get_from()<<" "<< et->second.get_to()<<" "<<et->second.get_weight()<<endl;
        }

        file.close();
    }
    else
    {
        cerr<<"Erreur. Ouverture de fichier impossible"<<endl;
    }
}


int Edge::get_from()
{
    return m_from;
}

int Edge::get_to()
{
    return m_to;
}

int Edge::get_weight()
{
    return m_weight;
}

int Vertex::get_indice()
{
    return m_indice;
}
void Vertex::set_indice(int indice)
{
    m_indice=indice;
}
/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{

    while ( m_vertices.find(idx)!=m_vertices.end() )
    {
        idx++;
    }

    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    vi->m_slider_value.set_value(value);
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    while ( m_edges.find(idx)!=m_edges.end() )
    {
        idx++;
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    ei->m_slider_weight.set_value(weight);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_edges[idx].m_weight = weight;

    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);
}

///d'après le cours
vector<int> Graph::Forte_connexite(vector<vector<int>> m_vect, int ordre, int s) //matrice d'adjacence, ordre du graphe, sommet de référence
{
    vector<int> c1, c2, c;
    vector<int> marques;
    int ajoute =1;

    for(int i=0;i<ordre;i++)
    {
        c1.push_back(0);
        c2.push_back(0);
        c.push_back(0);
        marques.push_back(0);
    }

    c1[s]=1;
    c2[s]=1;

    while(ajoute==1)
    {
        ajoute=0;

        for(int x=0;x<ordre;x++)
        {
            if(!marques[x] && c1[x])
            {

                marques[x]=1;
                for(int y=0;y<ordre;y++)
                {

                    if(m_vect[x][y] && !marques[y])
                    {

                        c1[y]=1;
                        ajoute=1;

                    }
                }
            }
        }
    }


    for(int i=0;i<ordre;i++)
    {
        marques[i]=0;
    }

    ajoute=1;
    //Recherche des composantes connexes arrivant à s à ajouter dans c2
    while(ajoute==1)
    {
        ajoute=0;
    for(int x=0;x<ordre;x++)
        {
            if(!marques[x] && c2[x])
            {
                marques[x]=1;
                for(int y=0;y<ordre;y++)
                {
                    if(m_vect[y][x] && !marques[y])
                    {
                        c2[y]=1;
                        ajoute=1;

                    }
                }
            }
        }
    }


    for(int x=0;x<ordre;x++)
    {
        c[x]=c1[x]&c2[x];
    }
    cout<<endl;
    for(int i=0;i<ordre;i++)
    {
        cout<<c[i]<<" ";
    }
    cout<<endl;
    return c;
}

vector<vector<int>> Graph::Compo_connexes(vector<vector<int>> m_vect, int ordre)
{
    vector<vector<int>> c;
    vector<int> marque;

    for(int i=0;i<ordre;i++)
    {
        marque.push_back(0);
    }
    for(int a=0;a<ordre;a++)
    {
        c.push_back(marque);
    }

    for(int x=0;x<ordre;x++)
    {
        if(!marque[x])
        {

            c[x]=Forte_connexite(m_vect,ordre,x);

            marque[x]=1;

            for(int y=0;y<ordre;y++)
            {
                if(c[x][y] && !marque[y])
                {
                    marque[y]=1;
                }
            }
        }
    }

    return c;

}
