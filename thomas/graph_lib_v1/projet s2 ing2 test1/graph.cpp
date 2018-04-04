#include "graph.h"
#include <fstream>
#include "sommet.h"

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
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.

void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "ours.bmp");
    add_interfaced_vertex(1, 60.0, 400, 100, "vegetation.bmp");
    add_interfaced_vertex(2,  50.0, 200, 300, "insecte.bmp");
    add_interfaced_vertex(3,  0.0, 400, 300, "elan.bmp");
    add_interfaced_vertex(4,  100.0, 600, 300, "lievre_d_amerique.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "loup_gris.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "renard.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "castor.jpg", 2);


    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
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

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

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
}

void Graph::allouer(int ordre)
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
}


void Graph ::Lire_fichier(string filename )
{
    /// ouverture du fichier en lecture
    ifstream fichier(filename.c_str(), ios::in);
 string name;
 int x,y;
    /// test d'ouverture de fichier

    if(fichier)
    {

        allouer(m_ordre);
        fichier>>m_ordre;  /// on lit la première valeure du fichier qui est l'ordre.
        fichier>>m_aretes;
        for(int i=0;i<m_ordre;i++)
        {
            fichier>> name >> x>> y;
            m_name.push_back(name);
            Sommet(name,x,y);
        }

        for(int i=0; i< m_ordre; i++)       ///on remplit la matrice de sommets à l'aide de la matrice du fichier.
        {
            for(int j=0; j<m_ordre; j++)
            {
                fichier>>m_mat[i][j];
            }
        }
        fichier.close();
    }
    else
    {
        cerr<<"Erreur. Ouverture de fichier impossible"<<endl;
    }
}
void Graph::afficher_fichier()
{
    cout<<m_ordre<<endl;
    cout<<m_aretes<<endl;
        for(int i=0; i< m_ordre; i++)       ///on remplit la matrice de sommets à l'aide de la matrice du fichier.
        {
            for(int j=0; j<m_ordre; j++)
            {
                cout<<m_mat[i][j];
            }
            cout<<endl;
        }
     cout<<endl;
        cout<<"-----Les infuences de notre biome -----"<<endl;
        cout<<endl;

       for(int i=0; i< m_ordre; i++)       ///on remplit la matrice de sommets à l'aide de la matrice du fichier.
        {
            for(int j=0; j<m_ordre; j++)
            {
                if(m_mat[i][j]==1)
                {
                      cout<<m_name[i]<<" mange "<< m_name[j]<<endl;
                }

            }
        }
}



//S-P qui charge une image en sécurité
BITMAP  Graph :: *charger_bitmap(char *nomImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage, NULL);
    if(!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }

}

void Graph :: menu()
{
    BITMAP  *page=NULL,*choix0=NULL,*choix1=NULL,*choix2=NULL,*choix3=NULL,*choix4=NULL;


    page=create_bitmap(SCREEN_W,SCREEN_H);
    choix0=load_bitmap("pics/darwin.bmp",NULL);


   // blit(choix0,page,0,0,0,0,SCREEN_W,SCREEN_H);
     blit( page,screen,0,0,0,0,SCREEN_W,SCREEN_H);



    choix1=load_bitmap("pics/darwin_t1.bmp",NULL);
    choix2=load_bitmap("pics/darwin_t2.bmp",NULL);
    choix3=load_bitmap("pics/darwin_t3.bmp",NULL);
    choix4=load_bitmap("pics/darwin_q.bmp",NULL);

  int choix=0;

    while(choix != 4 || !mouse_b&1 )
    {
        if(    403<=mouse_x && mouse_x<=858 && 51<=mouse_y && mouse_y<=163 )
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
                       Lire_fichier("trophique1.txt");
                       break;
                    }


            }

        }





}





}
