#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>
#include "coordinates_3d.hpp"
#include "object_3d.hpp"

class Edge : public  Object_3d
{
public:
    Edge(Coordinates_3d* p1, Coordinates_3d* p2);
    ~Edge();
    Coordinates_3d* get_p1();
    Coordinates_3d* get_p2();
    std::string to_string();
private:
};

#endif 