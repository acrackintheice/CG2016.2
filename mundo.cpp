#include "mundo.hpp"
#include <iostream>

using namespace std;

Mundo::Mundo(Window* window){
    _window = window;
}

Mundo::~Mundo(){}

void Mundo::add_object(Objeto* obj){
    _objetos.push_back(obj);
}

vector<Objeto*> Mundo::get_objects(){
    return _objetos;
}
void Mundo::move_window(double x1_offset, double y1_offset, double x2_offset, double y2_offset){
    _window->move(x1_offset, x2_offset, y1_offset, y2_offset);
}
void Mundo::remove_object(string nome){
    vector<Objeto*>::iterator it;
    for(it = _objetos.begin(); it != _objetos.end(); it++){
        Objeto* obj = (*it);
        if (obj->get_name() == nome){
            _objetos.erase(it);
            delete obj;
            break;
        }
    }
}

Window* Mundo::get_window(){
    return _window;
}
















