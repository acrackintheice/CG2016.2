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
#include "matrices.cpp"

using namespace std;
/*
g++ `pkg-config --cflags gtk+-3.0` -o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp `pkg-config --libs gtk+-3.0`
*/

/*
gcc `pkg-config --cflags gtk+-3.0 gtkmm-3.0`-o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp cor.hpp cor.cpp ui.hpp ui.cpp `pkg-config --libs gtk+-3.0 gtkmm-3.0` -rdynamic -lstdc++ -std=c++11 -lm
*/

static void rotate(double angle, Coordinates_3d p1, Coordinates_3d p2, Coordinates_3d p3){
  /* Transforming the angle to radians*/
  double angleD = angle;
  angle = (M_PI / 180.0) * angle;
  double x = p1.get_x();
  double y = p1.get_y();
  double z = p1.get_z();

  Coordinates_3d v = Coordinates_3d(p2.get_x() - p1.get_x(), p2.get_y() - p1.get_y(), p2.get_z() - p1.get_z());
  double norma_v = Operations::norma_3d(v);
  double a = v.get_x() / norma_v;
  double b = v.get_y() / norma_v;
  double c = v.get_z() / norma_v;
  double d = sqrt(b*b + c*c);

  /*
  cout << "------------------------------------------- " << endl;
  cout << "Before " << endl;
  cout << p3.get_x() << endl;
  cout << p3.get_y() << endl;
  cout << p3.get_z() << endl;

  cout << "------------------------------------------- " << endl;
  cout << "V    : " << v.to_string() << endl;
  cout << "Norma: " << norma_v << endl;
  cout << "a    : " << a << endl;
  cout << "b    : " << b << endl;
  cout << "c    : " << c << endl;
  cout << "d    : " << d << endl;
  cout << "b/d  : " << b/d << endl;
  cout << "c/d  : " << c/d << endl;
  cout << "Angle: " << angleD << endl;
  cout << "Cos(Angle): " << cos(angle) << endl;
  cout << "Sin(Angle): " << sin(angle) << endl;
  cout << "------------------------------------------- " << endl;
  cout << "After" << endl;
  Matriz4x4 tr_inv = Matrices::generate_tr_inv(x,y,z);
  Matriz4x4 ra_inv = Matrices::generate_ra_inv(b,c,d);
  Matriz4x4 rb_inv = Matrices::generate_rb_inv(a,d);
  Matriz4x4 r      = Matrices::generate_r(cos(angle), sin(angle));
  Matriz4x4 rb     = Matrices::generate_rb(a,d);
  Matriz4x4 ra     = Matrices::generate_ra(b,c,d);
  Matriz4x4 tr     = Matrices::generate_tr(x,y,z);

  Matriz4x4 t_1 = tr_inv.multiplicarPor4x4(ra_inv);
  Matriz4x4 t_2 = t_1.multiplicarPor4x4(rb_inv);
  Matriz4x4 t_3 = t_2.multiplicarPor4x4(r);
  Matriz4x4 t_4 = t_3.multiplicarPor4x4(rb);
  Matriz4x4 t_5 = t_4.multiplicarPor4x4(ra);
  */
  Matriz4x4 rotation_matrix  = Matrices::generate_rotation_matrix(a,b,c,d,angle,x,y,z);
  Matriz4x1 point_matrix = Matriz4x1(p3.get_x(), p3.get_y(), p3.get_z(), 1);
  Matriz4x1 result_matrix = rotation_matrix.multiplicar4x1(point_matrix);
  /*
  8,23
  cout << "------------------------------------------- " << endl;
  cout << "Result 1: " << endl;
  cout << result_matrix.get(0) << endl;
  cout << result_matrix.get(1) << endl;
  cout << result_matrix.get(2) << endl;
  Matriz4x4 rotation_matrix2 = t_5.multiplicarPor4x4(tr);
  Matriz4x1 result_matrix2 = rotation_matrix2.multiplicar4x1(point_matrix);
  cout << "------------------------------------------- " << endl;
  cout << "Result 2: " << endl;
  cout << result_matrix2.get(0) << endl;
  cout << result_matrix2.get(1) << endl;
  cout << result_matrix2.get(2) << endl;
  cout << "------------------------------------------- " << endl;
  cout << " Matrices " << endl;
  cout << " tr inv " << endl;
  tr_inv.print();
  cout << endl;
  cout << " ra inv " << endl;
  ra_inv.print();
  cout << endl;
  cout << " tr inv * ra_inv" << endl;
  t_1.print();
  cout << endl;
  cout << " tr inv * ra inv * rb inv" << endl;
  t_2.print();
  cout << endl;
  cout << " tr inv * ra inv * rb inv * r" << endl;
  t_3.print();
  cout << endl;
  cout << " tr inv * ra inv * rb inv * r * rb" << endl;
  t_4.print();
  cout << endl;
  cout << " tr inv * ra inv * rb inv * r * rb * ra" << endl;
  t_5.print();
  cout << endl;
  cout << " tr inv * ra inv * rb inv * r * rb * ta * tr" << endl;
  rotation_matrix.print();
  cout << endl;
  cout << "------------------------------------------- " << endl;
  */
  //transform(rotation_matrix);
}
int main (int argc, char *argv[]){
  rotate(15 , Coordinates_3d(0,0,0), Coordinates_3d(0,0,1), Coordinates_3d(10,10,0));
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
  curve_points.push_back(Coordinates(0,-70));
  curve_points.push_back(Coordinates(-65,-30));
  curve_points.push_back(Coordinates(-65,30));  

 /* (0,-70) (-65,-30) (-65,30) (0,70) (65,30) (65,-30) (0,-70) (-65,-30) (-65,30) */

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
