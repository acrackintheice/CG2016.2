#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP

#include <vector>
#include <string>
#include <iostream>
#include "object.hpp"
#include "../utils/operations.cpp"
#include "line.hpp"
#include "point.hpp"


class Wireframe : public Object {
public:
    Wireframe(std::vector<Coordinates *> points, std::vector<Edge> edges, std::string name, Color *color,
              Color *background_color, bool filled);

    std::vector<Drawing_Edge> clip(bool clip_flag = true);

private:
    std::vector<Drawing_Edge> sub_clip(std::vector<Drawing_Edge> in);

    bool fake_frame(std::vector<Drawing_Edge> in);

    bool inside(Coordinates point, int edge_code);
};

#endif // WIREFRAME_HPP