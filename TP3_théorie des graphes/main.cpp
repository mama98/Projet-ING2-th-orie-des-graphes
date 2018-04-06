#include <iostream>
#include "Sommet.h"
#include "Arete.h"
#include "graphe.h"
#include <fstream>

using namespace std;

int main()
{
    Graphe g1;
    string fichier, fichier2;
    cout<<"veuillez entrer le nom du fichier dont vous souhaitez y appliquer la methode de Kruskal:"<<endl;
    cout<<"ex: TP3.txt "<<endl;
    cin>>fichier;
    cout<<endl;
    g1.Lire_fichier(fichier);
    g1.afficher();
    cout<<endl;
    g1.sauvegarder(fichier);
    cout<<endl;
    cout<<"Allez voir dans le fichier texte sauvegarde du fichier tp3"<<endl;
    cout<<"Veuillez entrer le nom du fichier ou vous voulez utiliser Djikstra:"<<endl;
    cout<<"ex:Djikstra.txt"<<endl;
    cin>>fichier2;
    cout<<endl;
    g1.Lire_fichier_Djikstra(fichier2);
    g1.Djikstra();
    return 0;
}
