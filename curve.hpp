#ifndef CURVE_H_
#define CURVE_H_

#include <cmath>
#include <iostream>
#include "object.hpp"
#include "matrix4x1.hpp"
#include "matrix4x4.hpp"
#include "matrix1x4.hpp"
#include "line.hpp"

class Curve : public Object {
public:
    Curve(std::vector<Coordinates *> points, std::string name, Color *color);

};

#endif /* CURVE_H_ */
