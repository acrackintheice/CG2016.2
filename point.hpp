#ifndef POINT_HPP
#define POINT_HPP

#include <string>
#include "object.hpp"
#include "coordinates.hpp"

class Point : public Object
{
public:
    Point(Coordinates xy, std::string name, Color* color);
    ~Point();
    void clip();
};

#endif // POINT_HPP