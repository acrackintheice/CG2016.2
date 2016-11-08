//
// Created by eduardo on 05/11/16.
//

#ifndef CG2016_CLION_SPLINE_SURFACE_H
#define CG2016_CLION_SPLINE_SURFACE_H

#include "surface.hpp"

class Spline_Surface : public Surface {

public:

    Spline_Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool blending);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                               Coordinates vp_max, bool clip_flag) override;
private:
    void forward_diff(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                      Coordinates vp_min, Coordinates vp_max);

    void blending_function(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                                           Coordinates vp_min, Coordinates vp_max);

};


#endif //CG2016_CLION_SPLINE_SURFACE_H
