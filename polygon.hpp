#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "coordinates.hpp"
#include "object.hpp"
#include <vector>
#include <string>

class Polygon : public Object
{
public:
    Polygon(std::vector<Coordinates> points, std::string name, Color* color, Color* background_color, bool filled);
    ~Polygon();
    void clip();
    std::vector<Coordinates> get_drawing_points();
};

#endif // POLYGON_HPP