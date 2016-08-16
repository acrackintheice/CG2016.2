#include "reta.hpp"

using namespace std;

Reta::Reta(Coordenadas* p1,Coordenadas* p2, string name)
{
    _pontos.push_back(p1);
    _pontos.push_back(p2);
    _name = name;
}
Reta::~Reta(){
}