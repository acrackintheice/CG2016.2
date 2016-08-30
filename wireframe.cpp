#include "wireframe.hpp"

using namespace std;

Wireframe::Wireframe(vector<Coordinates> points, string name){
   _points = points;
   _scn_points = points;
   _name = name;
}
Wireframe::~Wireframe(){
}