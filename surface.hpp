#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "object.hpp"
#include <string>
#include <algorithm>
#include <iostream>

class Surface : public Object {
public:
    Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool blending = true);
protected:
    bool _blending;

    Matrix4x4 update(Matrix4x4 D);
    void draw_fwd_diff(double n, double x, double Dx, double D2x, double D3x,
                       double y, double Dy, double D2y, double D3y,
                       cairo_t *cr, Coordinates win_min, Coordinates win_max,
                       Coordinates vp_min, Coordinates vp_max);
};

#endif // LINE_HPP
