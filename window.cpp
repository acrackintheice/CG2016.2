#include "window.hpp"
#include <vector>
#include <iostream>

using namespace std;

Window::Window(Coordinates p1, Coordinates p2, Coordinates vup) : _vup(vup)
{
    _name = "window";
    _points.push_back(p1);
    _points.push_back(p2);
}
Window::~Window(){
}
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
    // Getting the old points
    Coordinates p1 = _points[0];
    Coordinates p2 = _points[1];
    // Creating new x and y values
    double new_x1 = p1.get_x()+value;
    double new_y1 = p1.get_y()+value;
    double new_x2 = p2.get_x()-value;
    double new_y2 = p2.get_y()-value;
    // Checking if zooming will not break the window
    if(new_x1 < new_x2 && new_y1 < new_y2){
        // Creating new points with the added offsets
        Coordinates new_p1 = Coordinates(new_x1, new_y1);
        Coordinates new_p2 = Coordinates(new_x2, new_y2);
        // Setting the new points as current
        _points[0] = new_p1;
        _points[1] = new_p2;
    }
    else{
        // If zoom breaks the window we give a message
        cout << "Limite do Zoom" << endl;
    }
}

void Window::zoom_out(double value){
    // Getting the old points
    Coordinates p1 = _points[0];
    Coordinates p2 = _points[1];
    // Creating new x and y values
    double new_x1 = p1.get_x()-value;
    double new_y1 = p1.get_y()-value;
    double new_x2 = p2.get_x()+value;
    double new_y2 = p2.get_y()+value;
    
    // Even tough zoom out never breaks the window, i'm testing for the same problem that happened in the zoom in
    if(new_x1 < new_x2 && new_y1 < new_y2){
        // Creating new points with the added offsets+
        Coordinates new_p1 = Coordinates(new_x1, new_y1);
        Coordinates new_p2 = Coordinates(new_x2, new_y2);
        // Setting the new points as current
        _points[0] = new_p1;
        _points[1] = new_p2;
    }
    else{
        // Should never happen
        cout << "Zoom limit" << endl;
    }
}

void Window::move(double x1_offset, double y1_offset, double x2_offset, double y2_offset){
    // Getting the old points
    Coordinates p1 = _points[0];
    Coordinates p2 = _points[1];
    // Creating new points with the added offsets+
    Coordinates new_p1 = Coordinates(p1.get_x()+x1_offset, p1.get_y()+y1_offset);
    Coordinates new_p2 = Coordinates(p2.get_x()+x2_offset, p2.get_y()+y2_offset);
    // Setting the new points as current
    _points[0] = new_p1;
    _points[1] = new_p2;
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
