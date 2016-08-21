#include "point.hpp"

using namespace std;

Point::Point(Coordinates xy, string name){
  _points.push_back(xy);
  _name = name;
}
Point::~Point(){
}