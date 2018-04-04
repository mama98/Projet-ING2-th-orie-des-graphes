#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <allegro.h>

class Menu
{
private :

   /// buffer recevant l'image
    BITMAP *m_page;
   /// image de fond
    BITMAP *m_decor;
    BITMAP *m_decor2;
   /// 3 images issu du menu
    BITMAP *m_f1;
    BITMAP *m_f2;
    BITMAP *m_f3;
    /// 4 bitmap map intermediare
    BITMAP *m1;
    BITMAP *m2;
    BITMAP *m3;
    BITMAP *m4;
    int fin;

public:
    Menu();
    ~Menu();
    BITMAP  *charger_bitmap(char *nomImage);
   // void affichage(BITMAP *m_page,BITMAP *m_decor,BITMAP *m_f1,BITMAP *m_f2,BITMAP *m_f3,BITMAP *m1,BITMAP *m2,BITMAP *m3,BITMAP *m4,int fin);

   void affichage();
};

#endif // MENU_H_INCLUDED
