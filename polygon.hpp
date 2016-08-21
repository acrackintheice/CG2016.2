#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "coordinates.hpp"
#include "object.hpp"
#include <vector>
#include <string>

class Polygon : public Object
{
public:
    Polygon(std::vector<Coordinates> pontos, std::string name);
    ~Polygon();
    std::vector<Coordinates> get_drawing_points();
};

#endif // POLYGON_HPP