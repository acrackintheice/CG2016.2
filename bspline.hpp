#ifndef BSpline_HPP
#define BSpline_HPP

#include <string>
#include <vector>
#include <iostream>
#include "object.hpp"
#include "matriz4x1.hpp"
#include "matriz4x4.hpp"
#include "matriz1x4.hpp"
#include "line.hpp"


class BSpline: public Object
{
public:
    BSpline(std::vector<Coordinates_3d*> points, std::string name, Color* color);
    std::vector<Coordinates_3d> getFwdDiffPoints(double n,Matriz4x1 dx, Matriz4x1 dy);
    std::vector<Edge> clip();
private:
	bool too_far_away(Coordinates_3d c);
	bool is_inside(Coordinates_3d c);
};

#endif // BSPLINE_HPP