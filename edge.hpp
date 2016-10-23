#ifndef EDGE_HPP
#define EDGE_HPP

#include "coordinates.hpp"
#include <string>

class Edge 
{
public:
    Edge(Coordinates* p1, Coordinates* p2);
    ~Edge();
    Coordinates* p1();
    Coordinates* p2();
    std::string to_string();
private:
	Coordinates* _p1;
	Coordinates* _p2;
};

#endif 