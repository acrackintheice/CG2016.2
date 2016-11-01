#include "curve.hpp"

using namespace std;

Curve::Curve(std::vector<Coordinates *> points, std::string name, Color *color) {
    _points = points;
    _name = name;
    _color = color;
    _background_color = new Color(1, 1, 1, 1);
    _filled = false;
}

vector<Drawing_Edge> Curve::clip(bool clip_flag) {
    vector<Coordinates> drawing_points;
    vector<Drawing_Edge> edges;
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
            for (double t = 0; t <= 1; t = t + step) {
                double l1T[] = {(t * t * t), (t * t), t, 1};
                Matriz1x4 T = Matriz1x4(l1T);
                Matriz1x4 TMB = T.multiplicarPor4x4(MB);
                double x = TMB.multiplicarPor4x1(Gx);
                double y = TMB.multiplicarPor4x1(Gy);
                drawing_points.push_back(Coordinates(x, y, 0));
            }
        }
        /*  Clipping  */
        // If the first point of the curve is too far away, we dont draw anything
        if (too_far_away(drawing_points[0])) {
            return edges;
        }
            // Else, we clip every line
        else {
            vector<Coordinates>::iterator it2 = drawing_points.begin();
            for (int i = 0; i < drawing_points.size() - 1; ++i, it2++) {
                Coordinates p1 = *(it2);
                Coordinates p2 = *(it2 + 1);
                Line l = Line(new Coordinates(p1.x(), p1.y(), 0), new Coordinates(p2.x(), p2.y(), 0), "",
                              new Color(1, 1, 1, 1));;
                vector<Drawing_Edge> clipped = l.clip();
                if (clipped.size() > 0) {
                    Coordinates p = clipped[0].p1();
                    Coordinates u = clipped[0].p2();
                    edges.push_back(Drawing_Edge(p, u));
                }
            }
        }
    }
    return edges;
}

bool Curve::too_far_away(Coordinates c) {
    return c.x() || c.y() < -10 && c.x() || c.y() > 10;
}