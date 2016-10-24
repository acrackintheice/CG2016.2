#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <iostream>
#include "object.hpp"
#include "operations.cpp"
#include "wireframe.hpp"

class Window : public Object
{
public:
	Window(Coordinates* p1, Coordinates* p2, Coordinates* p3, Coordinates* p4, Coordinates* vup, Coordinates* vpn);
    ~Window();
	void move(double dx, double dy, double dz);
	Coordinates min();
	Coordinates max();
	Coordinates vup();
	Coordinates vpn();
    Coordinates vrp();
	void transform(Matriz4x4 transformation, bool use_scn = false, bool change_scn = false);
    std::vector<Edge> clip();
private:
	Wireframe* _vup;
    Wireframe* _vpn;
    Wireframe* _vrp;

    std::vector<Wireframe*> configuration_points;
};

#endif // WINDOW_HPP
