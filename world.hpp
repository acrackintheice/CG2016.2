#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>
#include "object.hpp"
#include "window.hpp"
#include "coordinates.hpp"
#include "matriz3x3.hpp"
#include "object_3d.hpp"

class World
{
public:
    World(Window* window);
    ~World();
    void add_object(Object* obj);
    void add_object_3d(Object_3d*);
    void remove_object(std::string name);
    Object* get_object(std::string name);
    std::vector<Object*> get_objects();
    Window* get_window();
    double angle_between_vectors(Coordinates vector_1,Coordinates vector_2);
    void scn_upate();
    void clip();
    void set_clip_flag(bool clip_flag);
private:

	Window* _window;
    std::vector<Object*> _objects;
    std::vector<Object_3d*> _3d_objects;
    bool _clip_flag;
};

#endif // WORLD_HPP



/*
    What need to be done:
        Transform 3D to 2D objects.
        Transformations in 3D. (Dont need to do it today)
*/