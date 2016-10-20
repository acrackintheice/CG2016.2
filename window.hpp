#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <iostream>
#include "object.hpp"
#include "operations.cpp"

class Window : public Object
{
public:
	Window(Coordinates_3d* p1, Coordinates_3d* p2, Coordinates_3d* p3, Coordinates_3d* p4, Coordinates_3d* vup, Coordinates_3d* vpn);
	void move(double dx, double dy, double dz);
	Coordinates_3d* get_p1();
	Coordinates_3d* get_p2();
	Coordinates_3d* get_p3();
	Coordinates_3d* get_p4();
	Coordinates_3d* get_vup();
	Coordinates_3d* get_vpn();
	void transform(Matriz4x4 transformation);
	void transform2(Matriz4x4 transformation);
	double get_vup_angle();
private:
	Coordinates_3d* _vup;
	Coordinates_3d* _vpn;
};

#endif // WINDOW_HPP
