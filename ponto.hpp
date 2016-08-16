#ifndef PONTO_HPP
#define PONTO_HPP

#include <string>
#include "objeto.hpp"
#include "coordenadas.hpp"

class Ponto : public Objeto
{
public:
    Ponto(Coordenadas *xy, std::string name);
    ~Ponto();
};

#endif // PONTO_HPP