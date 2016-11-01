#ifndef POINT_HPP
#define POINT_HPP

#include <string>
#include "object.hpp"

class Point : public Object {
public:
    Point(Coordinates *xy, std::string name, Color *color);

    virtual void
    clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max,
                  bool clip_flag) override;
};


#endif // POINT_HPP