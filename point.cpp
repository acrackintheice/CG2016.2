#include "point.hpp"
#include <iostream>

using namespace std;

Point::Point(Coordinates xy, string name, Color* color){
	_points.push_back(xy);
	_scn_points.push_back(xy);
	_name = name;
	_color = color;
	_filled = false;
    _background_color = new Color(1, 1, 1, 1);
}
void Point::clip(){
	double x = _scn_points[0].get_x();
	double y = _scn_points[0].get_y();

	if(x < -1 || x > 1 || y < -1 || y > 1){
		_scn_points.clear();
	}
}