#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>
#include "object.hpp"
#include "window.hpp"
#include "coordinates.hpp"

class World
{
public:
    World(Window* window);
    ~World();
    void add_object(Object* obj);
    void remove_object(std::string name);
    Object* get_object(std::string name);
    void move_window(double x1_offset, double y1_offset, double x2_offset, double y2_offset);
    std::vector<Object*> get_objects();
    Window* get_window();
private:
	Window* _window;
    std::vector<Object*> _objects;
};

#endif // WORLD_HPP