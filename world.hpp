#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>
#include <iostream>
#include "object.hpp"
#include "window.hpp"
#include "coordinates.hpp"
#include "math.h"
#include "operations.cpp"
#include "matrix4x4.hpp"

class World {
public:
    World(Window *window);

    ~World();

    void add_object(Object *obj);

    void remove_object(std::string name);

    Object *get_object(std::string name);

    std::vector<Object *> objects();

    Window *window();

    void project(bool perspective);

private:
    Window *_window;
    std::vector<Object *> _objects;
};

#endif // WORLD_HPP