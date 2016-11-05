#include "object.hpp"

using namespace std;


Object::~Object() {
    delete _color;
    delete _background_color;
    for (vector<Coordinates *>::iterator it = _points.begin(); it != _points.end(); it++) {
        Coordinates *point = (*it);
        delete point;
    }
}

string Object::name() {
    return _name;
}

vector<Coordinates *> Object::points() {
    return _points;
}

Color *Object::color() {
    return _color;
}

Color *Object::background_color() {
    return _color;
}

bool Object::filled() {
    return _filled;
}

/* Returns the object's geometric center */
Coordinates Object::geometric_center(bool use_z, bool use_scn) {
    double sum_x = 0;
    double sum_y = 0;
    double sum_z = 0;
    double size = _points.size();
    for (vector<Coordinates *>::iterator it = _points.begin(); it != _points.end(); it++) {
        Coordinates *point = (*it);
        if (use_scn) {
            sum_x = sum_x + point->x_scn();
            sum_y = sum_y + point->y_scn();
            sum_z = sum_z + point->z_scn();
        } else {
            sum_x = sum_x + point->x();
            sum_y = sum_y + point->y();
            sum_z = sum_z + point->z();
        }
    }
    if (use_z) {
        return Coordinates(sum_x / size, sum_y / size, sum_z / size);
    } else {
        return Coordinates(sum_x / size, sum_y / size, 0);
    }
}

/* Transform every point of the object using a transformation matrix*/
void Object::transform(Matrix4x4 transformation, bool use_scn, bool change_scn) {
    for (vector<Coordinates *>::iterator it = _points.begin(); it != _points.end(); it++) {
        Coordinates *point = (*it);
        Matrix4x1 transformed_point =
                (use_scn) ? transformation.multiply4x1(Matrix4x1(point->x_scn(), point->y_scn(), point->z_scn(), 1))
                          : transformation.multiply4x1(Matrix4x1(point->x(), point->y(), point->z(), 1));
        double div = transformed_point.get(3);
        if (change_scn) {
            double div = transformed_point.get(3);
            point->set_xyz_scn(transformed_point.get(0) / div, transformed_point.get(1) / div,
                               transformed_point.get(2) / div);
        } else {
            point->set_xyz(transformed_point.get(0) / div, transformed_point.get(1) / div,
                           transformed_point.get(2) / div);
        }
    }
}

void Object::translate(double dx, double dy, double dz) {
    transform(Matrices::translation(dx, dy, dz));
}

void Object::scale(double sx, double sy, double sz) {
    Coordinates center = geometric_center();
    double cx = center.x();
    double cy = center.y();
    double cz = center.z();
    transform(Matrices::scaling(sx, sy, sz, cx, cy, cz));
}

void Object::rotate_x(double angle) {
    angle = (M_PI / 180.0) * angle;
    transform(Matrices::rotate_x(angle));
}

void Object::rotate_y(double angle) {
    angle = (M_PI / 180.0) * angle;
    transform(Matrices::rotate_y(angle));
}

void Object::rotate_z(double angle) {
    angle = (M_PI / 180.0) * angle;
    transform(Matrices::rotate_z(angle));
}

/* Rotate by angle(in Degrees) around an axis defined by P1 -> P2 */
void Object::rotate(double angle, Coordinates p1, Coordinates p2) {
    /* Transforming the angle to radians*/
    angle = (M_PI / 180.0) * angle;
    double a = p1.x();
    double b = p1.y();
    double c = p1.z();
    double d = p2.x();
    double e = p2.y();
    double f = p2.z();
    double u = d - a;
    double v = e - b;
    double w = f - c;
    double l = pow(u, 2) + pow(v, 2) + pow(w, 2);
    double j = cos(angle);
    double k = sin(angle);
    Matrix4x4 rotation = Matrices::arbitrary_rotation(u, v, w, a, b, c, j, k, l);
    transform(rotation);
}

void Object::draw_edge(Coordinates p1, Coordinates p2, cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max) {
    vector<Drawing_Edge> edges;
    edges = Operations::liang_barsky(p1.x(), p1.y(), p2.x(), p2.y());
    if (edges.size() > 0) {
        Drawing_Edge e = edges[0];
        Coordinates vp_p1 = Transformations::viewport(e.p1(), win_min, win_max, vp_min, vp_max);
        Coordinates vp_p2 = Transformations::viewport(e.p2(), win_min, win_max, vp_min, vp_max);
        cairo_move_to(cr, vp_p1.x(), vp_p1.y());
        cairo_line_to(cr, vp_p2.x(), vp_p2.y());
        cairo_stroke(cr);
    }
}