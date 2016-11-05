#include "bezier_curve.hpp"

Bezier_Curve::Bezier_Curve(std::vector<Coordinates *> points, std::string name, Color *color) : Curve(points, name, color){}

void Bezier_Curve::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max,
                          bool clip_flag) {
    /* Finding the curve points using Blending Functions */
    double step = 0.01;
    /* Creating the Bezier matrix */
    Matrix4x4 MB = Matrices::bezier();
    vector<Coordinates *>::iterator it = _points.begin();
    // If the bezier curve has the correct number of points
    if (((_points.size() - 1) % 3) == 0) {
        for (int i = 0; i < _points.size() - 1; i = i + 3, it = it + 3) {
            Matrix4x1 Gx = Matrix4x1((*it)->x_scn(), (*(it + 1))->x_scn(), (*(it + 2))->x_scn(), (*(it + 3))->x_scn());
            Matrix4x1 Gy = Matrix4x1((*it)->y_scn(), (*(it + 1))->y_scn(), (*(it + 2))->y_scn(), (*(it + 3))->y_scn());
            Coordinates last_point = Coordinates(0, 0, 0);
            // Finding the wireframes that define the curve
            for (double t = 0; t <= 1; t = t + step) {
                double l1T[] = {(t * t * t), (t * t), t, 1};
                Matrix1x4 T = Matrix1x4(l1T);
                Matrix1x4 TMB = T.multiply4x4(MB);
                double x = TMB.multiplyPor4x1(Gx);
                double y = TMB.multiplyPor4x1(Gy);
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