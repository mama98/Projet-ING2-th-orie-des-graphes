#include "menu2.h"
#include "graph.h"
#include <allegro.h>
using namespace std;

//S-P qui charge une image en sécurité
BITMAP  *Menu2::charger_bitmap(char *nomImage)
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

Menu2::Menu2()
{
   /// initialisation des bitmaps
   m_fond=create_bitmap(SCREEN_W, SCREEN_H);
   m_page=charger_bitmap("darwin.bmp");
   m_f1=charger_bitmap("clown1.bmp");
   m_f2=charger_bitmap("clown4.bmp");
   m_f3=charger_bitmap("clown5.bmp");
}

Menu2::~Menu2()
{
    //dtor
}


void Menu2::affichage()
{

    Menu2 m;
    Graph g;
    bool jouer=false;
    m.m_page;
    ///AFFICHAGE DU MENU PRINCIPAL

   // blit(m.m_page2,m.m_page,0,0,(SCREEN_W-m.m_page2->w)/2,(SCREEN_H-m.m_page2->h)/2,m.m_page2->w,m.m_page2->h);
    blit(m.m_page,m.m_fond,0,0,(SCREEN_W-m.m_page->w)/2,(SCREEN_H-m.m_page->h)/2,m.m_page->w,m.m_page->h);
    blit(m.m_fond,screen,0,0,(SCREEN_W-m.m_fond->w)/2,(SCREEN_H-m.m_fond->h)/2, m.m_fond->w,m.m_fond->h);


    ///Affichage du 2eme menu puis chargement du terrain(decor, deplacements et radar) en fontion du choix du joueur
    while(jouer==false)
    {
        if((mouse_b&1)&&(mouse_x>351)&&(mouse_x<596)&&(mouse_y>82)&&(mouse_y<98))
        {
//re1://Revenir au choix du terrain
            cout<<"trophique1"<<endl;
            jouer=true;

           m.m_f1;

            blit(m.m_f1,m.m_fond,0,0,(SCREEN_W-m.m_f1->w)/2,(SCREEN_H-m.m_f1->h)/2,m.m_f1->w,m.m_f1->h);
            //blit(f1,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            //rest(500);
            while(jouer==true)
            {
                //Chargement des caractéristiques en fonction de la map choisie par le joueur
                if((mouse_b&1)&&(mouse_x>380)&&(mouse_x<634)&&(mouse_y>175)&&(mouse_y<201))
                {
                    jouer=true;
                     m.m_f2;
                     g.make_example();
            blit(m.m_f2,m.m_fond,0,0,(SCREEN_W-m.m_f2->w)/2,(SCREEN_H-m.m_f2->h)/2,m.m_f2->w,m.m_f2->h);

                }

                if((mouse_b&1)&&(mouse_x>438)&&(mouse_x<685)&&(mouse_y>283)&&(mouse_y<309))
                {
                    jouer=true;
                     m.m_f3;
            blit(m.m_f3,m.m_fond,0,0,(SCREEN_W-m.m_f3->w)/2,(SCREEN_H-m.m_f3->h)/2,m.m_f3->w,m.m_f3->h);


                }

                if((mouse_b&1)&&(mouse_x>510)&&(mouse_x<674)&&(mouse_y>411)&&(mouse_y<442))
                {
                    jouer=true;
                    exit(1);

                }
            }


        }


    }


}


/*
///AFFICHAGE DU MENU PRINCIPAL
    blit(accueil,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    ///Affichage du 2eme menu puis chargement du terrain(decor, deplacements et radar) en fontion du choix du joueur
   while(jouer==0)
    {
        if((mouse_b&1)&&(mouse_x>325)&&(mouse_x<435)&&(mouse_y>290)&&(mouse_y<325))
        {
            re1://Revenir au choix du terrain

            jouer=1;
            blit(menu2,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            rest(500);
            while(jouer==1)
            {
                //Chargement des caractéristiques en fonction de la map choisie par le joueur
                if((mouse_b&1)&&(mouse_x>105)&&(mouse_x<260)&&(mouse_y>250)&&(mouse_y<360))
                {
                    jouer=2;
                    mapdecor=charger_bitmap("map1.bmp");
                    mapdeplacements=charger_bitmap("map1.bmp");
                    mapcollision=charger_bitmap("map1collision.bmp");
                    radar=charger_bitmap("camera1.bmp");
                    fondradar=charger_bitmap("camera1.bmp");
                    musiquefond=load_midi("pokemon.mid");
                    n=1;
                }

                if((mouse_b&1)&&(mouse_x>325)&&(mouse_x<480)&&(mouse_y>250)&&(mouse_y<360))
                {
                    jouer=2;
                    mapdecor=charger_bitmap("map2.bmp");
                    mapdeplacements=charger_bitmap("map2.bmp");
                    mapcollision=charger_bitmap("map2collision.bmp");
                    radar=charger_bitmap("camera2.bmp");
                    fondradar=charger_bitmap("camera2.bmp");
                    musiquefond=load_midi("pokemon3.mid");
                    n=2;

                }

                if((mouse_b&1)&&(mouse_x>540)&&(mouse_x<690)&&(mouse_y>250)&&(mouse_y<360))
                {
                    jouer=2;
                    mapdecor=charger_bitmap("map3.bmp");
                    mapdeplacements=charger_bitmap("map3.bmp");
                    mapcollision=charger_bitmap("map3collision.bmp");
                    radar=charger_bitmap("camera3.bmp");
                    fondradar=charger_bitmap("camera3.bmp");
                    musiquefond=load_midi("powerrangers.mid");
                    n=3;
                }
*/
