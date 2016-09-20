#include "wireframe.hpp"

using namespace std;

Wireframe::Wireframe(vector<Coordinates> points, string name, Color* color){
	_points = points;
	_scn_points = points;
	_name = name;
	_color = color;
	_filled = false;
	_background_color = new Color(1, 1, 1, 1);
}
Wireframe::~Wireframe(){
}