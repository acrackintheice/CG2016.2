#include "window.hpp"
#include <vector>
#include <iostream>

using namespace std;

Window::Window(Coordenadas *p1, Coordenadas *p2)
{
    _name = "window";
    _pontos.push_back(p1);
    _pontos.push_back(p2);
}
Window::~Window(){
    vector<Coordenadas*>::iterator it;
    for(it = _pontos.begin(); it != _pontos.end(); it++){
        delete  *it;
    }
}

void Window::zoom_in(double value){
      // Getting the old points
    Coordenadas* p1 = _pontos[0];
    Coordenadas* p2 = _pontos[1];
    // Creating new points with the added offsets+
    Coordenadas* new_p1 = new Coordenadas(p1->get_x()+value, p1->get_y()+value);
    Coordenadas* new_p2 = new Coordenadas(p2->get_x()-value, p2->get_y()-value);
    // Setting the new points as current
    if(new_p1->get_x() < new_p2->get_x() && new_p1->get_y() < new_p2->get_y()){
        _pontos[0] = new_p1;
        _pontos[1] = new_p2;
        // Deleting the old poitns
        delete p1;
        delete p2;
    }
    else{
        cout << "Limite do Zoom" << endl;
    }
}

void Window::zoom_out(double value){
      // Getting the old points
    Coordenadas* p1 = _pontos[0];
    Coordenadas* p2 = _pontos[1];
    // Creating new points with the added offsets+
    Coordenadas* new_p1 = new Coordenadas(p1->get_x()-value, p1->get_y()-value);
    Coordenadas* new_p2 = new Coordenadas(p2->get_x()+value, p2->get_y()+value);
    // Setting the new points as current
    if(new_p1->get_x() < new_p2->get_x() && new_p1->get_y() < new_p2->get_y()){
        _pontos[0] = new_p1;
        _pontos[1] = new_p2;
        // Deleting the old poitns
        delete p1;
        delete p2;
    }
    else{
        cout << "Limite do Zoom" << endl;
    }
}

void Window::move(double x1_offset, double y1_offset, double x2_offset, double y2_offset){
    // Getting the old points
    Coordenadas* p1 = _pontos[0];
    Coordenadas* p2 = _pontos[1];
    // Creating new points with the added offsets+
    Coordenadas* new_p1 = new Coordenadas(p1->get_x()+x1_offset, p1->get_y()+y1_offset);
    Coordenadas* new_p2 = new Coordenadas(p2->get_x()+x2_offset, p2->get_y()+y2_offset);
    // Setting the new points as current
    _pontos[0] = new_p1;
    _pontos[1] = new_p2;
    // Deleting the old poitns
    delete p1;
    delete p2;
}

Coordenadas* Window::get_min(){
    return _pontos[0];
}

Coordenadas* Window::get_max(){
    return _pontos[1];
}


/*
Coordenadas* Window::transformada_viewport(Coordenadas *c, Viewport* vp){
    double Xw     = c->get_x();
    double Xwmin  = _pontos.at(0)->get_x();
    double Xwmax  = _pontos.at(2)->get_x();
    double Xvpmax = vp->getMax()->get_x();
    double Xvpmin = vp->getMin()->get_x();

    double Yw     = c->get_y();
    double Ywmin  = _pontos.at(0)->get_y();
    double Ywmax  = _pontos.at(2)->get_y();
    double Yvpmax = vp->getMax()->get_y();
    double Yvpmin = vp->getMin()->get_y();

    double xv =     (((Xw - Xwmin) / (Xwmax - Xwmin))  * (Xvpmax - Xvpmin));
    double yv = ((1- ((Yw - Ywmin) / (Ywmax - Ywmin))) * (Yvpmax - Yvpmin));

    return new Coordenadas(xv,yv);
}
*/
