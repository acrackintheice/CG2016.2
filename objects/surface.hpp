#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "object.hpp"
#include <string>
#include <algorithm>
#include <iostream>

class Surface : public Object {
public:
    Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool bspline = true);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                               Coordinates vp_min, Coordinates vp_max, bool clip_flag) override;

private:
    bool _bspline;
};

#endif // LINE_HPP
