#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>

class Sommet
{
    public:
        ///atributs
        std::string m_name;
        int m_x;
        int m_y;

        ///méthodes
        Sommet();
        Sommet(std::string _name, int _x, int _y);
        virtual ~Sommet();


    protected:

    private:
};

#endif // SOMMET_H
