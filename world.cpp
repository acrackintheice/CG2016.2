#include "world.hpp"

using namespace std;

World::World(Window* window)
{
    _window = window;
    add_object(window);
}
World::~World()
{
    for(vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); it++)
    {
        Object* obj = (*it);
        delete obj;
    }
}
void World::add_object(Object* obj)
{
    _objects.push_back(obj);
}
Object* World::get_object(string name)
{
    Object* chosen = 0;
    for(vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); it++)
    {
        Object* obj = (*it);
        if (obj->get_name() == name)
        {
            chosen = obj;
            break;
        }
    }
    return chosen;
}
vector<Object*> World::get_objects()
{
    return _objects;
}
void World::remove_object(string name)
{
    if(name != "Window")
    {
        for(vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); it++)
        {
            Object* obj = (*it);
            if (obj->get_name() == name)
            {
                _objects.erase(it);
                delete obj;
                break;
            }
        }
    }
}
Window* World::get_window()
{
    return _window;
}
void World::scn_upate()
{
    /* Creating a new window cause we don't want to mess with the world window */
    Window window = Window( 
        new Coordinates_3d(_window->get_p1()->get_x(), _window->get_p1()->get_y(), _window->get_p1()->get_z()),  
        new Coordinates_3d(_window->get_p2()->get_x(), _window->get_p2()->get_y(), _window->get_p1()->get_z()),
        new Coordinates_3d(_window->get_p3()->get_x(), _window->get_p3()->get_y(), _window->get_p1()->get_z()),
        new Coordinates_3d(_window->get_p4()->get_x(), _window->get_p4()->get_y(), _window->get_p1()->get_z()),
        new Coordinates_3d(_window->get_vup()->get_x(), _window->get_vup()->get_y(), _window->get_vup()->get_z()),
        new Coordinates_3d(_window->get_vpn()->get_x(), _window->get_vpn()->get_y(), _window->get_vpn()->get_z()));
    /* Defining the parameters for the scn transformation */
    /* dx and dy are pretty straightfoward*/
    double dx = -window.get_geometric_center().get_x();                                                              
    double dy = -window.get_geometric_center().get_y();
    /* Translating the window to the world origin in order to calculate the angle between the Vup vector and the Y axis*/
    window.translate(dx, dy, 0);
    /* The angle we will rotate the objects with in order to fix their orientation */
    double angle = -(Operations::angle_between_vectors(Coordinates_3d(0,10,0), *(window.get_vup())));
    /* Rotating the window to calculate the scaling factors */
    window.rotate(angle* 180.0 / M_PI, Coordinates_3d(0,0,0), Coordinates_3d(0,0,1));
    /* Well, these are the formulas for the scaling factors, we dont really know why */
    double sx = 1.0 / fabs(window.get_geometric_center().get_x() - window.get_p1()->get_x());                             
    double sy = 1.0 / fabs(window.get_geometric_center().get_y() - window.get_p1()->get_y());
    /* Now we have all the parameters so we can create the transformation matrix*/
    double l1[] = {sx*cos(angle), sx*(-sin(angle)), 0};
    double l2[] = {sy*sin(angle), sy*cos(angle)   , 0};
    double l3[] = {cos(angle)*(dx*sx) + sin(angle)*(dy*sy),-sin(angle)*(dx*sx) + cos(angle)*(dy*sy),1};
    Matriz3x3 scn_matrix = Matriz3x3(l1,l2,l3);
    /* Updating the objects SCN values */
    for(vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); it++)
    {
        Object* obj = (*it);
        obj-> update_scn_points(scn_matrix);
    }
}
void World::project_3d_objects(bool perspective)
{
   // cout << "Starting projection" << endl;
    Coordinates_3d vrp = _window->get_geometric_center();
    // Translate every object of -VRP 
    cout << "Before Translation" << endl;
    /*
    for(vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); it++)
    {
        Object* obj = (*it);
        obj->translate(-vrp.get_x(), -vrp.get_y(), -vrp.get_z());
    }
    */
    // Determine VPN and its angle with X and Y
    Coordinates_3d* N = _window->get_vpn();
    Coordinates_3d* V = _window->get_vup();
    
  //  cout << "N:" << endl;
  //  cout << N->to_string() << endl;

  //  cout << "V:" << endl;
  //  cout << V->to_string() << endl;

    double norma_N = Operations::norma_3d(N);

  //  cout << "Norma N:" << endl;
  //  cout << norma_N << endl;

    Coordinates_3d* n = new Coordinates_3d(N->get_x()/norma_N, N->get_y()/norma_N, N->get_z()/norma_N);

  //  cout << "n:" << endl;
 //   cout << n->to_string() << endl;

    Coordinates_3d* croos_V_N = Operations::cross_product_3d(V, N);

 //   cout << "croos_V_N:" << endl;
 //   cout << croos_V_N->to_string() << endl;

    double norma_cross_V_N = Operations::norma_3d(croos_V_N);

//    cout << "norma_cross_V_N N:" << endl;
  //  cout << norma_cross_V_N << endl;

    Coordinates_3d* u = new Coordinates_3d(croos_V_N->get_x()/norma_cross_V_N,
     croos_V_N->get_y()/norma_cross_V_N,
     croos_V_N->get_z()/norma_cross_V_N);

////    cout << "u:" << endl;
 //   cout << u->to_string() << endl;

    Coordinates_3d* v = Operations::cross_product_3d(n, u);

  //  cout << "v:" << endl;
 //   cout << v->to_string() << endl;

    double u1 = u->get_x();
    double u2 = u->get_y();
    double u3 = u->get_z();

    double v1 = v->get_x();
    double v2 = v->get_y();
    double v3 = v->get_z();

    double n1 = n->get_x();
    double n2 = n->get_y();
    double n3 = n->get_z();

    //cout << "Before rotation" << endl;
    //Rotate the world around X and Y in order to align VPN with Z
    double l1[] = {u1,u2,u3,0};
    double l2[] = {v1,v2,v3,0};
    double l3[] = {n1,n2,n3,0};
    double l4[] = { 0, 0, 0,1};
    Matriz4x4 rotation_matrix = Matriz4x4(l1,l2,l3,l4);

    for(vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); it++)
    {
        Object* obj = (*it);
        obj->project(rotation_matrix);
    }
    // Ignore Z for all objects
}
/*
gcc -pthread -I/usr/include/gtk-3.0 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/gtkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gtkmm-3.0/include -I/usr/include/atkmm-1.6 -I/usr/include/giomm-2.4 -I/usr/lib/x86_64-linux-gnu/giomm-2.4/include -I/usr/include/pangomm-1.4 -I/usr/lib/x86_64-linux-gnu/pangomm-1.4/include -I/usr/include/cairomm-1.0 -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include -I/usr/include/gtk-3.0/unix-print -I/usr/include/gdkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gdkmm-3.0/include -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include  -o vpl_wexecution coordenadas.cpp cor.cpp main.cpp mundo.cpp objeto.cpp ponto.cpp reta.cpp transformations.cpp ui.cpp window.cpp wireframe.cpp -lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 -lpangomm-1.4 -lgtk-3 -lglibmm-2.4 -lcairomm-1.0 -lgdk-3 -latk-1.0 -lgio-2.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lsigc-2.0 -lgobject-2.0 -lglib-2.0   -rdynamic -lstdc++ -std=c++11 -lm
*/









