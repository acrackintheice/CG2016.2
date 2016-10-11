#ifndef OBJECT_3D_HPP
#define OBJECT_3D_HPP

#include "coordinates_3d.hpp"
#include "matriz1x4.hpp"
#include "matriz4x4.hpp"
#include "color.hpp"
#include <vector>
#include <string>

class Object_3d
{
public:
    std::string get_name();
    std::vector<Coordinates_3d*> get_points();
    Coordinates_3d get_geometric_center();
    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, Coordinates_3d p1, Coordinates_3d p2);
    virtual ~Object_3d();
protected:
	void virtual transform(Matriz4x4 transformation); 
    std::string _name;
    std::vector<Coordinates_3d*> _points;
};

#endif // OBJECT_HPP