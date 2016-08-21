#include "coordinates.hpp"

Coordinates::Coordinates(double x, double y){
	_x = x;
	_y = y;
}

Coordinates::~Coordinates(){
}

double Coordinates::get_x(){
    return _x;
}
double Coordinates::get_y(){
    return _y;
}
