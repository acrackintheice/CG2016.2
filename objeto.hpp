#ifndef OBJETO_HPP
#define OBJETO_HPP

#include "coordenadas.hpp"
#include <vector>
#include <string>
#include <iostream>
class Objeto
{
public:
    std::string get_name();
    std::vector<Coordenadas*> get_pontos();
    virtual ~Objeto(){}
protected:
    std::string _name;
    std::vector<Coordenadas*> _pontos;
};

#endif // OBJETO_HPP