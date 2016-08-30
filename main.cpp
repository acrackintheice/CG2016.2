#include <gtk/gtk.h>
#include "point.hpp"
#include "line.hpp"
#include "object.hpp"
#include "coordinates.hpp"
#include "wireframe.hpp"
#include "ui.hpp"
#include "world.hpp"
#include "window.hpp"
#include <vector>
#include <iostream>
#include "math.h"

using namespace std;

/*
g++ `pkg-config --cflags gtk+-3.0` -o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp `pkg-config --libs gtk+-3.0`
*/

/*
gcc `pkg-config --cflags gtk+-3.0 gtkmm-3.0`-o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp cor.hpp cor.cpp ui.hpp ui.cpp `pkg-config --libs gtk+-3.0 gtkmm-3.0` -rdynamic -lstdc++ -std=c++11 -lm
*/
int main (int argc, char *argv[]){
  Window* window = new Window(Coordinates(-600, -600), Coordinates(600,600), Coordinates(0,600));
  World* world   = new World(window);
  vector<Coordinates> square_points;
  square_points.push_back(Coordinates(32,32));
  square_points.push_back(Coordinates(32,322));
  square_points.push_back(Coordinates(322,322));
  square_points.push_back(Coordinates(322,32));
  Polygon* pol = new Polygon(square_points, "Square");
  Point* p = new Point(Coordinates(0,0), "Point");
  Line* r =  new Line(Coordinates(10, 150), Coordinates(10,450), "Line");
  world->add_object(pol);
  world->add_object(p);
  world->add_object(r);
  UI ui = UI(argc, argv, world);
  return 0;
}
