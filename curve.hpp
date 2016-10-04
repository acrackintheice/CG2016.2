#ifndef CURVE_H_
#define CURVE_H_

#include "object.hpp"
#include "matriz4x1.hpp"
#include "matriz4x4.hpp"
#include "matriz1x4.hpp"

class Curve : public Object{
public:
	Curve(std::vector<Coordinates> points, std::string name, Color* color);
	virtual ~Curve();
private:
	void blending_functions();
	void clip();
};

#endif /* CURVE_H_ */
