#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>

class Sommet
{
public:


    std::string m_name;
    int m_x;
    int m_y;
    Sommet();
    Sommet(std::string _name, int _x, int _y);
    ~Sommet();


};

#endif // SOMMET_H_INCLUDED
