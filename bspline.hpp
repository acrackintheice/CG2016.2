#ifndef BSpline_HPP
#define BSpline_HPP

#include "coordinates.hpp"
#include "object.hpp"
#include <string>
#include <vector>
#include "matriz4x1.hpp"
#include "matriz4x4.hpp"
#include "matriz1x4.hpp"

class BSpline: public Object
{
public:
    BSpline(std::vector<Coordinates> points, std::string name, Color* color);
    std::vector<Coordinates> getFwdDiffPoints(double n,Matriz4x1 dx, Matriz4x1 dy);
    std::vector<Coordinates> get_drawing_points();
    void clip();
private:
	bool too_far_away(Coordinates c);
	bool is_inside(Coordinates c);
};

#endif // BSPLINE_HPP