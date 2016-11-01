#ifndef LINE_HPP
#define LINE_HPP

#include "object.hpp"
#include <string>
#include <algorithm>
#include <iostream>

class Line: public Object
{
public:
    Line(Coordinates* p1, Coordinates* p2, std::string name = "", Color* color = new Color(1,1,1,1));
    std::vector<Drawing_Edge> clip(bool clip_flag = true);

    virtual void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max, bool clip_flag) override;
};


#endif // LINE_HPP

