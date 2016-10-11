#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "object_3d.hpp"
#include "edge.hpp"

class Window_3d : public Object_3d
{
public:
	Window_3d(Coordinates_3d* p1, Coordinates_3d* p2, Coordinates_3d* p3, Coordinates_3d* p4, Coordinates_3d* vup);
	~Window_3d();
	void move(double dx, double dy);
	void zoom_in(double value);
	void zoom_out(double value);
	void reset();
	Coordinates_3d* get_min();
	Coordinates_3d* get_max();
	Coordinates_3d* get_vup();
	double get_vup_angle();
	std::vector<Edge*> get_edges();
private:
	void transform(Matriz4x4 transformation);

	Coordinates_3d* _vup;
	std::vector<Edge*> _edges;
};

#endif // WINDOW_HPP
