#include <gtk/gtk.h>
#include "ponto.hpp"
#include "reta.hpp"
#include "objeto.hpp"
#include "coordenadas.hpp"
#include "wireframe.hpp"
#include "ui.hpp"
#include "mundo.hpp"
#include "window.hpp"
#include <vector>
#include <iostream>
using namespace std;

/*
g++ `pkg-config --cflags gtk+-3.0` -o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp `pkg-config --libs gtk+-3.0`
*/

/*
gcc `pkg-config --cflags gtk+-3.0 gtkmm-3.0`-o simple main.cpp reta.hpp reta.cpp objeto.hpp objeto.cpp coordenadas.hpp coordenadas.cpp ponto.hpp ponto.cpp wireframe.hpp wireframe.cpp cor.hpp cor.cpp ui.hpp ui.cpp `pkg-config --libs gtk+-3.0 gtkmm-3.0` -rdynamic -lstdc++ -std=c++11 -lm
*/

int main (int argc, char *argv[]){
  Window* window = new Window(new Coordenadas(0,0), new Coordenadas(500,500));
  Mundo* mundo = new Mundo(window);
  UI* ui = new UI(argc, argv, mundo);
  Reta* r = new Reta(new Coordenadas(0,0), new Coordenadas(20,20), "kappaLine");
  Reta* r2 = new Reta(new Coordenadas(200,100), new Coordenadas(60,75), "kappaLine2");
  vector<Coordenadas*> pontosW1;
  pontosW1.push_back(new Coordenadas(50,400));
  pontosW1.push_back(new Coordenadas(50,300));
  pontosW1.push_back(new Coordenadas(300,300));
  pontosW1.push_back(new Coordenadas(300,400));
  Wireframe* w = new Wireframe( pontosW1, "wireframe1");
  Ponto* p = new Ponto(new Coordenadas(400,400),"p1");

  return 0;
}
