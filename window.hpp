#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "object.hpp"

class Window : public Object
{
public:
    Window(Coordinates p1, Coordinates p2);
    ~Window();
    void move(double x1_offset, double y1_offset, double x2_offset, double y2_offset);
    void zoom_in(double value);
    void zoom_out(double value);
    void reset();
    Coordinates get_min();
    Coordinates get_max();
};

#endif // WINDOW_HPP