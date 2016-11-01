#ifndef CURVE_H_
#define CURVE_H_

#include <cmath>
#include <iostream>
#include "object.hpp"
#include "../utils/matrix4x1.hpp"
#include "../utils/matriz4x4.hpp"
#include "../utils/matrix1x4.hpp"
#include "line.hpp"

class Curve : public Object {
public:
    Curve(std::vector<Coordinates *> points, std::string name, Color *color);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max, bool clip_flag) override;
};

#endif /* CURVE_H_ */
