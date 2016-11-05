//
// Created by eduardo on 05/11/16.
//

#ifndef CG2016_CLION_SPLINE_SURFACE_H
#define CG2016_CLION_SPLINE_SURFACE_H

#include "surface.hpp"

class Spline_Surface : public Surface {

public:

    Spline_Surface(std::vector<Coordinates *> points, std::string name, Color *color);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                               Coordinates vp_max, bool clip_flag) override;
private:
    void draw_fwd_diff(double n, double x, double Dx, double D2x, double D3x, double y, double Dy, double D2y,
                       double D3y, cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                       Coordinates vp_max);

    Matrix4x4 update(Matrix4x4 D);

};


#endif //CG2016_CLION_SPLINE_SURFACE_H
