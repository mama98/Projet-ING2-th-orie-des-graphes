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
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
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
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
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
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    /// ccreation de la toolbox
    m_top_box.add_child(m_delete);
    m_delete.add_child(m_text_delete);
    m_delete.set_dim(80,40);
    m_delete.set_posx(0);
    m_delete.set_posy(0);
    m_delete.set_bg_color(ROUGE);
    m_text_delete.set_message("  SUPPRIMER  ");

    m_top_box.add_child(m_add);
    m_add.add_child(m_text_add);
    m_add.set_dim(80,40);
    m_add.set_posx(0);
    m_add.set_posy(40);
    m_add.set_bg_color(BLEU);
    m_text_add.set_message("  AJOUTER  ");


       m_top_box.add_child(m_save);
    m_save.add_child(m_text_save);
    m_save.set_dim(80,40);
    m_save.set_posx(0);
    m_save.set_posy(80);
    m_save.set_bg_color(VIOLET);
    m_text_save.set_message("  SAUVEGARDER  ");


    m_top_box.add_child(m_exit);
    m_exit.add_child(m_text_exit);
    m_exit.set_dim(80,40);
    m_exit.set_posx(0);
    m_exit.set_posy(120);
    m_exit.set_bg_color(BLANC);
    m_text_exit.set_message("QUITTER");

}


int ** Graph::allouer(int ordre)
{
    m_mat=new int*[ordre];                      ///Création de la matrice d'ordre donné dans le fichier.

    for(int i=0;i<ordre;i++)
    {
        m_mat[i]=new int[ordre];
    }
    for (int j=0;j<ordre;j++)                   ///on initialise la matrice à 0.
    {
        for (int k=0;k<ordre;k++)
        {
            m_mat[j][k]=0;
        }
    }

    return m_mat;
}

void Graph ::Lire_fichier(string filename )
{
    /// ouverture du fichier en lecture
    ifstream fichier(filename.c_str(), ios::in);
    //int* temp=nullptr;
    string image;
    int indice =0;
    int x,y;
    double quantite;
    /// test d'ouverture de fichier
    if(fichier)
    {
        //temp=new int[m_ordre];
        m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
        fichier>>m_ordre;  /// on lit la première valeur du fichier qui est l'ordre.
        fichier>>m_aretes;
        m_mat=allouer(m_ordre);
        for(int i=0;i<m_ordre;i++)
        {
            fichier>> indice>>quantite>> x >> y >>image;
            add_interfaced_vertex(indice, quantite, x, y,image);
        }
        int k=0;
        for(int i=0; i< m_ordre; i++)       ///on remplit la matrice de sommets à l'aide de la matrice du fichier.
        {
            for(int j=0; j<m_ordre; j++)
            {
                fichier>>m_mat[i][j];
                if(m_mat[i][j]!=0)
                {
                    add_interfaced_edge(k, i, j, m_mat[i][j]);
                    k++;
                }

            }
        }

        fichier.close();
    }
    else
    {
        cerr<<"Erreur. Ouverture de fichier impossible"<<endl;
    }
}

