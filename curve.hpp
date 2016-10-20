#ifndef CURVE_H_
#define CURVE_H_

#include <cmath>
#include <iostream>
#include "object.hpp"
#include "matriz4x1.hpp"
#include "matriz4x4.hpp"
#include "matriz1x4.hpp"
#include "line.hpp"

class Curve : public Object
{
public:
	Curve(std::vector<Coordinates_3d*> points, std::string name, Color* color);
	std::vector<Edge> clip();
private:
	bool too_far_away(Coordinates_3d c);
	bool is_inside(Coordinates_3d c);
	
};

#endif /* CURVE_H_ */
