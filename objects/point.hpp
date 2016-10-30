#ifndef POINT_HPP
#define POINT_HPP

#include <string>
#include "object.hpp"

class Point : public Object
{
public:
    Point(Coordinates* xy, std::string name, Color* color);
    std::vector<Drawing_Edge> clip(bool clip_flag = true);
};

#endif // POINT_HPP