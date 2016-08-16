#ifndef COORDENADASXY_HPP
#define COORDENADASXY_HPP

class Coordenadas
{
public:
    Coordenadas(double x, double y);
    ~Coordenadas();
    double get_x();
    double get_y();
private:
    double _x;
    double _y;
};

#endif // COORDENADASXY_HPP