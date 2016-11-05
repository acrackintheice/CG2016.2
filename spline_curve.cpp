#include "spline_curve.hpp"

using namespace std;

Spline_Curve::Spline_Curve(std::vector<Coordinates *> points, std::string name, Color *color) : Curve(points, name, color) {}

void Spline_Curve::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                            Coordinates vp_min, Coordinates vp_max, bool clip_flag) {
    vector<Coordinates> drawing_points;
    vector<Drawing_Edge> edges;
    // 0 - Calculating the deltas.
    double delta = 0.01;
    Matrix4x4 e = Matrices::deltas(delta);
    /* 1 - Calculating C =  mbs * Gbs */
    /* Creating the B-Spline matrix in order to calculate the Cs */
    Matrix4x4 mbs = Matrices::bspline();
    /* Now for each curve */
    vector<Coordinates *>::iterator it = _points.begin();
    for (int i = 3; i < _points.size(); i++, it++) {
        /* Creating the objects matrixes in order to calculate the Cs */
        Matrix4x1 gx = Matrix4x1((*it)->x_scn(), (*(it + 1))->x_scn(), (*(it + 2))->x_scn(), (*(it + 3))->x_scn());
        Matrix4x1 gy = Matrix4x1((*it)->y_scn(), (*(it + 1))->y_scn(), (*(it + 2))->y_scn(), (*(it + 3))->y_scn());
        /* Calculating the Cs */
        Matrix4x1 Cx = mbs.multiply4x1(gx);
        Matrix4x1 Cy = mbs.multiply4x1(gy);
        /* 2 - Calculating f0, delta(f0), delta²(f0) e delta³(f0) based on the first point of the bspline */
        Matrix4x1 dx = e.multiply4x1(Cx);
        Matrix4x1 dy = e.multiply4x1(Cy);
        /* 3 - Drawing the points with desenharCurvaFwdDiff(...) from the slides */
        draw_fwd_diff(1 / delta, dx, dy, cr, win_min, win_max, vp_min, vp_max);
    }
}

void Spline_Curve::draw_fwd_diff(double n, Matrix4x1 dx, Matrix4x1 dy, cairo_t *cr, Coordinates win_min,
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
