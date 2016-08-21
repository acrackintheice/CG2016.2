#include "line.hpp"
#include <iostream>

using namespace std;

Line::Line(Coordinates p1,Coordinates p2, string name)
{
    _points.push_back(p1);
    _points.push_back(p2);
    _name = name;
}
Line::~Line(){
}