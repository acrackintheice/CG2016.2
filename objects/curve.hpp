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

    std::vector<Drawing_Edge> clip(bool clip_flag = true);

private:
    bool too_far_away(Coordinates c);
};

#endif /* CURVE_H_ */
