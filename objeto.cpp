#include "objeto.hpp"

using namespace std;

string Objeto::get_name(){
    return _name;
}
vector<Coordenadas*> Objeto::get_pontos(){
    return _pontos;
}