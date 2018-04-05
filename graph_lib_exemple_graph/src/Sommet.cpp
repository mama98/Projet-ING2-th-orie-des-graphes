#include "Sommet.h"

Sommet::Sommet()
{
    //ctor
}

Sommet::~Sommet()
{
    //dtor
}

Sommet::Sommet(std::string _name,int _x,int _y)
{
    m_name=_name;
    m_x=_x;
    m_y=_y;
}
