#ifndef CG2016_CLION_BEZIER_SURFACE_H
#define CG2016_CLION_BEZIER_SURFACE_H


#include "surface.hpp"

class Bezier_Surface : public Surface {

public:

    Bezier_Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool blending);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                               Coordinates vp_max, bool clip_flag) override;

    void blending_function(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                                           Coordinates vp_min, Coordinates vp_max);

    void forward_diff(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                      Coordinates vp_min, Coordinates vp_max);

};


#endif //CG2016_CLION_BEZIER_SURFACE_H
