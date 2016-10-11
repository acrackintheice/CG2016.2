#include "edge.hpp"

Edge::Edge(Coordinates_3d* p1, Coordinates_3d* p2){
	_points.push_back(p1);
	_points.push_back(p2);
	_name = "Edge";
}

Edge::~Edge(){
}

Coordinates_3d* Edge::get_p1(){
    return _points[0];
}
Coordinates_3d* Edge::get_p2(){
    return _points[1];
}
std::string Edge::to_string(){
	return "(" + _points[0]->to_string() + "\n" + _points[1]->to_string() + ")";
}