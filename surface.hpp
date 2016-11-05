#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "object.hpp"
#include <string>
#include <algorithm>
#include <iostream>

class Surface : public Object {
public:
    Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool bspline = true);

};

#endif // LINE_HPP
