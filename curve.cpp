#include "curve.hpp"

using namespace std;

Curve::Curve(std::vector<Coordinates *> points, std::string name, Color *color) {
    _points = points;
    _name = name;
    _color = color;
    _background_color = new Color(1, 1, 1, 1);
    _filled = false;
}
