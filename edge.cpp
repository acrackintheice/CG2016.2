#include "edge.hpp"

Edge::Edge(Coordinates_3d* p1, Coordinates_3d* p2){
	_p1 = p1;
	_p2 = p2;
}

Edge::~Edge(){
}

Coordinates_3d* Edge::get_p1(){
    return _p1;
}
Coordinates_3d* Edge::get_p2(){
    return _p2;
}
std::string Edge::to_string(){
	return "(" + _p1->to_string() + " ----> " + _p2->to_string() + ")";
}