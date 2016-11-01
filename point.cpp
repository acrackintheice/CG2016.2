#include "point.hpp"

using namespace std;

Point::Point(Coordinates *xy, string name, Color *color) {
    _points.push_back(xy);
    _edges.push_back(Edge(xy, xy));
    _name = name;
    _color = color;
    _filled = false;
    _background_color = new Color(1, 1, 1, 1);
}

void Point::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max,
                          bool clip_flag) {
    Coordinates *p = _points[0];
    double x = p->x_scn();
    double y = p->y_scn();

    if (!(x < -1 || x > 1 || y < -1 || y > 1)) {
        Coordinates vp_p1 = Transformations::viewport(*(p), win_min, win_max, vp_min, vp_max);
        cairo_move_to(cr, vp_p1.x(), vp_p1.y());
        cairo_line_to(cr, vp_p1.x(), vp_p1.y());
        cairo_stroke(cr);
    }
}