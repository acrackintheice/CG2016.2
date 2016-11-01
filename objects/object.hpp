#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cairo.h>
#include "../core/coordinates.hpp"
#include "../utils/matrix1x4.hpp"
#include "../utils/matriz4x4.hpp"
#include "../utils/matrix4x1.hpp"
#include "../utils/color.hpp"
#include "../core/edge.hpp"
#include "../core/drawing_edge.hpp"
#include "math.h"
#include "../utils/operations.cpp"
#include "../utils/matrices.cpp"
#include "../utils/transformations.hpp"

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

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max, bool clip_flag)= 0;

    void draw_edge(Coordinates p1, Coordinates p2, cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max);

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