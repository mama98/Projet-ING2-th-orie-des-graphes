#include "graphe.h"
#include <fstream>
#include "Arete.h"
#include "Sommet.h"
#include <iostream>
#define INFINI 1000.0
using namespace std;
///SOURCES: Réalisé à partir des bouts de code de Kuskal et Djikstra
/// du dossier de cours magistral de théorie des graphes ING2 par Jean Pierre Segado.

Graphe::Graphe()
{

}

Graphe::~Graphe()
{

}

void Graphe::Lire_fichier(string filename)

{
    ifstream fichier (filename.c_str(), ios:: in); /// on ouvre le fichier en mode lecture
    if(fichier)
    {
        fichier>>m_ordre;  /// on lit la première valeure du fichier qui est l'ordre.
        fichier>>m_aretes;
        Arete a;
        a.m_s1=0;
        a.m_s2=0;
        a.m_poids=0;

        for(int i=0; i< m_aretes; i++)       ///on remplit la matrice de sommets à l'aide de la matrice du fichier.
        {
            fichier>>a.m_s1;
            fichier>>a.m_s2;
            fichier>>a.m_poids;
            m_AR.push_back(a);
        }

        fichier.close();                        ///fermeture du fichier
    }

    else
        cerr <<"Impossible d'ouvrir le fichier"<< endl;

}

void Graphe::Kruskal()
{
    arbre = new Arete[m_aretes];
    int *connexe;
    connexe = new int[m_ordre];
    bool cmpt=false;
    int indiceA=0, indiceG=0;
    int x,s1,s2;
    Arete u;

    ///Allouer l'arbre de "ordre-1" aretes
    for(int i=0; i<m_ordre-1; i++)
    {
        arbre[i].m_s1=0;
        arbre[i].m_s2=0;
        arbre[i].m_poids=0;
    }

    ///Allouer le tableau connexe de "ordre" sommets

    for(x=0; x<m_ordre; x++)
    {
        connexe[x]=x;
    }

    ///Trier le graphe par ordre croissant des poids de ses "n" aretes
    while(!cmpt)
    {
        cmpt=true;
        for(int k=0; k<m_aretes-1; k++)
        {

            if(m_AR[k].m_poids>m_AR[k+1].m_poids)
            {
                swap(m_AR[k], m_AR[k+1]);
                cmpt=false;
            }

        }

    }
    cout<<endl;
    /// tant que les aretes de l'arbre et du graphe ne sont pas toutes traitées
    while(indiceA<m_ordre-1 && indiceG<m_aretes)
    {
        u= m_AR[indiceG];
        s1=connexe[u.m_s1];
        s2=connexe[u.m_s2];

        if(s1==s2)
            indiceG++;
        else
        {
            arbre[indiceA]=u ;
            indiceA++;
            indiceG++;
            for(x=0; x<m_ordre; x++)
            {
                if(connexe[x]==s1)
                {
                    connexe[x]=s2;
                }
            }


        }

    }
    cout<<"Arbre de Kruskal:"<<endl;
    for(int l=0; l<m_ordre-1; l++)
    {
        cout<<"Sommet :"<<arbre[l].m_s1<<" Sommet :"<<arbre[l].m_s2<<" Poids:"<<arbre[l].m_poids<<endl;
    }

}

void Graphe::sauvegarder(string filename)
{
    Kruskal();
    ofstream fichier("sauvegarde.txt",ios::out| ios::trunc);
    if(fichier)
    {
        fichier<< "le chemin de poids minimum est : "<<endl;
        for(int i=0; i<m_ordre-1; i++)
        {
            fichier<< arbre[i].m_s1<<" "<< arbre[i].m_s2<< " "<< arbre[i].m_poids<<endl;
        }

        fichier.close();
    }
    else
    {
        cerr<<"Erreur d'ouverture de fichier"<<endl;
    }
}

void Graphe::allouer(int ordre)
{
    m_adj=new int*[ordre];                      ///Création de la matrice d'ordre donné dans le fichier.

    for(int i=0; i<ordre; i++)
    {
        m_adj[i]=new int[ordre];
    }
    for (int j=0; j<ordre; j++)                 ///on initialise la matrice à 0.
    {
        for (int k=0; k<ordre; k++)
        {
            m_adj[j][k]=0;
        }
    }
}

void Graphe::Lire_fichier_Djikstra(string filename)

{
    ifstream fichier (filename.c_str(), ios:: in); /// on ouvre le fichier en mode lecture
    if(fichier)
    {
        fichier>>m_ordre;  /// on lit la première valeure du fichier qui est l'ordre.
        allouer(m_ordre);
        for(int i=0; i< m_ordre; i++)       ///on remplit la matrice de sommets à l'aide de la matrice du fichier.
        {
            for(int j=0; j<m_ordre; j++)
            {
                fichier>>m_adj[i][j];
            }
        }

        fichier.close();                        ///fermeture du fichier
    }

    else
        cerr <<"Impossible d'ouvrir le fichier"<< endl;

}

void Graphe::Djikstra()
{
    int*marques;
    int*pred;
    int *l;     ///longueur minimales des sommets
    int s=0;    /// On part du sommet 0
    int x,y,xmin;
    float minimal;
    int nb=0;

///Allocation du tableau marques
    marques = new int[m_ordre];
    for(int i=0; i<m_ordre; i++)
    {
        marques[i]=0;
    }
    ///Allocation du tableau
    l = new int[m_ordre];
    for(int i=0; i<m_ordre; i++)
    {
        l[i]=INFINI;
    }
    ///Allocation du tableau de predecesseurs
    pred = new int[m_ordre];
    for(int i=0; i<m_ordre; i++)
    {
        pred[i]=0;
    }


    l[s]=nb=0;

    while(nb<m_ordre)
    {
        minimal=INFINI;

        for(x=0; x<m_ordre; x++)
        {
            if(!marques[x] && l[x]<minimal)
            {
                xmin=x;
                minimal=l[x];

            }
        }

        marques[xmin]=1;
        nb++;

        for(y=0; y<m_ordre; y++)
        {
            if(m_adj[xmin][y]&& !marques[y]&& l[xmin]+m_adj[xmin][y]<l[y])
            {
                l[y]=l[xmin]+ m_adj[xmin][y];
                pred[y]=xmin;
            }
        }
    }
    cout<<"chemin donne par Djikstra en partant de 0:"<<endl;
    for(int p=0; p<m_ordre; p++)
    {
        cout<<pred[p]<<endl;
    }

}

void Graphe::afficher()
{

    for(int i=0; i<m_aretes; i++)
    {
        cout<<"Sommet :"<<m_AR[i].m_s1<<" Sommet :"<<m_AR[i].m_s2<<" Poids:"<<m_AR[i].m_poids<<endl;
    }
}

