#ifndef CURVE_HPP
#define CURVE_HPP

#include "coordinates.hpp"
#include "object.hpp"
#include <string>
#include <vector>


class Curve: public Object
{
public:
    Curve(std::vector<Coordinates> points, std::string name, Color* color);
    ~Curve();
    std::vector<Coordinates> get_drawing_points();
    void clip();
};

#endif // LINE_HPP