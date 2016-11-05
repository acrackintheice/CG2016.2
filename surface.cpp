#include "surface.hpp"
#include "wireframe.hpp"

Surface::Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool bspline) {
    _points = points;
    _name = name;
    _color = color;
    _filled = false;
    _background_color = new Color(1, 1, 1, 1);
}

