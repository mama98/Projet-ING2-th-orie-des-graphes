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
    m_main_box.set_dim(870,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    /// ccreation de la toolbox
    m_top_box.add_child(m_deleteS);
    m_deleteS.add_child(m_text_deleteS);
    m_deleteS.set_dim(120,40);
    m_deleteS.set_posx(0);
    m_deleteS.set_posy(0);
    m_deleteS.set_bg_color(ROUGE);
    m_text_deleteS.set_message("  SUPPRIMER S ");

    /*     m_top_box.add_child(m_delete);
        m_delete.add_child(m_text_delete);
        m_delete.set_dim(120,40);
        m_delete.set_posx(0);
        m_delete.set_posy(40);
        m_delete.set_bg_color(ROUGE);
        m_text_delete.set_message("  SUPPRIMER A ");*/

    m_top_box.add_child(m_add);
    m_add.add_child(m_text_add);
    m_add.set_dim(120,40);
    m_add.set_posx(0);
    m_add.set_posy(80);
    m_add.set_bg_color(BLEU);
    m_text_add.set_message("  AJOUTER  ");


    m_top_box.add_child(m_save);
    m_save.add_child(m_text_save);
    m_save.set_dim(120,40);
    m_save.set_posx(0);
    m_save.set_posy(120);
    m_save.set_bg_color(KAKICLAIR);
    m_text_save.set_message("  SAUVEGARDER  ");

    m_top_box.add_child(m_return);
    m_return.add_child(m_text_return);
    m_return.set_dim(120,40);
    m_return.set_posx(0);
    m_return.set_posy(160);
    m_return.set_bg_color(VERT);
    m_text_return.set_message("  RETOUR  ");

    m_top_box.add_child(m_evolution);
    m_evolution.add_child(m_text_evolution);
    m_evolution.set_dim(120,40);
    m_evolution.set_posx(0);
    m_evolution.set_posy(200);
    m_evolution.set_bg_color(VERT);
    m_text_evolution.set_message("  EVOLUTION ");


    m_top_box.add_child(m_exit);
    m_exit.add_child(m_text_exit);
    m_exit.set_dim(120,40);
    m_exit.set_posx(0);
    m_exit.set_posy(240);
    m_exit.set_bg_color(BLANC);
    m_text_exit.set_message("QUITTER");

}


int ** Graph::allouer(int ordre)
{
    m_mat=new int*[ordre];                      ///Création de la matrice d'ordre donné dans le fichier.

    for(int i=0; i<ordre; i++)
    {
        m_mat[i]=new int[ordre];
    }
    for (int j=0; j<ordre; j++)                 ///on initialise la matrice à 0.
    {
        for (int k=0; k<ordre; k++)
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
    string image;
    int indice =0;
    int x,y;
    double quantite;
    /// test d'ouverture de fichier
    if(fichier)
    {
        m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
        fichier>>m_ordre;  /// on lit la première valeur du fichier qui est l'ordre.
        m_vect.resize(m_ordre);
        for(int i=0; i<m_ordre; i++)
        {
            m_vect[i].resize(m_ordre);
        }

        fichier>>m_aretes;
        // m_mat=allouer(m_ordre);
        for(int i=0; i<m_ordre; i++)
        {
            fichier>> indice>>quantite>> x >> y >>image;
            add_interfaced_vertex(indice, quantite, x, y,image);
        }
        int k=0;

        for(int i=0; i<m_ordre; i++)
        {
            for(int j=0; j<m_ordre; j++)
            {
                fichier>>m_vect[i][j];
                if(m_vect[i][j]!=0)
                {
                    add_interfaced_edge(k, i, j, m_vect[i][j]);
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

BITMAP * load_bitmap_check(char *nomImage)                                      ///garder
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
        if(403<=mouse_x && mouse_x<=858 && 51<=mouse_y && mouse_y<=163 )
        {
            choix=1;
            draw_sprite(page,choix1,0,0);
        }
        else if (465<=mouse_x && mouse_x<=922 && 207<= mouse_y && mouse_y<=324)
        {
            choix=2;
            draw_sprite(page,choix2,0,0);
        }
        else if (517<= mouse_x && mouse_x<= 965 && 381 <= mouse_y && mouse_y <=495)
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


        if(mouse_b&1 && choix<=4&& choix>=1)
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
    cout<<"le nom de l'image a ajouter"<<endl;
    cin>>image;
    int successeur;
    cout<<" Veuillez saisir ses liens: "<<endl;
    cout<<"lien 1 :"<<endl;
    cin>>lien1;
    cout<<"poids :"<<endl;
    cin>> poids;

    int  a=m_vertices.size();

    add_interfaced_vertex(a,0,0,0,image);
    add_interfaced_edge(m_edges.size(),a,lien1,poids);
}

void Graph::supprimerS(int eidx)
{
    int num ;
    Vertex &remed=m_vertices.at(eidx);

    for(auto& elem : m_vertices)
    {
        m_vertices.find(eidx)->second.m_out.size();
        if (m_interface && remed.m_interface)
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_box );
    }
    m_ordre -- ;
    m_vertices.erase( eidx );


}


void Graph::test_remove_edge(int eidx)
{
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
        /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
        /* m_interface->m_main_box.add_child(ei->m_top_edge); */
        /* m_edges[idx] = Edge(weight, ei); */
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
//    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    //// std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    // vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    //veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );
    m_nb_arcs--;
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


void Graph::retour()
{
    BITMAP  *page=NULL,*choix0=NULL;


    page=create_bitmap(SCREEN_W,SCREEN_H);
    choix0=load_bitmap("pics/darwin.bmp",NULL);


    blit( page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

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

        Sauvegarder_fichier(fichier);
    }
    if(a==3)
    {
        ajouterS(); ///ajouter
    }

    if(a==4)
    {
        retour();
    }
    if(a==5)
    {
        evolution();
    }
    if(a==6)
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
    if(m_deleteS.clicked())
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
    if(m_return.clicked())
    {
        return 4;
    }
    if(m_evolution.clicked())
    {
        return 5;
    }
    if(m_exit.clicked())
    {
        return 6;
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

        for(int j=0; j<m_vertices.size(); j++)    //sauvegarde de la matrice par son parcours
        {
            for(int k=0; k<m_vertices.size(); k++)

            {
                file <<m_vect[j][k] <<" ";

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

void Graph::evolution()
{

    int k=0;


    std::map<int,Vertex>::iterator it3;

    int s=0;
    /// cherche de la proie (it3)
    for( std::map<int,Vertex>:: iterator it= m_vertices.begin(); it!=m_vertices.end(); it++) /// predateur
    {
        it->second.m_value; /// second -> vertex qui ont un attribut m_value

        for(std::map<int, Edge>:: iterator it2=m_edges.begin(); it2!=m_edges.end(); it2++) /// proie
        {

            if(it->first == it2->second.m_to)/// arete de la proie qui vient evrs le predateur
            {
                s=it2->second.m_from;

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
            for( std::map<int,Vertex>::iterator it4 = m_edges.begin(); it4!=m_edges.end(); it4++) /// proie
            {
                if(it->first==it2->second.m_from)/// arete du predateur qui vient evrs le predateur
                {
                    it->second.m_value-=it2->second.m_weight*it4->second.m_value;

                }

            }

        }
    }

}
