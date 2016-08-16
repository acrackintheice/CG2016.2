#include "wireframe.hpp"

using namespace std;

Wireframe::Wireframe(vector<Coordenadas*> pontos, string name){
   _pontos = pontos;
   _name = name;
}
Wireframe::~Wireframe(){
}