#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP

#include <vector>
#include <string>
#include <iostream>
#include "object.hpp"
#include "operations.cpp"
#include "line.hpp"
#include "point.hpp"


class Wireframe : public Object {
public:
    Wireframe(std::vector<Coordinates *> points, std::vector<Edge> edges, std::string name = "", Color *color = new Color(1,1,1,1),
              Color *background_color = new Color(1,1,1,1), bool filled = false);

    void clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max, bool clip_flag);

private:
    std::vector<Drawing_Edge> sub_clip(std::vector<Drawing_Edge> in);

    bool fake_frame(std::vector<Drawing_Edge> in);

    bool inside(Coordinates point, int edge_code);
};

#endif // WIREFRAME_HPP