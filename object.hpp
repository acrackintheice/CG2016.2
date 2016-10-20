#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <string>
#include <iostream>
#include "coordinates_3d.hpp"
#include "matriz1x3.hpp"
#include "matriz3x3.hpp"
#include "matriz1x4.hpp"
#include "matriz4x4.hpp"
#include "matriz4x1.hpp"
#include "color.hpp"
#include "edge.hpp"
#include "math.h"
#include "operations.cpp"
#include "matrices.cpp"

class Object
{
public:
    std::string get_name();
    std::vector<Coordinates_3d*> get_points();
    std::vector<Edge> get_edges();
    Color* get_color();
    Color* get_background_color();
    bool is_filled();
    Coordinates_3d get_geometric_center();
    void translate(double dx, double dy, double dz);
    void scale(double sx, double sy, double sz);
    void rotate(double angle, Coordinates_3d p1, Coordinates_3d p2);
    void rotate_x(double angle);
    void rotate_y(double angle);
    void rotate_z(double angle);
    void virtual update_scn_points(Matriz3x3 scn_matrix);
    std::vector<Edge> virtual clip();
    std::vector<Edge> virtual clip2();
    void virtual transform(Matriz4x4 transformation); 
    void virtual transform2(Matriz4x4 transformation);
    void project(Matriz4x4 rotation_matrix);
    std::string to_string();
    virtual ~Object();
protected:
    std::string _name;
    std::vector<Coordinates_3d*> _points;

    std::vector<Edge> _edges;

    bool _filled;
    Color* _color;
    Color* _background_color;
};

#endif // OBJECT_HPP