#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "object.hpp"

class Window : public Object
{
public:
	Window(Coordinates p1, Coordinates p2, Coordinates vup);
	~Window();
	void move(double x1_offset, double y1_offset, double x2_offset, double y2_offset);
	void zoom_in(double value);
	void zoom_out(double value);
	void reset();
	Coordinates get_min();
	Coordinates get_max();
	Coordinates get_vup();
	std::vector<Coordinates> get_drawing_points();
private:
	void transform(Matriz3x3 transformation);

	Coordinates _vup;
};

#endif // WINDOW_HPP