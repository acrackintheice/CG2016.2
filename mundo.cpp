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
Objeto* Mundo::get_object(string name){
    Objeto* chosen = 0;
    vector<Objeto*>::iterator it;
    for(it = _objetos.begin(); it != _objetos.end(); it++){
        Objeto* obj = (*it);
        if (obj->get_name() == name){
            chosen = obj;
            break;
        }
    }
    return chosen;
}

vector<Objeto*> Mundo::get_objects(){
    return _objetos;
}
void Mundo::move_window(double x1_offset, double y1_offset, double x2_offset, double y2_offset){
    _window->move(x1_offset, x2_offset, y1_offset, y2_offset);
}
void Mundo::remove_object(string name){
    vector<Objeto*>::iterator it;
    for(it = _objetos.begin(); it != _objetos.end(); it++){
        Objeto* obj = (*it);
        if (obj->get_name() == name){
            _objetos.erase(it);
            delete obj;
            break;
        }
    }
}

Window* Mundo::get_window(){
    return _window;
}

/*

gcc -pthread -I/usr/include/gtk-3.0 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/gtkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gtkmm-3.0/include -I/usr/include/atkmm-1.6 -I/usr/include/giomm-2.4 -I/usr/lib/x86_64-linux-gnu/giomm-2.4/include -I/usr/include/pangomm-1.4 -I/usr/lib/x86_64-linux-gnu/pangomm-1.4/include -I/usr/include/cairomm-1.0 -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include -I/usr/include/gtk-3.0/unix-print -I/usr/include/gdkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gdkmm-3.0/include -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include  -o vpl_wexecution coordenadas.cpp cor.cpp main.cpp mundo.cpp objeto.cpp ponto.cpp reta.cpp transformations.cpp ui.cpp window.cpp wireframe.cpp -lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 -lpangomm-1.4 -lgtk-3 -lglibmm-2.4 -lcairomm-1.0 -lgdk-3 -latk-1.0 -lgio-2.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lsigc-2.0 -lgobject-2.0 -lglib-2.0   -rdynamic -lstdc++ -std=c++11 -lm


*/









