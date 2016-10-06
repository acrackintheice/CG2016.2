#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP

#include "coordinates.hpp"
#include "object.hpp"
#include <vector>
#include <string>
#include "line.hpp"
#include "point.hpp"

class Wireframe : public Object
{
public:
    Wireframe(std::vector<Coordinates> points, std::string name, Color* color);
    void clip();
};

#endif // WIREFRAME_HPP