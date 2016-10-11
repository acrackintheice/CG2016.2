#include "window_3d.hpp"
#include "operations.cpp"
#include <vector>
#include <iostream>

using namespace std;

Window_3d::Window_3d(Coordinates_3d* p1, Coordinates_3d* p2, Coordinates_3d* p3, Coordinates_3d* p4, Coordinates_3d* vup)
{
    _vup = vup;
    _name = "Window_3d";
    _points.push_back(p1);
    _points.push_back(p2);
    _points.push_back(p3);
    _points.push_back(p4);
    _edges.push_back(new Edge(p1,p2));
    _edges.push_back(new Edge(p2,p3));
    _edges.push_back(new Edge(p3,p4));
    _edges.push_back(new Edge(p4,p1));
}
Window_3d::~Window_3d(){
/*
    Need to delete some things now
*/
}
std::vector<Edge*> Window_3d::get_edges(){
    return _edges;
}
/* 
The window's transform function is different from the Object's one because  
it also needs to transform the Vup vector
*/
void Window_3d::transform(Matriz4x4 transformation){
    /* Transforming the points */
    /*
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
    */
    /* Transforming the vup vector*/
    /*
    double l4[] = {0,0,1};
    Coordinates point = _vup;
    l4[0] = point.get_x();
    l4[1] = point.get_y();
    Matriz1x3 point_matrix = Matriz1x3(l4);
    Matriz1x3 transformed_point = point_matrix.multiplicarPor3x3(transformation);
    _vup = Coordinates(transformed_point.get(0), transformed_point.get(1));
    */
}
void Window_3d::zoom_in(double value){
    /* 
    Coordinates p1 = _points[0];
    Coordinates p2 = _points[1];
    double new_x1 = p1.get_x()+value;
    double new_y1 = p1.get_y()+value;
    double new_x2 = p2.get_x()-value;
    if(new_x1 < new_x2 && new_y1 < new_y2){
        Coordinates new_p1 = Coordinates(new_x1, new_y1);
        Coordinates new_p2 = Coordinates(new_x2, new_y2);
        _points[0] = new_p1;
        _points[1] = new_p2;
    }
    else{
        cout << "Limite do Zoom" << endl;
    }
    */
}
void Window_3d::zoom_out(double value){
    /*
    Coordinates p1 = _points[0];
    Coordinates p2 = _points[1];
    double new_x1 = p1.get_x()-value;
    double new_y1 = p1.get_y()-value;
    double new_x2 = p2.get_x()+value;
    double new_y2 = p2.get_y()+value;
    if(new_x1 < new_x2 && new_y1 < new_y2){
        Coordinates new_p1 = Coordinates(new_x1, new_y1);
        Coordinates new_p2 = Coordinates(new_x2, new_y2);
        _points[0] = new_p1;
        _points[1] = new_p2;
    }
    else{
        cout << "Zoom limit" << endl;
    }
    */
}
void Window_3d::move(double dx, double dy){
    /*
    double rad = get_vup_angle() - (M_PI / 2);
    double l1[] = {1,0,0};
    double l2[] = {0,1,0};
    double l3[] = {
    		dx*cos(rad) + dy*sin(rad),
    		dx*-sin(rad) + dy*cos(rad),
    		1};
    Matriz3x3 resultant(l1,l2,l3);
    transform(resultant);
    */
}
Coordinates_3d* Window_3d::get_min(){
    return _points[0];
}
Coordinates_3d* Window_3d::get_max(){
    return _points[1];
}
Coordinates_3d* Window_3d::get_vup(){
    return _vup;
}
double Window_3d::get_vup_angle(){
	/*
    //Getting the window's center
    Coordinates center = get_geometric_center();
    //Getting the vector that indicates the upward direction of the window
    Coordinates window_vup = Coordinates(center.get_x()-_vup.get_x(), -(center.get_y()-_vup.get_y()));
    //Getting the length (magnitude) of the window_vup
	double length = sqrt(pow(window_vup.get_x(),2)+pow(window_vup.get_y(),2));
	//Normalizing the window_vup
	Coordinates normalized_window_vup = Coordinates(window_vup.get_x()/length, window_vup.get_y()/length);
	//Getting the angle of the window in radians
	double radians = acos(normalized_window_vup.get_x()) * ((normalized_window_vup.get_y()<0) ? -1 : 1);
	return radians;
    */
}
