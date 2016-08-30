#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "coordinates.hpp"
#include "matriz1x3.hpp"
#include "matriz3x3.hpp"
#include <vector>
#include <string>

class Object
{
public:
    std::string get_name();
    std::vector<Coordinates> get_points();
    std::vector<Coordinates> virtual get_drawing_points();
    Coordinates get_geometric_center();
    void translate(double sx, double sy);
	void scale(double sx, double sy);
	void rotate(double angle, Coordinates point);
    void update_scn_points(Matriz3x3 scn_matrix);
	void print();
    virtual ~Object();
protected:
	void virtual transform(Matriz3x3 transformation);
	
    std::string _name;
    std::vector<Coordinates> _points;
    std::vector<Coordinates> _scn_points;
};

#endif // OBJECT_HPP