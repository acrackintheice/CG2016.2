#ifndef CURVE_H_
#define CURVE_H_

#include "object.hpp"

class Curve : Object{
public:
	Curve(std::vector<Coordinates> points, std::string name, Color* color, Color* background_color, bool filled);
	virtual ~Curve();
private:
	void blending_functions(std::vector<Coordinates> points);
	void clip();
};

#endif /* CURVE_H_ */
