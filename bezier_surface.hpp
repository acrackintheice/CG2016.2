#ifndef CG2016_CLION_BEZIER_SURFACE_H
#define CG2016_CLION_BEZIER_SURFACE_H


#include "surface.hpp"

class Bezier_Surface : public Surface {

public:

    Bezier_Surface(std::vector<Coordinates *> points, std::string name, Color *color);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                               Coordinates vp_max, bool clip_flag) override;

};


#endif //CG2016_CLION_BEZIER_SURFACE_H
