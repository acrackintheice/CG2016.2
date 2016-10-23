#ifndef COORDINATES_3D_HPP
#define COORDINATES_3D_HPP

#include <string>

class Coordinates
{
public:
    Coordinates(double x, double y, double z);
    ~Coordinates();
    double x_scn();
    double y_scn();
    double z_scn();
    double x();
    double y();
    double z();
    void set_xyz(double new_x, double new_y, double new_z);
    void set_xyz_scn(double new_x, double new_y, double new_z);
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