#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "Sommet.h"

class Arete
{
public:
    int m_s1;
    int m_s2;
    int m_poids;
    Arete();
    Arete(int s1, int s2, int poids);
    ~Arete();

};

#endif // ARETE_H_INCLUDED
