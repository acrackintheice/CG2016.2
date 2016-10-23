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
void Object::transform(Matriz4x4 transformation, bool use_scn, bool change_scn) {
    for (vector<Coordinates *>::iterator it = _points.begin(); it != _points.end(); it++) {
        Coordinates *point = (*it);
        Matriz4x1 transformed_point =
                (use_scn) ? transformation.multiplicar4x1(Matriz4x1(point->x_scn(), point->y_scn(), point->z_scn(), 1))
                          : transformation.multiplicar4x1(Matriz4x1(point->x(), point->y(), point->z(), 1));
        if (change_scn) {
            point->set_xyz_scn(transformed_point.get(0), transformed_point.get(1), transformed_point.get(2));
        } else {
            point->set_xyz(transformed_point.get(0), transformed_point.get(1), transformed_point.get(2));
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
    Matriz4x4 rotation = Matrices::arbitrary_rotation(u, v, w, a, b, c, j, k, l);
    transform(rotation);
}

/* Generic method for objects that only have one clipping option */
vector<Edge> Object::clip2() {
    return clip();
}