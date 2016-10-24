#include "window.hpp"

using namespace std;

Window::Window(Coordinates *p1, Coordinates *p2, Coordinates *p3, Coordinates *p4, Coordinates *vup,
               Coordinates *vpn) {
    vector<Coordinates*> vup_points;
    Coordinates* vup1 = new Coordinates(0,0,0);
    vup_points.push_back(vup1);
    vup_points.push_back(vup);
    vector<Edge> vup_edges;
    vup_edges.push_back(Edge(vup1, vup));

    vector<Coordinates*> vpn_points;
    Coordinates* vpn1 = new Coordinates(0,0,0);
    vpn_points.push_back(vpn1);
    vpn_points.push_back(vpn);
    vector<Edge> vpn_edges;
    vpn_edges.push_back(Edge(vpn1, vpn));

    vector<Coordinates*> vrp_points;
    Coordinates* vrp1 = new Coordinates(0,0,0);
    vrp_points.push_back(vrp1);
    vector<Edge> vrp_edges;
    vrp_edges.push_back(Edge(vrp1, vrp1));

    _vup = new Wireframe(vup_points, vup_edges,"VUP", new Color(1,1,1,1), new Color(1,1,1,1), false);
    _vpn = new Wireframe(vpn_points, vpn_edges,"VPN", new Color(1,1,1,1), new Color(1,1,1,1), false);
    _vrp = new Wireframe(vrp_points, vrp_edges,"VRP", new Color(1,1,1,1), new Color(1,1,1,1), false);
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
    delete _vrp;
}

/*
The window's transform function is different from the Object's one because
it also needs to transform the configuration points that don't define the window's geometry
*/
void Window::transform(Matriz4x4 transformation, bool use_scn, bool change_scn) {
    /* Transforming the points */
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
    for(vector<Wireframe *>::iterator it = configuration_points.begin(); it != configuration_points.end(); it++){
        Wireframe *wireframe = (*it);
        wireframe->transform(transformation, use_scn, change_scn);
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
    Coordinates* vup = _vup->points()[1];
    Coordinates c = Coordinates(vup->x(), vup->y(), vup->z());
    c.set_xyz_scn(vup->x_scn(), vup->y_scn(), vup->z_scn());
    return c;
}

Coordinates Window::vpn() {
    Coordinates* vpn = _vpn->points()[1];
    Coordinates c = Coordinates(vpn->x(), vpn->y(), vpn->z());
    c.set_xyz_scn(vpn->x_scn(), vpn->y_scn(), vpn->z_scn());
    return c;
}
Coordinates Window::vrp() {
    Coordinates* vrp = _vrp->points()[0];
    Coordinates c = Coordinates(vrp->x(), vrp->y(), vrp->z());
    c.set_xyz_scn(vrp->x_scn(), vrp->y_scn(), vrp->z_scn());
    return c;
}

vector<Edge> Window::clip() {
    return _edges;
}

