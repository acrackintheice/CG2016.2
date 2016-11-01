#include "bspline.hpp"

using namespace std;

BSpline::BSpline(std::vector<Coordinates *> points, std::string name, Color *color) {
    _points = points;
    _name = name;
    _color = color;
    _filled = false;
    _background_color = new Color(1, 1, 1, 1);
}

void BSpline::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                            Coordinates vp_min, Coordinates vp_max, bool clip_flag) {
    vector<Coordinates> drawing_points;
    vector<Drawing_Edge> edges;
    // 0 - Calculating the deltas.
    double delta = 0.01;
    Matriz4x4 e = Matrices::deltas(delta);
    /* 1 - Calculating C =  mbs * Gbs */
    /* Creating the B-Spline matrix in order to calculate the Cs */
    Matriz4x4 mbs = Matrices::bspline();
    /* Now for each curve */
    vector<Coordinates *>::iterator it = _points.begin();
    for (int i = 3; i < _points.size(); i++, it++) {
        /* Creating the objects matrixes in order to calculate the Cs */
        Matriz4x1 gx = Matriz4x1((*it)->x_scn(), (*(it + 1))->x_scn(), (*(it + 2))->x_scn(), (*(it + 3))->x_scn());
        Matriz4x1 gy = Matriz4x1((*it)->y_scn(), (*(it + 1))->y_scn(), (*(it + 2))->y_scn(), (*(it + 3))->y_scn());
        /* Calculating the Cs */
        Matriz4x1 Cx = mbs.multiplicar4x1(gx);
        Matriz4x1 Cy = mbs.multiplicar4x1(gy);
        /* 2 - Calculating f0, delta(f0), delta²(f0) e delta³(f0) based on the first point of the bspline */
        Matriz4x1 dx = e.multiplicar4x1(Cx);
        Matriz4x1 dy = e.multiplicar4x1(Cy);
        /* 3 - Drawing the points with desenharCurvaFwdDiff(...) from the slides */
        drawFwdDiffPoints(1 / delta, dx, dy, cr, win_min, win_max, vp_min, vp_max);
    }
}

void BSpline::drawFwdDiffPoints(double n, Matriz4x1 dx, Matriz4x1 dy, cairo_t *cr, Coordinates win_min,
                                Coordinates win_max, Coordinates vp_min, Coordinates vp_max) {
    double x = dx.get(0);
    double deltaX = dx.get(1);
    double delta2X = dx.get(2);
    double delta3X = dx.get(3);

    double y = dy.get(0);
    double deltaY = dy.get(1);
    double delta2Y = dy.get(2);
    double delta3Y = dy.get(3);

    Coordinates last_point = Coordinates(x, y, 0);
    for (int i = 0; i < n; ++i) {
        x = x + deltaX;
        deltaX = deltaX + delta2X;
        delta2X = delta2X + delta3X;
        y = y + deltaY;
        deltaY = deltaY + delta2Y;
        delta2Y = delta2Y + delta3Y;
        // Clipping and Drawing
        Coordinates current_point = Coordinates(x, y, 0);
        draw_edge(current_point, last_point, cr, win_min, win_max, vp_min, vp_max);
        last_point = current_point;
    }
}
