#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>
#include <iostream>
#include "object.hpp"
#include "window.hpp"
#include "coordinates_3d.hpp"
#include "math.h"
#include "operations.cpp"
#include "matriz4x4.hpp"
#include "matriz3x3.hpp"

class World
{
public:
    World(Window* window);
    ~World();
    void add_object(Object* obj);
    void remove_object(std::string name);
    Object* get_object(std::string name);
    std::vector<Object*> get_objects();
    Window* get_window();
    double angle_between_vectors(Coordinates_3d vector_1,Coordinates_3d vector_2);
    void scn_upate();
    void project_3d_objects(bool perspective);
private:

	Window* _window;
    std::vector<Object*> _objects;
};

#endif // WORLD_HPP