#ifndef COORDINATES_3D_HPP
#define COORDINATES_3D_HPP

#include <string>

class Coordinates_3d
{
public:
    Coordinates_3d(double x, double y, double z);
    ~Coordinates_3d();
    double get_x();
    double get_y();
    double get_z();
    void set_x(double new_x);
    void set_y(double new_y);
    void set_z(double new_z);
    std::string to_string();
private:
    double _x;
    double _y;
    double _z;
};

#endif 