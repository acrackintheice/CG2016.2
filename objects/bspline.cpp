#include "bspline.hpp"

using namespace std;

BSpline::BSpline(std::vector<Coordinates *> points, std::string name, Color *color) {
    _points = points;
    _name = name;
    _color = color;
    _filled = false;
    _background_color = new Color(1, 1, 1, 1);
}

vector<Drawing_Edge> BSpline::clip(bool clip_flag) {
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
        /* 3 - Calculating the points with desenharCurvaFwdDiff(...) from the slides */
        std::vector<Coordinates> some_points = getFwdDiffPoints(1 / delta, dx, dy);
        /* 4 - Inserting the new points into the points list */
        drawing_points.insert(drawing_points.end(), some_points.begin(), some_points.end());
    }
    /*  Clipping  */
    // If the first point of the curve is too far away, we dont draw anything
    if (too_far_away(drawing_points[0]))
        return edges;
        // Else, we clip every line
    else {
        vector<Coordinates>::iterator it2 = drawing_points.begin();
        for (int i = 0; i < drawing_points.size() - 1; ++i, it2++) {
            Coordinates p1 = *(it2);
            Coordinates p2 = *(it2 + 1);
            Line l = Line(new Coordinates(p1.x(), p1.y(), 0), new Coordinates(p2.x(), p2.y(), 0), "",
                          new Color(1, 1, 1, 1));
            vector<Drawing_Edge> clipped = l.clip();
            if (clipped.size() > 0) {
                Coordinates p = clipped[0].p1();
                Coordinates u = clipped[0].p2();
                edges.push_back(Drawing_Edge(p, u));
            }
        }
    }
    return edges;
}

std::vector<Coordinates> BSpline::getFwdDiffPoints(double n, Matriz4x1 dx, Matriz4x1 dy) {
    double x = dx.get(0);
    double deltaX = dx.get(1);
    double delta2X = dx.get(2);
    double delta3X = dx.get(3);

    double y = dy.get(0);
    double deltaY = dy.get(1);
    double delta2Y = dy.get(2);
    double delta3Y = dy.get(3);

    std::vector<Coordinates> some_points;
    for (int i = 0; i < n; ++i) {
        x = x + deltaX;
        deltaX = deltaX + delta2X;
        delta2X = delta2X + delta3X;
        y = y + deltaY;
        deltaY = deltaY + delta2Y;
        delta2Y = delta2Y + delta3Y;
        some_points.push_back(Coordinates(x, y, 0));
    }
    return some_points;
}

bool BSpline::too_far_away(Coordinates c) {
    return c.x() && c.y() < -10 && c.x() && c.y() > 10;
}