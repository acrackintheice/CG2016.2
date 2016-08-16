#include "coordenadas.hpp"

Coordenadas::Coordenadas(double x, double y){
	_x = x;
	_y = y;
}

Coordenadas::~Coordenadas(){
}

double Coordenadas::get_x(){
    return _x;
}
double Coordenadas::get_y(){
    return _y;
}
