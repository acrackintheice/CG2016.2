#include "surface.hpp"
#include "wireframe.hpp"

Surface::Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool blending) {
    _points = points;
    _name = name;
    _color = color;
    _filled = false;
    _background_color = new Color(1, 1, 1, 1);
    _blending = blending;
}

void Surface::draw_fwd_diff(double n, double x, double Dx, double D2x, double D3x,
                            double y, double Dy, double D2y, double D3y,
                            cairo_t *cr, Coordinates win_min, Coordinates win_max,
                            Coordinates vp_min, Coordinates vp_max) {
    Coordinates last_point = Coordinates(x, y, 0);
    for (int i = 0; i < n; ++i) {
        x = x + Dx;
        Dx = Dx + D2x;
        D2x = D2x + D3x;
        y = y + Dy;
        Dy = Dy + D2y;
        D2y = D2y + D3y;
        // Clipping and Drawing
        Coordinates current_point = Coordinates(x, y, 0);
        draw_edge(current_point, last_point, cr, win_min, win_max, vp_min, vp_max);
        last_point = current_point;
    }
}

Matrix4x4 Surface::update(Matrix4x4 D) {
    double l0[] = {D.get(0, 0) + D.get(1, 0), D.get(0, 1) + D.get(1, 1),
                   D.get(0, 2) + D.get(1, 2), D.get(0, 3) + D.get(1, 3)};

    double l1[] = {D.get(1, 0) + D.get(2, 0), D.get(1, 1) + D.get(2, 1),
                   D.get(1, 2) + D.get(2, 2), D.get(1, 3) + D.get(2, 3)};

    double l2[] = {D.get(2, 0) + D.get(3, 0), D.get(2, 1) + D.get(3, 1),
                   D.get(2, 2) + D.get(3, 2), D.get(2, 3) + D.get(3, 3)};

    double l3[] = {D.get(3, 0), D.get(3, 1), D.get(3, 2), D.get(3, 3)};
    return Matrix4x4(l0, l1, l2, l3);
}

