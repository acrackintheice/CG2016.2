#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <iostream>
#include "object.hpp"
#include "operations.cpp"

class Window : public Object
{
public:
	Window(Coordinates* p1, Coordinates* p2, Coordinates* p3, Coordinates* p4, Coordinates* vup, Coordinates* vpn, Coordinates* cop);
    ~Window();
	void move(double dx, double dy, double dz);
	Coordinates min();
	Coordinates max();
	Coordinates vup();
	Coordinates vpn();
    Coordinates vrp();
    Coordinates cop();
	void transform(Matriz4x4 transformation, bool use_scn = false, bool change_scn = false);
    std::vector<Edge> clip();
private:
    Coordinates* _vup;
    Coordinates* _vpn;
	Coordinates* _vrp;
    Coordinates* _cop;

    std::vector<Coordinates*> configuration_points;
};

#endif // WINDOW_HPP
