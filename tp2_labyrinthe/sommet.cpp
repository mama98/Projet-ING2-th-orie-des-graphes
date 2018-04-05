#include "sommet.h"

Sommet::Sommet() :
    m_adjacents(), m_nbadjacents(0), m_marque(false), m_carac('\0')
{   }

const std::vector<int>& Sommet::get_adjacents() const
{
    return m_adjacents;
}

void Sommet::ajouter_adjacent(int idx)
{
    m_adjacents.push_back(idx);
    m_nbadjacents = m_adjacents.size();
}

bool Sommet::est_marque() const
{
    return m_marque;
}

void Sommet::set_marque(bool marque)
{
    m_marque = marque;
}

char Sommet::get_carac() const
{
    return m_carac;
}

void Sommet::set_carac(char c)
{
    m_carac = c;
}

bool Sommet::est_adjacent_a(int idx) const
{
    for (const auto& ida : m_adjacents)
        if ( idx==ida )
            return true;

    return false;
}

