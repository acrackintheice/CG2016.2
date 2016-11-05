#ifndef BSpline_HPP
#define BSpline_HPP

#include "curve.hpp"


class Spline_Curve : public Curve {
public:
    Spline_Curve(std::vector<Coordinates *> points, std::string name, Color *color);

    void draw_fwd_diff(double n, Matrix4x1 dx, Matrix4x1 dy, cairo_t *cr, Coordinates win_min,
                           Coordinates win_max, Coordinates vp_min, Coordinates vp_max);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                               Coordinates vp_max, bool clip_flag) override;
};

#endif // BSPLINE_HPP