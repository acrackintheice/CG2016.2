#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <string>

class Coordinates
{
public:
    Coordinates(double x, double y);
    ~Coordinates();
    double get_x();
    double get_y();
    std::string to_string();
private:
    double _x;
    double _y;
};

#endif // COORDINATES_HPP