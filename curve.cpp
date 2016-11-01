#include "curve.hpp"

using namespace std;

Curve::Curve(std::vector<Coordinates *> points, std::string name, Color *color) {
    _points = points;
    _name = name;
    _color = color;
    _background_color = new Color(1, 1, 1, 1);
    _filled = false;
}

void Curve::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max,
                          bool clip_flag) {
    /* Finding the curve points using Blending Functions */
    double step = 0.01;
    /* Creating the Bezier matrix */
    Matriz4x4 MB = Matrices::bezier();
    vector<Coordinates *>::iterator it = _points.begin();
    // If the bezier curve has the correct number of points
    if (((_points.size() - 1) % 3) == 0) {
        for (int i = 0; i < _points.size() - 1; i = i + 3, it = it + 3) {
            Matriz4x1 Gx = Matriz4x1((*it)->x_scn(), (*(it + 1))->x_scn(), (*(it + 2))->x_scn(), (*(it + 3))->x_scn());
            Matriz4x1 Gy = Matriz4x1((*it)->y_scn(), (*(it + 1))->y_scn(), (*(it + 2))->y_scn(), (*(it + 3))->y_scn());
            Coordinates last_point = Coordinates(0, 0, 0);
            // Finding the wireframes that define the curve
            for (double t = 0; t <= 1; t = t + step) {
                double l1T[] = {(t * t * t), (t * t), t, 1};
                Matriz1x4 T = Matriz1x4(l1T);
                Matriz1x4 TMB = T.multiplicarPor4x4(MB);
                double x = TMB.multiplicarPor4x1(Gx);
                double y = TMB.multiplicarPor4x1(Gy);
                if (t == 0) {
                    last_point = Coordinates(x, y, 0);
                } else {
                    // Clipping and Drawing
                    Coordinates current_point = Coordinates(x, y, 0);
                    draw_edge(current_point, last_point, cr, win_min, win_max, vp_min, vp_max);
                    last_point = current_point;
                }
            }
        }
    }
}
