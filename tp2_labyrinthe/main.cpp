/**
    Ce projet constitue une base pour la réalisation du TP2 "Labyrinthe"
    de théorie des graphes 2ème semestre ING2 ECE PARIS.

    Par rapport à l'énoncé initial (hérité du langage C) et à la réalisation
    (méritante) de l'étudiant Cremel qui était proposée ce code a été intégralement
    ré-écrit en essayant de simplifier au maximum l'interface d'utilisation.

    De ce fait il y a une classe Labybase qui gère les aspects "techniques"
    en particulier le chargement depuis un fichier et l'affichage "graphique"

    Il est indispensable d'aller voir l'interface publique de Labybase
    dans labybase.h, mais il n'est pas nécessaire de comprendre l'implémentation
    dans labybase.cpp pour utiliser le code fourni.

    La classe dans laquelle vous travaillerez est la classe Labyrinthe qui hérite
    publiquement de Labybase, mais ne peut (ne devrait pas) avoir besoin des aspects
    techniques (privés) de Labybase. Il sera aussi sans doute utile/nécessaire
    de compléter la classe Sommet, par exemple en ajoutant à chaque sommet
    un attribut m_predecesseur pour "remonter" les chemins trouvés par BFS ou DFS
    (alternativement on pourra avoir des vecteurs de prédecesseurs locales aux procédures)

    Par rapport au modèle initial, on s'est débarrassé de la classe "Noeud" qui représentait
    en fait des positions de sommets. LES SOMMETS SONT DESORMAIS REFERENCES PAR UN SEUL ENTIER.
    On a donc le sommet 0, le sommet 1 etc... ce qui permet de ranger les sommets dans
    un simple vecteur de sommets à une dimension (m_sommets dans Labybase) et de gérer la liste
    des sommets adjacents à un sommet comme un vecteur d'entiers (m_adjacents dans Sommet).

    La numérotation se fait en partant de 0 en haut à gauche, et va de gauche à droite puis
    de haut en bas (selon la convention usuelle de lecture d'un texte). LES COORDONNEES
    (LIGNE, COLONNE) NE JOUENT PLUS AUCUN ROLE DANS LA MECANIQUE DES PARCOURS (RELISEZ
    3 FOIS CETTE PHRASE !). Vous ne DEVEZ PAS voir de lig,col dans vos algos, seulement
    des indices => un seul int suffit pour désigner un sommet. Par commodité il sera toujours
    possible d'afficher les coordonnées associées à un indice, mais il ne s'agit que
    d'un affichage, pas d'une donnée utile à l'algo (voir utilisation de la méthode coords
    dans la méthode affichage_donnees de la classe Labyrinthe)

    Regardez attentivement la méthode affichage_donnees de la classe Labyrinthe
    pour un exemple d'utilisation du graphe. Vous ferez vos méthode au même niveau
    et avec les même outils (mais des algos différents !)


    Robin Fercoq 2018
    ECE PARIS
*/

#include "labyrinthe.h"

#include <iostream>

int main()
{
    /// Dans le bloc try le déroulement normal du projet
    try
    {
        /// Création et chargement du labyrinthe,
        /// voir les autres labyrinthes dans le répertoire de projet
        Labyrinthe laby("laby.txt");

        /// Affichage graphique, ne refaites pas votre propre méthode d'affichage !
        laby.afficher();

        /// Exemple d'utilisation des attributs de sommet pour afficher des infos
        /// A enlever par la suite !
        laby.get_sommet(3).set_marque(true);
        laby.get_sommet(5).set_carac('#');
        std::cout << std::endl << "Exemple d'utilisation des attributs marque et carac de sommet :" << std::endl;
        laby.afficher();

        /// Exemple de méthode parcours, vous pourrez enlever cet appel par la suite !
        laby.affichage_donnees();

        /// ICI LES APPELS A VOS METHODES BFS, DFS, Composantes Connexes...
        /// ...
        laby.composantes_connexes();
    }

    /// Récupérer exceptions lancées explicitement avec throw par notre code
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
