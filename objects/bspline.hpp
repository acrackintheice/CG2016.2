#ifndef BSpline_HPP
#define BSpline_HPP

#include <string>
#include <vector>
#include <iostream>
#include "object.hpp"
#include "../utils/matrix4x1.hpp"
#include "../utils/matriz4x4.hpp"
#include "../utils/matrix1x4.hpp"
#include "line.hpp"


class BSpline : public Object {
public:
    BSpline(std::vector<Coordinates *> points, std::string name, Color *color);

    std::vector<Coordinates> getFwdDiffPoints(double n, Matriz4x1 dx, Matriz4x1 dy);

    std::vector<Drawing_Edge> clip(bool clip_flag = true);

private:
    bool too_far_away(Coordinates c);
};

#endif // BSPLINE_HPP