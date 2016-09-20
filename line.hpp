#ifndef LINE_HPP
#define LINE_HPP

#include "coordinates.hpp"
#include "object.hpp"
#include <string>


class Line: public Object
{
public:
    Line(Coordinates p1, Coordinates p2, std::string name, Color* color);
    ~Line();
    void clip();
};

#endif // LINE_HPP

