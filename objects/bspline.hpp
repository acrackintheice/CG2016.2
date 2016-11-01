#ifndef BSpline_HPP
#define BSpline_HPP

#include <string>
#include <vector>
#include <iostream>
#include "object.hpp"
#include "../utils/matrix4x1.hpp"
#include "../utils/matriz4x4.hpp"
#include "../utils/matrix1x4.hpp"
#include "line.hpp"


class BSpline : public Object {
public:
    BSpline(std::vector<Coordinates *> points, std::string name, Color *color);

    void drawFwdDiffPoints(double n, Matriz4x1 dx, Matriz4x1 dy, cairo_t *cr, Coordinates win_min,
                           Coordinates win_max, Coordinates vp_min, Coordinates vp_max);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                               Coordinates vp_max, bool clip_flag) override;
};

#endif // BSPLINE_HPP