BITMAP * load_bitmap_check(char *nomImage){                                     ///garder
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
                       fichier="trophique1.txt";
                       Lire_fichier(fichier);
                       break;
                    }
                case 2:
                    {
                        choix=4;
                        fichier="trophique2.txt";
                        Lire_fichier(fichier);
                        break;
                    }
                case 3:
                    {
                        choix=4;
                        fichier="trophique3.txt";
                        Lire_fichier(fichier);

                        vector<int> resultat=Forte_connexite(m_mat,m_ordre,1);

                        for(int i=0;i!=resultat.end();i++)
                        {
                            cout <<resultat[i]<<" ";
                        }
                        cout<<endl;
                        for(int y=0; y<m_ordre;y++)
                        {
                            for(int f=0;f<m_ordre;f++)
                            {
                                cout<<m_mat[y][f]<<" ";
                            }
                            cout<<endl;
                        }
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
void Graph::Afficher()
{
    cout<<m_ordre<<endl;
    Edge ed;
    cout<<m_aretes<<endl;
        for(int i=0; i< m_ordre; i++)       ///on remplit la matrice de sommets à l'aide de la matrice du fichier.
        {
            for(int j=0; j<m_ordre; j++)
            {
                cout<<m_mat[i][j];
            }
            cout<<endl;
        }

        cout<<"Voici les influences de notre biome"<<endl;

        for(int i=0; i< m_ordre; i++)
        {
            for(int j=0; j<m_ordre; j++)
            {
                if(m_mat[i][j]==1)
                {

                }

            }

        }
}

void Graph:: ajouterS()
{
    string image;
    cout<<"le nom de l'image a ajouter"<<endl;
    cin>>image;
  int  a=m_vertices.size();
     add_interfaced_vertex(a,0,0,0,image);

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
        ///suppression
    }
    if(a==2)
    {
           Sauvegarder_fichier(fichier);
    }
    if(a==3)
    {
        ajouterS(); ///ajouter
    }
    if(a==4)
    {
        exit(1);
    }
    m_interface->update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();


}

int GraphInterface::update()
{
    if(m_delete.clicked())
    {
        return 1;
    }
    if(m_save.clicked())
    {
        return 2;
    }
    if(m_add.clicked())
    {
        return 3;
    }
    if(m_exit.clicked())
    {
        return 4;
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

        for(map<int, Vertex>::iterator it=m_vertices.begin();it!=m_vertices.end();it++)
        {
            file<< it->first <<" "<<it->second.m_value << " "<<it->second.m_interface->m_top_box.get_posx() << " "<<it->second.m_interface->m_top_box.get_posy()<< " "<<it->second.m_interface->m_img.get_pic_name()<<endl;
        }
        for(int j=0; j<m_vertices.size(); j++)    //sauvegarde de la matrice par son parcours
        {
            for(int k=0; k<m_vertices.size(); k++)
            {
                file <<m_mat[j][k] <<" ";

            }
            file << endl;
        }

        file.close();
    }
    else
    {
        cerr<<"Erreur. Ouverture de fichier impossible"<<endl;
    }
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

m_edges[idx].m_from = id_vert1;
m_edges[idx].m_to = id_vert2;

m_vertices[id_vert1].m_out.push_back(idx);
m_vertices[id_vert2].m_in.push_back(idx);
}

///d'après le cours
vector<int> Graph::Forte_connexite(vector<int> m_mat, int ordre, int s) //matrice d'adjacence, ordre du graphe, sommet de référence
{
    vector<int> c1, c2, c;
    vector<int> marques;
    int x,y;
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

        for(x=0;x<ordre;x++)
        {
            if(!marques[x] && c1[x])
            {
                marques[x]=1;
                for(y=0;y<ordre;y++)
                {
                    if(m_mat[x][y] && !marques[y])
                    {
                        c1[y]=1;
                        ajoute=1;
                    }
                }
            }
        }
    }
    //Recherche des composantes connexes arrivant à s à ajouter dans c2
    while(ajoute=1)
    {
    for(x=0;x<ordre;x++)
        {
            if(!marques[x] && c2[x])
            {
                marques[x]=1;
                for(y=0;y<ordre;y++)
                {
                    if(m_mat[y][x] && !marques[y])
                    {
                        c2[y]=1;
                        ajoute=1;
                    }
                }
            }
        }
    }


    for(x=0;x<ordre;x++)
    {
        c[x]=c1[x]&c2[x];
    }
    return c;
}

vector<vector<int>> Composantes_fconnexes(vector<int> m_mat)
{
    vector<vector<int>> tab_fconnexes;
    vector<int> marques;
    int x,y;

    for(int i=0;i<m_ordre;i++)
    {
        marques.push_back(0);
    }

    for(int s=0;s<=ordre;s++)
    {
        Forte_connexite(marquesm_ordre,s);
        tab_fconnexes.push_back(marques);

    }
        return(tab_fconnexes);

}
