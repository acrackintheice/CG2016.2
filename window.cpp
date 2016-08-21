#include "window.hpp"
#include <vector>
#include <iostream>

using namespace std;

Window::Window(Coordinates p1, Coordinates p2)
{
    _name = "window";
    _points.push_back(p1);
    _points.push_back(p2);
}
Window::~Window(){
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