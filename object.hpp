#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <string>
#include <iostream>
#include "coordinates.hpp"
#include "matrix1x4.hpp"
#include "matriz4x4.hpp"
#include "matrix4x1.hpp"
#include "color.hpp"
#include "edge.hpp"
#include "math.h"
#include "operations.cpp"
#include "matrices.cpp"

class Object {
public:
    std::string name();

    std::vector<Coordinates *> points();

    Color *color();

    Color *background_color();

    bool filled();

    Coordinates geometric_center(bool use_z = true, bool use_scn = false);

    void translate(double dx, double dy, double dz);

    void scale(double sx, double sy, double sz);

    void rotate(double angle, Coordinates p1, Coordinates p2);

    void rotate_x(double angle);

    void rotate_y(double angle);

    void rotate_z(double angle);

    virtual std::vector<Edge> clip()= 0;

    virtual std::vector<Edge> clip2();

    virtual void transform(Matriz4x4 transformation, bool use_scn = false, bool change_scn = false);

    virtual ~Object();

protected:
    std::string _name;
    std::vector<Coordinates *> _points;
    std::vector<Edge> _edges;
    Color *_color;
    Color *_background_color;
    bool _filled;
};

#endif // OBJECT_HPP