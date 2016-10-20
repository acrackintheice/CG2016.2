#ifndef EDGE_HPP
#define EDGE_HPP

#include "coordinates_3d.hpp"
#include <string>

class Edge 
{
public:
    Edge(Coordinates_3d* p1, Coordinates_3d* p2);
    ~Edge();
    Coordinates_3d* get_p1();
    Coordinates_3d* get_p2();
    std::string to_string();
private:
	Coordinates_3d* _p1;
	Coordinates_3d* _p2;
};

#endif 