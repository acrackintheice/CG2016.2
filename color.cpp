#include "color.hpp"

Color::Color(double r, double g, double b, double a){
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}
Color::~Color(){}

double Color::get_r(){
	return _r;
}
double Color::get_g(){
	return _g;
}
double Color::get_b(){
	return _b;
}
double Color::get_a(){
	return _a;
}
