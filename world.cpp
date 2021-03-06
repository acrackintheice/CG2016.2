#include "world.hpp"

using namespace std;

World::World(Window *window) {
    _window = window;
    add_object(window);
}

World::~World() {
    for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
        Object *obj = (*it);
        delete obj;
    }
}

void World::add_object(Object *obj) {
    _objects.push_back(obj);
}

Object *World::get_object(string name) {
    Object *chosen = 0;
    for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
        Object *obj = (*it);
        if (obj->name() == name) {
            chosen = obj;
            break;
        }
    }
    return chosen;
}

vector<Object *> World::objects() {
    return _objects;
}

void World::remove_object(string name) {
    if (name != "Window") {
        for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object *obj = (*it);
            if (obj->name() == name) {
                _objects.erase(it);
                delete obj;
                break;
            }
        }
    }
}

Window *World::window() {
    return _window;
}


void World::project(bool perspective) {
    // Calculating the translation parameters
    double cx = (perspective) ? _window->cop().x() : _window->vrp().x();
    double cy = (perspective) ? _window->cop().y() : _window->vrp().y();
    double cz = (perspective) ? _window->cop().z() : _window->vrp().z();
    // Translating the Window to the center of the world in order to calculate the rotation parameters
    _window->transform(Matrices::translation(-_window->vrp().x(),
                                             -_window->vrp().y(),
                                             -_window->vrp().z()), false, true);
    // Calculating the rotation parameters, a bunch of vectors
    Coordinates vpn = _window->vpn();
    double n_vpn = Operations::norma(vpn, true);
    Coordinates n = Coordinates(vpn.x_scn() / n_vpn, vpn.y_scn() / n_vpn, vpn.z_scn() / n_vpn);
    Coordinates cross = Operations::cross_product_3d(_window->vup(), n, true);
    double n_cross = Operations::norma(cross);
    Coordinates u = Coordinates(cross.x() / n_cross, cross.y() / n_cross, cross.z() / n_cross);
    Coordinates v = Operations::cross_product_3d(n, u);
    // Translating and rotating the window in order to calculate the projection and normalization parameters
    _window->transform(Matrices::world_to_view(u.x(), u.y(), u.z(), v.x(), v.y(), v.z(),
                                               n.x(), n.y(), n.z(), cx, cy, cz), false, true);
    // Calculating the projection parameters(only used for perspective)
    double d = _window->vrp().z_scn();
    // Calculating the normalization parameters
    double sx = 1.0 / _window->max().x_scn();
    double sy = 1.0 / _window->max().y_scn();
    // Creating the projection and normalization matrix
    Matrix4x4 projection = (perspective) ? Matrices::perspective(u.x(), u.y(), u.z(), v.x(), v.y(), v.z(),
                                                                 n.x(), n.y(), n.z(), cx, cy, cz, sx, sy, d)
                                         : Matrices::parallel(u.x(), u.y(), u.z(), v.x(), v.y(), v.z(),
                                                              n.x(), n.y(), n.z(), cx, cy, cz, sx, sy);
    // Projecting and Normalizing every object
    for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
        (*it)->transform(projection, false, true);
    }
}

