#ifndef OBJETO_HPP
#define OBJETO_HPP

#include "coordenadas.hpp"
#include "matriz1x3.hpp"
#include "matriz3x3.hpp"
#include <vector>
#include <string>
class Objeto
{
public:
    std::string get_name();
    std::vector<Coordenadas*> get_pontos();
    void translate(double Dx, double Dy);
	void scale(double Sx, double Sy);
	void print();
    virtual ~Objeto(){}
protected:
	void transform(Matriz3x3* transformation);
	Coordenadas* geometric_center();
    std::string _name;
    std::vector<Coordenadas*> _pontos;
};

#endif // OBJETO_HPP