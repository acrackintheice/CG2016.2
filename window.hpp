#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <iostream>
#include "object.hpp"
#include "operations.cpp"

class Window : public Object {
public:
    Window(Coordinates *p1, Coordinates *p2, Coordinates *p3, Coordinates *p4, Coordinates *vup, Coordinates *vpn,
           Coordinates *cop);

    ~Window();

    void move(double dx, double dy, double dz);

    Coordinates min();

    Coordinates max();

    Coordinates vup();

    Coordinates vpn();

    Coordinates vrp();

    virtual void
    clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max,
                  bool clip_flag) override;

    Coordinates cop();

    void transform(Matrix4x4 transformation, bool use_scn = false, bool change_scn = false);

private:
    Coordinates *_vup;
    Coordinates *_vpn;
    Coordinates *_vrp;
    Coordinates *_cop;

    std::vector<Coordinates *> configuration_points;
};

#endif // WINDOW_HPP
