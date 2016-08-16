#ifndef RETA_HPP
#define RETA_HPP

#include "coordenadas.hpp"
#include <string>
#include "objeto.hpp"

class Reta: public Objeto
{
public:
    Reta(Coordenadas* p1, Coordenadas* p2, std::string name);
    ~Reta();
};

#endif // RETA_HPP

