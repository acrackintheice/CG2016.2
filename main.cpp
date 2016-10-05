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
#include <algorithm>
#include "math.h"
#include "operations.cpp"
#include "curve.hpp"
#include "bspline.hpp"

using namespace std;
/*
g++ `pkg-config --cflags gtk+-3.0` -o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp `pkg-config --libs gtk+-3.0`
*/

/*
gcc `pkg-config --cflags gtk+-3.0 gtkmm-3.0`-o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp cor.hpp cor.cpp ui.hpp ui.cpp `pkg-config --libs gtk+-3.0 gtkmm-3.0` -rdynamic -lstdc++ -std=c++11 -lm
*/
int main (int argc, char *argv[]){
  Window* window = new Window(Coordinates(-500, -500), Coordinates(500,500), Coordinates(0,500));
  World* world   = new World(window);
  vector<Coordinates> square_points;
  square_points.push_back(Coordinates(-500,0));
  square_points.push_back(Coordinates(0,500));
  square_points.push_back(Coordinates(500,0));
  square_points.push_back(Coordinates(0,-500));
  Polygon* pol = new Polygon(square_points, "Square", new Color(0,0,0,1), new Color(1,1,1,1), false);
  vector<Coordinates> wireframe_points;
  wireframe_points.push_back(Coordinates(0,0));
  wireframe_points.push_back(Coordinates(0,200));
  wireframe_points.push_back(Coordinates(200,200));
  wireframe_points.push_back(Coordinates(200,0));
  Wireframe* w = new Wireframe(wireframe_points, "Wireframe", new Color(0,0,255,1));
  vector<Coordinates> curve_points;
  curve_points.push_back(Coordinates(0,-70));
  curve_points.push_back(Coordinates(-65,-30));
  curve_points.push_back(Coordinates(-65,30));
  curve_points.push_back(Coordinates(0,70));
  curve_points.push_back(Coordinates(65, 30));
  curve_points.push_back(Coordinates(65, -30));
  //curve_points.push_back(Coordinates(0,-400));
  //curve_points.push_back(Coordinates(300,-150));
  //curve_points.push_back(Coordinates(-300,150));  
  BSpline* c = new BSpline(curve_points, "Curve", new Color(0,0,255,1));
  Point* p1 = new Point(Coordinates(0,-70), "P1-Spline", new Color(0,0,0,1));
  Point* p2 = new Point(Coordinates(-65,-30), "P2-Spline", new Color(255,0,0,1));
  Point* p3 = new Point(Coordinates(-65,30), "P3-Spline", new Color(255,0,0,1));
  Point* p4 = new Point(Coordinates(0,70), "P4-Spline", new Color(255,0,0,1));
  Point* p5 = new Point(Coordinates(65, 30), "P5-Spline", new Color(255,0,0,1));
  Point* p6 = new Point(Coordinates(65, -30), "P6-Spline", new Color(255,0,0,1));
  world->add_object(c);
  world->add_object(pol);
  world->add_object(p1);
  world->add_object(p2);
  world->add_object(p3);
  world->add_object(p4);
  world->add_object(p5);
  world->add_object(p6);
  UI ui = UI(argc, argv, world);
  return 0;
}
