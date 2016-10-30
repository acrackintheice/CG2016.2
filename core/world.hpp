#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>
#include <iostream>
#include "../objects/object.hpp"
#include "../objects/window.hpp"
#include "../utils/coordinates.hpp"
#include "math.h"
#include "../utils/operations.cpp"
#include "../utils/matriz4x4.hpp"

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