#include "window.hpp"
#include "operations.cpp"
#include <vector>
#include <iostream>

using namespace std;

Window::Window(Coordinates p1, Coordinates p2, Coordinates vup) : _vup(vup)
{
    _name = "Window";
    _points.push_back(p1);
    _points.push_back(p2);
    _scn_points = _points;
}
Window::~Window(){
}

std::vector<Coordinates> Window::get_drawing_points(){
    std::vector<Coordinates> drawing_points;
    Coordinates min = _scn_points[0];
    Coordinates max = _scn_points[1];

    drawing_points.push_back(min);
    drawing_points.push_back(Coordinates(min.get_x(), max.get_y()));
    drawing_points.push_back(max);
    drawing_points.push_back(Coordinates(max.get_x(), min.get_y()));
    drawing_points.push_back(min);
    return drawing_points;
}
/* 
The window's transform function is different from the Object's one because  
it also needs to transform the Vup vector
*/
void Window::transform(Matriz3x3 transformation){
    /* Transforming the points */
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
    /* Transforming the vup vector*/
    double l4[] = {0,0,1};
    Coordinates point = _vup;
    l4[0] = point.get_x();
    l4[1] = point.get_y();
    Matriz1x3 point_matrix = Matriz1x3(l4);
    Matriz1x3 transformed_point = point_matrix.multiplicarPor3x3(transformation);
    _vup = Coordinates(transformed_point.get(0), transformed_point.get(1));
}
void Window::zoom_in(double value){
    /* Getting the old points */
    Coordinates p1 = _points[0];
    Coordinates p2 = _points[1];
    /* Creating new x and y values */
    double new_x1 = p1.get_x()+value;
    double new_y1 = p1.get_y()+value;
    double new_x2 = p2.get_x()-value;
    double new_y2 = p2.get_y()-value;
    /* Checking if zooming will not break the window */
    if(new_x1 < new_x2 && new_y1 < new_y2){
        /* Creating new points with the added offsets */
        Coordinates new_p1 = Coordinates(new_x1, new_y1);
        Coordinates new_p2 = Coordinates(new_x2, new_y2);
        /* Setting the new points as current */
        _points[0] = new_p1;
        _points[1] = new_p2;
    }
    else{
        /* If zoom breaks the window we give a message(doesnt happen anymore) */
        cout << "Limite do Zoom" << endl;
    }
}
void Window::zoom_out(double value){
    /* Getting the old points */
    Coordinates p1 = _points[0];
    Coordinates p2 = _points[1];
    /* Creating new x and y values */
    double new_x1 = p1.get_x()-value;
    double new_y1 = p1.get_y()-value;
    double new_x2 = p2.get_x()+value;
    double new_y2 = p2.get_y()+value;

    /* Even tough zoom out never breaks the window, i'm testing for the same problem that happened in the zoom in */
    if(new_x1 < new_x2 && new_y1 < new_y2){
        /* Creating new points with the added offsets */
        Coordinates new_p1 = Coordinates(new_x1, new_y1);
        Coordinates new_p2 = Coordinates(new_x2, new_y2);
        /* Setting the new points as current */
        _points[0] = new_p1;
        _points[1] = new_p2;
    }
    else{
        /* Should never happen */
        cout << "Zoom limit" << endl;
    }
}
void Window::move(double dx, double dy){
	//Getting the difference of the view-up of the window and 90ª (view-up of the world)
    double rad = get_vup_angle() - (M_PI / 2);
    /*
    //Naming variables in a character (to use in WolframAlpha):
    center = get_geometric_center();
    a = center.get_x();
    b = center.get_y();
    c = dx;
    d = dy;
    u = rad;

	//Matrices of transformations (1 per line) to move the window:
    ---------------------------
    {{1,0,0},{0,1,0},{-a,-b,1}}*
    {{cos(-u),-sin(-u),0},{sin(-u),cos(-u),0},{0,0,1}}*
    {{1,0,0},{0,1,0},{c,d,1}}*
    {{cos(u),-sin(u),0},{sin(u),cos(u),0},{0,0,1}}*
    {{1,0,0},{0,1,0},{a,b,1}}
	---------------------------
    //Use WolframAlpha to obtain the resultant matrix (and a nice vision of the matrices).
    */
    double l1[] = {1,0,0};
    double l2[] = {0,1,0};
    double l3[] = {
    		dx*cos(rad) + dy*sin(rad),
    		dx*-sin(rad) + dy*cos(rad),
    		1};
    Matriz3x3 resultant(l1,l2,l3);
    this->transform(resultant);
}
Coordinates Window::get_min(){
    return _points[0];
}
Coordinates Window::get_max(){
    return _points[1];
}
Coordinates Window::get_vup(){
    return _vup;
}
double Window::get_vup_angle(){
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
}
