/*#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>
#include "object_3d.hpp"
#include "window.hpp"
#include "coordinates.hpp"
#include "matriz3x3.hpp"

class World
{
public:
    World(Window* window);
    ~World();
    void add_object(Object_3d* obj);
    void remove_object(std::string name);
    Object* get_object(std::string name);
    std::vector<Object_3d*> get_objects();
    Window* get_window();
    //double angle_between_vectors(Coordinates vector_1,Coordinates vector_2);
    //void scn_upate();
    //void clip();
    //void set_clip_flag(bool clip_flag);
private:

	Window* _window;
    std::vector<Object_3d*> _objects;
    //bool _clip_flag;
};

#endif // WORLD_HPP