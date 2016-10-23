#ifndef LINE_HPP
#define LINE_HPP

#include "object.hpp"
#include <string>
#include <algorithm>
#include <iostream>

class Line: public Object
{
public:
    Line(Coordinates* p1, Coordinates* p2, std::string name, Color* color);
    std::vector<Edge> clip2();
    std::vector<Edge> clip();
};

#endif // LINE_HPP

