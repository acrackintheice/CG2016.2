#ifndef COORDINATES_HPP
#define COORDINATES_HPP

class Coordinates
{
public:
    Coordinates(double x, double y);
    ~Coordinates();
    double get_x();
    double get_y();
private:
    double _x;
    double _y;
};

#endif // COORDINATES_HPP