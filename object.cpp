#include "object.hpp"

using namespace std;


Object::~Object()
{
	delete _color;
	delete _background_color;
	for(vector<Coordinates_3d*>::iterator it = _points.begin(); it != _points.end(); it++)
	{
		Coordinates_3d* point = (*it);
		delete point;
	}
}
/* 
Return the list of points to be drawn, in the general case this list is the _scn_points list. 
It might change for especific objects, so they will need to overwrite this method.
*/
vector<Coordinates_3d*> Object::get_points()
{
	return _points;
}
vector<Edge> Object::get_edges()
{
	return _edges;
}
string Object::get_name()
{
	return _name;
}
Color* Object::get_color()
{
	return _color;
}
Color* Object::get_background_color()
{
	return _color;
}
bool Object::is_filled()
{
	return _filled;
}
/* Prints the object's data */
string Object::to_string()
{
	int i = 0;
	string s = _name;
	for(vector<Coordinates_3d*>::iterator it = _points.begin(); it != _points.end(); it++, i++)
	{
		Coordinates_3d* point = (*it);
		string x = std::to_string(point->get_x());
		string y = std::to_string(point->get_y());
		string z = std::to_string(point->get_z());
		s = s + "\n" + "Ponto " + std::to_string(i) + " : (" + x + ", " + y + ", " + z + ")";
		i++;
	}
	return s;
}
/* Returns the object's geometric center */
Coordinates_3d Object::get_geometric_center()
{
	double soma_x = 0;
	double soma_y = 0;
	double soma_z = 0;
	for(vector<Coordinates_3d*>::iterator it = _points.begin(); it != _points.end(); it++)
	{
		Coordinates_3d* point = (*it);
		soma_x = soma_x + point->get_x();
		soma_y = soma_y + point->get_y();
		soma_z = soma_z + point->get_z();
	}
	return Coordinates_3d((soma_x/_points.size()),(soma_y/_points.size()),(soma_z/_points.size()));
}
/* Transform every point of the object using a transformation matrix*/
void Object::transform(Matriz4x4 transformation)
{
	for(vector<Coordinates_3d*>::iterator it = _points.begin(); it != _points.end(); it++)
	{
		Coordinates_3d* point = (*it);
		double l4[] = {point->get_x(), point->get_y(), point->get_z(),1};
		Matriz1x4 transformed_point = Matriz1x4(l4).multiplicarPor4x4(transformation);
		(*it)->set_x(transformed_point.get(0));
		(*it)->set_y(transformed_point.get(1));
		(*it)->set_z(transformed_point.get(2));
	}
}
/* Transform every point of the object using a transformation matrix*/
void Object::transform2(Matriz4x4 transformation)
{
	for(vector<Coordinates_3d*>::iterator it = _points.begin(); it != _points.end(); it++)
	{
		Coordinates_3d* point = (*it);
		Matriz4x1 transformed_point = transformation.multiplicar4x1(Matriz4x1(point->get_x(), point->get_y(), point->get_z(), 1));
		(*it)->set_x(transformed_point.get(0));
		(*it)->set_y(transformed_point.get(1));
		(*it)->set_z(transformed_point.get(2));
	}
}

void Object::translate(double dx, double dy, double dz)
{
	transform(Matrices::generate_translation_matrix(dx,dy,dz));
}
void Object::scale(double sx, double sy, double sz)
{
	Coordinates_3d center = get_geometric_center();
	double cx =  center.get_x();
	double cy =  center.get_y();
	double cz =  center.get_z();
	transform(Matrices::generate_scaling_matrix(sx,sy,sz,cx,cy,cz));
}
void Object::rotate_x(double angle)
{
	angle = (M_PI / 180.0) * angle;
	transform(Matrices::generate_rotate_x_matrix(angle));
}
void Object::rotate_y(double angle)
{
	angle = (M_PI / 180.0) * angle;
	transform(Matrices::generate_rotate_y_matrix(angle));
}
void Object::rotate_z(double angle)
{
	angle = (M_PI / 180.0) * angle;
	transform(Matrices::generate_rotate_z_matrix(angle));
}
/* Rotate by angle around an axis defined by P1 -> P2 */
void Object::rotate(double angle, Coordinates_3d p1, Coordinates_3d p2)
{
  	/* Transforming the angle to radians*/
	angle = (M_PI / 180.0) * angle;
	double x = p1.get_x();
	double y = p1.get_y();
	double z = p1.get_z();

	Coordinates_3d v = Coordinates_3d(p2.get_x() - p1.get_x(), p2.get_y() - p1.get_y(), p2.get_z() - p1.get_z());
	double norma_v = Operations::norma_3d(&v);
	double a = v.get_x() / norma_v;
	double b = v.get_y() / norma_v;
	double c = v.get_z() / norma_v;
	double d = sqrt(b*b + c*c);
	if(d)
	{
		Matriz4x4 rotation_matrix  = Matrices::generate_rotation_matrix(a,b,c,d,angle,x,y,z);
		transform2(rotation_matrix);
	}
	else
	{
		cout << "Rotação cancelada pois d = 0, se você estiver rotacionado" <<
		        "redor de um eixo do mundo utilize a rotação específica"    << endl;
	}
}
/* 	Converts every point from _points to a _scn_point using the scn_matrix and stores 
	the new transformed point in the scn_points vector */
void Object::update_scn_points(Matriz3x3 scn_matrix)
{
	for(vector<Coordinates_3d*>::iterator it = _points.begin(); it != _points.end(); it++)
	{
		Coordinates_3d* point = (*it);
		double l4[] = {point->get_x(),point->get_y(),1};
		Matriz1x3 transformed_point = Matriz1x3(l4).multiplicarPor3x3(scn_matrix);
		point->set_x_scn(transformed_point.get(0));
		point->set_y_scn(transformed_point.get(1));
	}
}
void Object::project(Matriz4x4 rotation_matrix)
{
	for(vector<Coordinates_3d*>::iterator it = _points.begin(); it != _points.end(); it++)
	{
		double l4[] = {0,0,0,1};
		Coordinates_3d* point = (*it);
		l4[0] = point->get_x();
		l4[1] = point->get_y();
		l4[2] = point->get_z();
		Matriz1x4 point_matrix = Matriz1x4(l4);
		Matriz1x4 transformed_point = point_matrix.multiplicarPor4x4(rotation_matrix);
		point->set_x_scn(transformed_point.get(0));
		point->set_y_scn(transformed_point.get(1));
		point->set_z_scn(transformed_point.get(2));
	}
}
std::vector<Edge> Object::clip()
{
	return _edges;
}
	/* For objects that only have one choice for clipping clip2 will be the same as clip */
std::vector<Edge> Object::clip2()
{
	return clip();
}