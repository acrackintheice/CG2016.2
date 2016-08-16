#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP

#include "coordenadas.hpp"
#include "objeto.hpp"
#include <vector>
#include <string>

class Wireframe : public Objeto
{
public:
    Wireframe(std::vector<Coordenadas*> pontos, std::string name);
    ~Wireframe();
};

#endif // WIREFRAME_HPP