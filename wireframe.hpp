#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP

#include <vector>
#include <string>
#include <iostream>
#include "object.hpp"
#include "operations.cpp"
#include "line.hpp"
#include "point.hpp"


class Wireframe : public Object
{
public:
    Wireframe(std::vector<Coordinates_3d*> points, std::vector<Edge> edges, std::string name, Color* color, Color* background_color, bool filled);
    std::vector<Edge> clip();
private:
	std::vector<Edge> sub_clip(std::vector<Edge> in);
	bool fake_frame(std::vector<Edge> in);
	bool inside(Coordinates_3d* point, std::string edge);
};

#endif // WIREFRAME_HPP