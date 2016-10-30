#include "coordinates.hpp"

Coordinates::Coordinates(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
    _x_scn = x;
    _y_scn = y;
    _z_scn = z;
}

Coordinates::~Coordinates() {
}

double Coordinates::x() {
    return _x;
}

double Coordinates::y() {
    return _y;
}

double Coordinates::z() {
    return _z;
}

double Coordinates::x_scn() {
    return _x_scn;
}

double Coordinates::y_scn() {
    return _y_scn;
}

double Coordinates::z_scn() {
    return _z_scn;
}

void Coordinates::set_xyz(double new_x, double new_y, double new_z) {
    _x = new_x;
    _y = new_y;
    _z = new_z;
    _x_scn = new_x;
    _y_scn = new_y;
    _z_scn = new_z;
}
void Coordinates::set_xyz_scn(double new_x, double new_y, double new_z) {
    _x_scn = new_x;
    _y_scn = new_y;
    _z_scn = new_z;
}

std::string Coordinates::to_string() {
    return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ", " + std::to_string(_z) + ")";
}