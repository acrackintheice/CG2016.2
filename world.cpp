#include "world.hpp"
#include <iostream>
#include "math.h"
#include "operations.cpp"

using namespace std;

World::World(Window* window) : _window(window), _clip_flag(false)
{
    add_object(window);
}
World::~World(){
    vector<Object*>::iterator it;
    for(it = _objects.begin(); it != _objects.end(); it++){
        Object* obj = (*it);
        delete obj;
    }
}
void World::set_clip_flag(bool clip_flag){
    _clip_flag = clip_flag;
}
void World::add_object(Object* obj){
    _objects.push_back(obj);
}
Object* World::get_object(string name){
    Object* chosen = 0;
    vector<Object*>::iterator it;
    for(it = _objects.begin(); it != _objects.end(); it++){
        Object* obj = (*it);
        if (obj->get_name() == name){
            chosen = obj;
            break;
        }
    }
    return chosen;
}
vector<Object*> World::get_objects(){
    return _objects;
}
void World::remove_object(string name){
    if(name != "Window"){
        vector<Object*>::iterator it;
        for(it = _objects.begin(); it != _objects.end(); it++){
            Object* obj = (*it);
            if (obj->get_name() == name){
                _objects.erase(it);
                delete obj;
                break;
            }
        }
    }
}
Window* World::get_window(){
    return _window;
}
void World::clip(){
    vector<Object*>::iterator it;
    for(it = _objects.begin(); it != _objects.end(); it++){
        Object* obj = (*it);
        if (_clip_flag){
            obj-> clip2();
        }
        else{
            obj-> clip();
        }
    }
}
void World::scn_upate(){
    /* Creating a new window cause we don't want to mess with the world window */
    Window window = Window( _window->get_min(), _window->get_max(), _window->get_vup());
    /* Defining the parameters for the scn transformation */
    /* dx and dy are pretty straightfoward*/
    double dx = -window.get_geometric_center().get_x();                                                              
    double dy = -window.get_geometric_center().get_y(); 
    /* Translating the window to the world origin in order to calculate the angle between the Vup vector and the Y axis*/
    window.translate(dx, dy);
    /* The angle we will rotate the objects with in order to fix their orientation */
    double angle = -(Operations::angle_between_vectors(Coordinates(0,10), window.get_vup()));
    /* Rotating the window to calculate the scaling factors */
    window.rotate(angle* 180.0 / M_PI, Coordinates(0,0));
    /* Well, these are the formulas for the scaling factors, we dont really know why */
    double sx = 1.0 / fabs(window.get_geometric_center().get_x() - window.get_min().get_x());                             
    double sy = 1.0 / fabs(window.get_geometric_center().get_y() - window.get_min().get_y());
    /* Now we have all the parameters so we can create the transformation matrix*/
    double l1[] = {sx*cos(angle), sx*(-sin(angle)), 0};
    double l2[] = {sy*sin(angle), sy*cos(angle)   , 0};
    double l3[] = {cos(angle)*(dx*sx) + sin(angle)*(dy*sy),-sin(angle)*(dx*sx) + cos(angle)*(dy*sy),1};
    Matriz3x3 scn_matrix = Matriz3x3(l1,l2,l3);
    /* Updating the objects SCN values */
    vector<Object*>::iterator it;
    for(it = _objects.begin(); it != _objects.end(); it++){
        Object* obj = (*it);
        obj-> update_scn_points(scn_matrix);
    }
}
/*
gcc -pthread -I/usr/include/gtk-3.0 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/gtkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gtkmm-3.0/include -I/usr/include/atkmm-1.6 -I/usr/include/giomm-2.4 -I/usr/lib/x86_64-linux-gnu/giomm-2.4/include -I/usr/include/pangomm-1.4 -I/usr/lib/x86_64-linux-gnu/pangomm-1.4/include -I/usr/include/cairomm-1.0 -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include -I/usr/include/gtk-3.0/unix-print -I/usr/include/gdkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gdkmm-3.0/include -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include  -o vpl_wexecution coordenadas.cpp cor.cpp main.cpp mundo.cpp objeto.cpp ponto.cpp reta.cpp transformations.cpp ui.cpp window.cpp wireframe.cpp -lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 -lpangomm-1.4 -lgtk-3 -lglibmm-2.4 -lcairomm-1.0 -lgdk-3 -latk-1.0 -lgio-2.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lsigc-2.0 -lgobject-2.0 -lglib-2.0   -rdynamic -lstdc++ -std=c++11 -lm
*/









