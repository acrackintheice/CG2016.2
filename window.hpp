#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "objeto.hpp"

class Window : public Objeto
{
public:
    Window(Coordenadas* p1, Coordenadas* p2);
    ~Window();
    void move(double x1_offset, double y1_offset, double x2_offset, double y2_offset);
    void zoom_in(double value);
    void zoom_out(double value);
    void resetar();
    Coordenadas* get_min();
    Coordenadas* get_max();
};

#endif // WINDOW_HPP