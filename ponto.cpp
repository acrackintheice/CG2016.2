#include "ponto.hpp"

using namespace std;

Ponto::Ponto(Coordenadas* xy, string name){
  _pontos.push_back(xy);
  _name = name;
}
Ponto::~Ponto(){
}