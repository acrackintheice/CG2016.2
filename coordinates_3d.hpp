#ifndef COORDINATES_3D_HPP
#define COORDINATES_3D_HPP

#include <string>

class Coordinates_3d
{
public:
    Coordinates_3d(double x, double y, double z);
    ~Coordinates_3d();
    double get_x_scn();
    double get_y_scn();
    double get_z_scn();
    double get_x();
    double get_y();
    double get_z();
    void set_x(double new_x);
    void set_y(double new_y);
    void set_z(double new_z);
    void set_x_scn(double new_x);
    void set_y_scn(double new_y);
    void set_z_scn(double new_y);
    std::string to_string();
private:
    double _x;
    double _y;
    double _z;
    double _x_scn;
    double _y_scn;
    double _z_scn;
};

#endif 