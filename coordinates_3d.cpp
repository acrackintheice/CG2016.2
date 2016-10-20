#include "coordinates_3d.hpp"

Coordinates_3d::Coordinates_3d(double x, double y, double z){
	_x = x;
	_y = y;
	_z = z;
    _x_scn = x;
    _y_scn = y;
    _z_scn = z;
}

Coordinates_3d::~Coordinates_3d(){
}

double Coordinates_3d::get_x(){
    return _x;
}
double Coordinates_3d::get_y(){
    return _y;
}
double Coordinates_3d::get_z(){
    return _z;
}

void Coordinates_3d::set_x(double new_x){
    _x = new_x;
}
void Coordinates_3d::set_y(double new_y){
    _y = new_y;
}
void Coordinates_3d::set_z(double new_z){
    _z = new_z;
}

double Coordinates_3d::get_x_scn(){
    return _x_scn;
}
double Coordinates_3d::get_y_scn(){
    return _y_scn;
}
double Coordinates_3d::get_z_scn(){
    return _z_scn;
}
void Coordinates_3d::set_x_scn(double new_x){
    _x_scn = new_x;
}
void Coordinates_3d::set_y_scn(double new_y){
    _y_scn = new_y;
}
void Coordinates_3d::set_z_scn(double new_z){
    _z_scn = new_z;
}

std::string Coordinates_3d::to_string(){
	return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ", " + std::to_string(_z) + ")";
}