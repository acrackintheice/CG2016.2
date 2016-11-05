#ifndef CG2016_CLION_BEZIER_CURVE_H
#define CG2016_CLION_BEZIER_CURVE_H


#include "curve.hpp"
#include <vector>

class Bezier_Curve : public Curve {

public:

    Bezier_Curve(std::vector<Coordinates *> points, std::string name, Color *color);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                               Coordinates vp_max, bool clip_flag) override;

};


#endif //CG2016_CLION_BEZIER_CURVE_H
