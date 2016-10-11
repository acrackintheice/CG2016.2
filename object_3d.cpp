#include "object_3d.hpp"
#include <iostream>
#include "math.h"
#include "operations.cpp"
#include "matrices.cpp"

using namespace std;

Object_3d::~Object_3d(){
/*
	Need to delete all points
*/
	vector<Coordinates_3d*>::iterator it;
	for(it = _points.begin(); it != _points.end(); it++){
		Coordinates_3d* point = (*it);
		delete point;
	}
}
std::vector<Coordinates_3d*> Object_3d::get_points(){
	return _points;
}

string Object_3d::get_name(){
	return _name;
}

/* Returns the object's geometric center */
Coordinates_3d Object_3d::get_geometric_center(){
	double soma_x = 0;
	double soma_y = 0;
	double soma_z = 0;
	vector<Coordinates_3d*>::iterator it;
	for(it = _points.begin(); it != _points.end(); it++){
		Coordinates_3d* point = (*it);
		soma_x = soma_x + point->get_x();
		soma_y = soma_y + point->get_y();
		soma_z = soma_z + point->get_z();
	}
	Coordinates_3d center = Coordinates_3d((soma_x/_points.size()),(soma_y/_points.size()),(soma_z/_points.size()));
	return center;
}

/* Transform every point of the object using a transformation matrix*/
void Object_3d::transform(Matriz4x4 transformation){
	vector<Coordinates_3d*>::iterator it;
	for(it = _points.begin(); it != _points.end(); it++){
		double l4[] = {0,0,0,1};
		Coordinates_3d* point = (*it);
		l4[0] = point->get_x();
		l4[1] = point->get_y();
		l4[2] = point->get_z();
		Matriz1x4 point_matrix = Matriz1x4(l4);
		Matriz1x4 transformed_point = point_matrix.multiplicarPor4x4(transformation);
		(*it)->set_x(transformed_point.get(0));
		(*it)->set_y(transformed_point.get(1));
		(*it)->set_z(transformed_point.get(2));
	}
}

void Object_3d::translate(double dx, double dy, double dz){
	double l0[] = { 1,  0, 0, 0};
	double l1[] = { 0,  1, 0, 0};
	double l2[] = { 0,  0, 1, 0};
	double l3[] = {dx, dy, dz, 1};
	Matriz4x4 translation_matrix = Matriz4x4(l0,l1,l2,l3);
	transform(translation_matrix);
}

void Object_3d::scale(double sx, double sy, double sz){
	Coordinates_3d center = get_geometric_center();
	double cx =  center.get_x();
	double cy =  center.get_y();
	double cz =  center.get_z();
	double l0[] = {sx,              0,               0,               0};
	double l1[] = {0,               sy,              0,               0};
	double l2[] = {0,               0,               sz,              0};
	double l3[] = {(-cx * sx) + cx, (-cy * sy) + cy, (-cz * sz) + cz, 1};
	Matriz4x4 scaling_matrix = Matriz4x4(l0,l1,l2,l3);
	transform(scaling_matrix);
}

/* Angle in degrees, point is the point to rotate around */
void Object_3d::rotate(double angle, Coordinates_3d p1, Coordinates_3d p2){
	/* Transforming the angle to radians*/
	angle = (M_PI / 180.0) * angle;

	double x = p1.get_x();
	double y = p1.get_y();
	double z = p1.get_z();

	Coordinates_3d v = Coordinates_3d(p2.get_x() - p1.get_x(), p2.get_y() - p1.get_y(), p2.get_z() - p1.get_z());
	double norma_v = Operations::norma_3d(v);
	double a = v.get_x() / norma_v;
	double b = v.get_y() / norma_v;
	double c = v.get_z() / norma_v;
	double d = sqrt(a*a + c*c);

	Matriz4x4 tr_inv = Matrices::generate_tr_inv(x,y,z);
	Matriz4x4 ra_inv = Matrices::generate_ra_inv(c,b,d);
	Matriz4x4 rb_inv = Matrices::generate_rb_inv(a,d);
	Matriz4x4 r 	 = Matrices::generate_r(cos(angle), sin(angle));
	Matriz4x4 rb 	 = Matrices::generate_rb(a,d);
	Matriz4x4 ra 	 = Matrices::generate_ra(c,b,d);
	Matriz4x4 tr 	 = Matrices::generate_tr(x,y,z);

	
	Matriz4x4 rotation_matrix = tr_inv.multiplicarPor4x4(ra_inv).multiplicarPor4x4(rb_inv).multiplicarPor4x4(r).multiplicarPor4x4(rb).multiplicarPor4x4(ra).multiplicarPor4x4(tr);
	transform(rotation_matrix);
}

