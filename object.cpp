#include "object.hpp"
#include <iostream>
#include "math.h"

using namespace std;


Object::~Object(){
	delete _color;
	delete _background_color;
}
/* 
Return the list of points to be drawn, in the general case this list is the _scn_points list. 
It might change for especific objects, so they will need to overwrite this method.
*/
std::vector<Coordinates> Object::get_drawing_points(){
	return _scn_points;
}
std::vector<Coordinates> Object::get_scn_points(){
	return _scn_points;
}
string Object::get_name(){
	return _name;
}
Color* Object::get_color(){
	return _color;
}
Color* Object::get_background_color(){
	return _color;
}
vector<Coordinates> Object::get_points(){
	return _points;
}
bool Object::is_filled(){
	return _filled;
}
/* Prints the object's data */
void Object::print(){
	cout << _name << endl;
	vector<Coordinates>::iterator it;
	int i = 0;
	for(it = _scn_points.begin(); it != _scn_points.end(); it++){
		Coordinates point = (*it);
		cout << "Ponto " << i << " ==> (" << point.get_x() << ", " << point.get_y() << ")" << endl;
		i++;
	}
	cout << endl;
}
/* Returns the object's geometric center */
Coordinates Object::get_geometric_center(){
	double soma_x = 0;
	double soma_y = 0;
	vector<Coordinates>::iterator it;
	for(it = _points.begin(); it != _points.end(); it++){
		Coordinates point = (*it);
		soma_x = soma_x + point.get_x();
		soma_y = soma_y + point.get_y();
	}
	Coordinates center = Coordinates((soma_x/_points.size()),(soma_y/_points.size()));
	return center;
}
/* Transform every point of the object using a transformaton matrix */
void Object::transform(Matriz3x3 transformation){
	vector<Coordinates>::iterator it;
	for(it = _points.begin(); it != _points.end(); it++){
		double l4[] = {0,0,1};
		Coordinates point = (*it);
		l4[0] = point.get_x();
		l4[1] = point.get_y();
		Matriz1x3 point_matrix = Matriz1x3(l4);
		Matriz1x3 transformed_point = point_matrix.multiplicarPor3x3(transformation);
		(*it) = Coordinates(transformed_point.get(0), transformed_point.get(1));
	}
}
void Object::translate(double dx, double dy){
	double l0[] = {1,0,0};
	double l1[] = {0,1,0};
	double l2[] = {dx,dy,1};
	Matriz3x3 translation_matrix = Matriz3x3(l0,l1,l2);
	transform(translation_matrix);
}
void Object::scale(double sx, double sy){
	Coordinates center = get_geometric_center();
	double cx =  center.get_x();
	double cy =  center.get_y();
	double l0[] = {sx,0,0};
	double l1[] = {0,sy,0};
	double l2[] = {(-cx * sx) + cx,(-cy * sy) + cy, 1};
	Matriz3x3 scaling_matrix = Matriz3x3(l0,l1,l2);
	transform(scaling_matrix);
}
/* Angle in degrees, point is the point to rotate around*/
void Object::rotate(double angle, Coordinates point){
	/* Transforming angles from degrees to radians */
	angle = (M_PI / 180.0) * angle; 
	double px = point.get_x();
	double py = point.get_y();
	double l0[] = {cos(angle), -sin(angle), 0};
	double l1[] = {sin(angle),  cos(angle), 0};
	double l2_0 = (-px *  cos(angle)) + (-py * sin(angle)) + px;
	double l2_1 = (-px * -sin(angle)) + (-py * cos(angle)) + py;
	double l2[] = {l2_0, l2_1, 1};
	Matriz3x3 rotation_matrix = Matriz3x3(l0,l1,l2);
	transform(rotation_matrix);
}
/* 	Converts every point from _points to a _scn_point using the scn_matrix and stores 
	the new transformed point in the scn_points vector */
void Object::update_scn_points(Matriz3x3 scn_matrix){
	vector<Coordinates> new_scn_points;
	vector<Coordinates>::iterator it;
	for(it = _points.begin(); it != _points.end(); it++){
		double l4[] = {0,0,1};
		Coordinates point = (*it);
		l4[0] = point.get_x();
		l4[1] = point.get_y();
		Matriz1x3 point_matrix = Matriz1x3(l4);
		Matriz1x3 transformed_point = point_matrix.multiplicarPor3x3(scn_matrix);
		new_scn_points.push_back(Coordinates(transformed_point.get(0), transformed_point.get(1)));
	}
	_scn_points = new_scn_points;
}
void Object::clip(){
}
	/* For objects that only have one choice for clipping clip2 will be the same as clip */
void Object::clip2(){
	clip();
}
