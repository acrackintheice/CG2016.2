#include "window.hpp"

using namespace std;

Window::Window(Coordinates *p1, Coordinates *p2, Coordinates *p3, Coordinates *p4, Coordinates *vup,
               Coordinates *vpn, Coordinates *cop) {
    _vup = vup;
    _vpn = vpn;
    _vrp = new Coordinates(0,0,0);
    _cop = cop;
    _name = "Window";
    _points.push_back(p1);
    _points.push_back(p2);
    _points.push_back(p3);
    _points.push_back(p4);
    _edges.push_back(Edge(p1, p2));
    _edges.push_back(Edge(p2, p3));
    _edges.push_back(Edge(p3, p4));
    _edges.push_back(Edge(p4, p1));
    configuration_points.push_back(_vup);
    configuration_points.push_back(_vpn);
    configuration_points.push_back(_vrp);
    configuration_points.push_back(_cop);
    _color = new Color(255, 0, 0, 1);
    _background_color = new Color(1, 1, 1, 1);
    _filled = false;
}

Window::~Window() {
    for (vector<Coordinates *>::iterator it = _points.begin(); it != _points.end(); it++) {
        Coordinates *point = (*it);
        delete point;
    }
    delete _vup;
    delete _vpn;
}

/*
The window's transform function is different from the Object's one because
it also needs to transform the configuration points that don't define the window's geometry
*/
void Window::transform(Matriz4x4 transformation, bool use_scn, bool change_scn) {
    vector<Coordinates *> all_points = _points;
    all_points.insert(all_points.end(), configuration_points.begin(), configuration_points.end());
    /* Transforming the points */
    for (vector<Coordinates *>::iterator it = all_points.begin(); it != all_points.end(); it++) {
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

void Window::move(double dx, double dy, double dz) {
    translate(dx, dy, dz);
}

Coordinates Window::min() {
    Coordinates min = Coordinates(_points[0]->x(), _points[0]->y(), _points[0]->z());
    min.set_xyz_scn(_points[0]->x_scn(), _points[0]->y_scn(), _points[0]->z_scn());
    return min;
}

Coordinates Window::max() {
    Coordinates max = Coordinates(_points[2]->x(), _points[2]->y(), _points[2]->z());
    max.set_xyz_scn(_points[2]->x_scn(), _points[2]->y_scn(), _points[2]->z_scn());
    return max;
}

Coordinates Window::vup() {
    Coordinates vup = Coordinates(_vup->x(), _vup->y(), _vup->z());
    vup.set_xyz_scn(_vup->x_scn(), _vup->y_scn(), _vup->z_scn());
    return vup;
}

Coordinates Window::vpn() {
    Coordinates vpn = Coordinates(_vpn->x(), _vpn->y(), _vpn->z());
    vpn.set_xyz_scn(_vpn->x_scn(), _vpn->y_scn(), _vpn->z_scn());
    return vpn;
}

Coordinates Window::vrp() {
    Coordinates vrp = Coordinates(_vrp->x(), _vrp->y(), _vrp->z());
    vrp.set_xyz_scn(_vrp->x_scn(), _vrp->y_scn(), _vrp->z_scn());
    return vrp;
}

Coordinates Window::cop() {
    Coordinates cop = Coordinates(_cop->x(), _cop->y(), _cop->z());
    cop.set_xyz_scn(_cop->x_scn(), _cop->y_scn(), _cop->z_scn());
    return cop;
}

void Window::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min, Coordinates vp_max, bool clip_flag) {

}

