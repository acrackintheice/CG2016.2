#include "cor.hpp"

Cor::Cor(double r, double g, double b, double a){
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}
Cor::~Cor(){}

double Cor::get_r(){
	return _r;
}
double Cor::get_g(){
	return _g;
}
double Cor::get_b(){
	return _b;
}
double Cor::get_a(){
	return _a;
}
