#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>
#include "object.hpp"
#include "window.hpp"
#include "coordinates.hpp"
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
    double angle_between_vectors(Coordinates vector_1,Coordinates vector_2);
    void scn_upate();
    void clip();
private:

	Window* _window;
    std::vector<Object*> _objects;
};

#endif // WORLD_HPP