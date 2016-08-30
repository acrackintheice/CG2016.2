#include "polygon.hpp"

using namespace std;

Polygon::Polygon(vector<Coordinates> points, string name){
	_points = points;
	_name = name;
}
Polygon::~Polygon(){
}
std::vector<Coordinates> Polygon::get_drawing_points(){
	std::vector<Coordinates> drawing_points = _scn_points;
    Coordinates first_point = _scn_points[0];
    drawing_points.push_back(first_point);
	return drawing_points;
}