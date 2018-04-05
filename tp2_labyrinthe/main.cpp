/**
    Ce projet constitue une base pour la r�alisation du TP2 "Labyrinthe"
    de th�orie des graphes 2�me semestre ING2 ECE PARIS.

    Par rapport � l'�nonc� initial (h�rit� du langage C) et � la r�alisation
    (m�ritante) de l'�tudiant Cremel qui �tait propos�e ce code a �t� int�gralement
    r�-�crit en essayant de simplifier au maximum l'interface d'utilisation.

    De ce fait il y a une classe Labybase qui g�re les aspects "techniques"
    en particulier le chargement depuis un fichier et l'affichage "graphique"

    Il est indispensable d'aller voir l'interface publique de Labybase
    dans labybase.h, mais il n'est pas n�cessaire de comprendre l'impl�mentation
    dans labybase.cpp pour utiliser le code fourni.

    La classe dans laquelle vous travaillerez est la classe Labyrinthe qui h�rite
    publiquement de Labybase, mais ne peut (ne devrait pas) avoir besoin des aspects
    techniques (priv�s) de Labybase. Il sera aussi sans doute utile/n�cessaire
    de compl�ter la classe Sommet, par exemple en ajoutant � chaque sommet
    un attribut m_predecesseur pour "remonter" les chemins trouv�s par BFS ou DFS
    (alternativement on pourra avoir des vecteurs de pr�decesseurs locales aux proc�dures)

    Par rapport au mod�le initial, on s'est d�barrass� de la classe "Noeud" qui repr�sentait
    en fait des positions de sommets. LES SOMMETS SONT DESORMAIS REFERENCES PAR UN SEUL ENTIER.
    On a donc le sommet 0, le sommet 1 etc... ce qui permet de ranger les sommets dans
    un simple vecteur de sommets � une dimension (m_sommets dans Labybase) et de g�rer la liste
    des sommets adjacents � un sommet comme un vecteur d'entiers (m_adjacents dans Sommet).

    La num�rotation se fait en partant de 0 en haut � gauche, et va de gauche � droite puis
    de haut en bas (selon la convention usuelle de lecture d'un texte). LES COORDONNEES
    (LIGNE, COLONNE) NE JOUENT PLUS AUCUN ROLE DANS LA MECANIQUE DES PARCOURS (RELISEZ
    3 FOIS CETTE PHRASE !). Vous ne DEVEZ PAS voir de lig,col dans vos algos, seulement
    des indices => un seul int suffit pour d�signer un sommet. Par commodit� il sera toujours
    possible d'afficher les coordonn�es associ�es � un indice, mais il ne s'agit que
    d'un affichage, pas d'une donn�e utile � l'algo (voir utilisation de la m�thode coords
    dans la m�thode affichage_donnees de la classe Labyrinthe)

    Regardez attentivement la m�thode affichage_donnees de la classe Labyrinthe
    pour un exemple d'utilisation du graphe. Vous ferez vos m�thode au m�me niveau
    et avec les m�me outils (mais des algos diff�rents !)


    Robin Fercoq 2018
    ECE PARIS
*/

#include "labyrinthe.h"

#include <iostream>

int main()
{
    /// Dans le bloc try le d�roulement normal du projet
    try
    {
        /// Cr�ation et chargement du labyrinthe,
        /// voir les autres labyrinthes dans le r�pertoire de projet
        Labyrinthe laby("laby.txt");

        /// Affichage graphique, ne refaites pas votre propre m�thode d'affichage !
        laby.afficher();

        /// Exemple d'utilisation des attributs de sommet pour afficher des infos
        /// A enlever par la suite !
        laby.get_sommet(3).set_marque(true);
        laby.get_sommet(5).set_carac('#');
        std::cout << std::endl << "Exemple d'utilisation des attributs marque et carac de sommet :" << std::endl;
        laby.afficher();

        /// Exemple de m�thode parcours, vous pourrez enlever cet appel par la suite !
        laby.affichage_donnees();

        /// ICI LES APPELS A VOS METHODES BFS, DFS, Composantes Connexes...
        /// ...
        laby.composantes_connexes();
    }

    /// R�cup�rer exceptions lanc�es explicitement avec throw par notre code
    catch (const char* msg)
    {
        std::cerr << msg << std::endl;
    }

    /// Autres exceptions
    catch (...)
    {
        std::cerr << "Une autre exception est survenue." << std::endl;
    }

    return 0;
}
