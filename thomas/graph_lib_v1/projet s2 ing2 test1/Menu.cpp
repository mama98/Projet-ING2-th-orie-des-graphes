#include <allegro.h>
#include "Menu.h"

#include <iostream>
using namespace std;

//S-P qui charge une image en sécurité
BITMAP  *Menu::charger_bitmap(char *nomImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage, NULL);
    if(!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }

    return bmp;
}

Menu :: ~Menu()
{

}
Menu::Menu()
{
    /// initialisation des bitmaps
    /// creation du buffer d'affichage
    m_page=create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(m_page);
    /// chargement des images

    m_decor=charger_bitmap("pics/darwin.bmp");
    m_f1=charger_bitmap("pics/foret.bmp");
    m_f2=charger_bitmap("pics/antartic.bmp");
    m_f3=charger_bitmap("pics/desert.bmp");
     /// image intermediare
    m1=charger_bitmap("pics/darwin_t1.bmp");
    m2=charger_bitmap("pics/darwin_t2.bmp");
    m3=charger_bitmap("pics/darwin_t3.bmp");
    m4=charger_bitmap("pics/darwin_q.bmp");

       fin=0;
}
/*

void Menu:: affichage (BITMAP *m_page,BITMAP *m_decor,BITMAP *m_f1,BITMAP *m_f2,BITMAP *m_f3,BITMAP *m1,BITMAP *m2,BITMAP *m3,BITMAP *m4,int fin)
{


    int jouer=0;

    while(!fin && jouer==0)
    {
        /// on affiche le menu sur l'ecran

        blit(m_decor,m_page,0,0,0,0,SCREEN_W,SCREEN_H);

        /// si on clic sur trophique 1 on passe au 1er reseau
        if( (mouse_b&1) && mouse_x>=449 && mouse_x<=768 && mouse_y>=96 && mouse_y<=132)
        {

            blit(m1,m_page, 0,0,0,0,SCREEN_W, SCREEN_H);
            blit(m_f1,m_page,0,0,0,0,SCREEN_W,SCREEN_H);
            jouer=1;
        }

         if( (mouse_b&1) && mouse_x>=489 && mouse_x<=809 && mouse_y>=220 && mouse_y<=252)
        {
            blit(m2,m_page, 0,0,0,0,SCREEN_W, SCREEN_H);
            blit(m_f2,m_page,0,0,0,0,SCREEN_W ,SCREEN_H);
            jouer=2;
        }

         if( (mouse_b&1) && mouse_x>=558 && mouse_x<=877 && mouse_y>=358 && mouse_y<=394)
        {
            blit(m3,m_page, 0,0,0,0,SCREEN_W, SCREEN_H);
            blit(m_f3,m_page,0,0,0,0,SCREEN_W,SCREEN_H);
            jouer=3;
        }

         if( (mouse_b&1) && mouse_x>=660&& mouse_x<=875 && mouse_y>=528 && mouse_y<=571)
        {
            blit(m4,m_page, 0,0,0,0,SCREEN_W, SCREEN_H);
            exit(1);
        }
    }

    blit(m_page,screen,0,0,0,0,SCREEN_W,SCREEN_H);



}
*/

/*

void Menu::affichage()
{

    Menu m;

    bool jouer=false;
    m.m_page;
    ///AFFICHAGE DU MENU PRINCIPAL

   // blit(m.m_page2,m.m_page,0,0,(SCREEN_W-m.m_page2->w)/2,(SCREEN_H-m.m_page2->h)/2,m.m_page2->w,m.m_page2->h);
    blit(m.m_decor,m.m_page,0,0,(SCREEN_W-m.m_page->w)/2,(SCREEN_H-m.m_page->h)/2,m.m_page->w,m.m_page->h);
    blit(m.m_page,screen,0,0,(SCREEN_W-m.m_page->w)/2,(SCREEN_H-m.m_page->h)/2, m.m_page->w,m.m_page->h);


    ///Affichage du 2eme menu puis chargement du terrain(decor, deplacements et radar) en fontion du choix du joueur
    while(jouer==false)
    {
        if((mouse_b&1)&&(mouse_x>=351)&&(mouse_x<=596)&&(mouse_y>=82)&&(mouse_y<=98))
        {
//re1://Revenir au choix du terrain

            jouer=true;

           m.m_f1;

            blit(m.m_f1,m.m_page,0,0,(SCREEN_W-m.m_f1->w)/2,(SCREEN_H-m.m_f1->h)/2,m.m_f1->w,m.m_f1->h);
            //blit(f1,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            //rest(500);
            while(jouer==true)
            {
                //Chargement des caractéristiques en fonction de la map choisie par le joueur
                if((mouse_b&1)&&(mouse_x>=380)&&(mouse_x<=634)&&(mouse_y>=175)&&(mouse_y<=201))
                {
                    jouer=true;
                     m.m_f2;
                    // g.make_example();
            blit(m.m_f2,m.m_page,0,0,(SCREEN_W-m.m_f2->w)/2,(SCREEN_H-m.m_f2->h)/2,m.m_f2->w,m.m_f2->h);

                }

                if((mouse_b&1)&&(mouse_x>438)&&(mouse_x<685)&&(mouse_y>283)&&(mouse_y<309))
                {
                    jouer=true;
                     m.m_f3;
            blit(m.m_f3,m.m_page,0,0,(SCREEN_W-m.m_f3->w)/2,(SCREEN_H-m.m_f3->h)/2,m.m_f3->w,m.m_f3->h);


                }

                if((mouse_b&1)&&(mouse_x>510)&&(mouse_x<674)&&(mouse_y>411)&&(mouse_y<442))
                {
                    jouer=true;
                    exit(1);

                }
            }


        }


    }



    */




















}


