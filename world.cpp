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
    if (perspective) {

    } else {
        // The projection goes as:
        // Translation -> Rotation -> Scale -> Ignore Z
        // The Translation and Rotation are executed together using a Projection Matrix
        // Scaling and ignoring z are also executed together using the Normalization Matrix
        // Before Translating and Rotating the world, the window and her vectors are translated in order to calculate
        // the rotation vectors that are used in the rotations of the Projection Matrix.
        // I couldn't get the Projection to work putting the 4 operations together.

        // Starting the Work !!!
        // Translating the Window, VPN and Vup in order to calculate the rotation vectors
        double cx = _window->geometric_center().x();
        double cy = _window->geometric_center().y();
        double cz = _window->geometric_center().z();
        Matriz4x4 translation = Matrices::generate_translation_matrix(-cx, -cz, -cy);
        _window->transform(translation, false, true);
        // Calculating the rotation vectors
        Coordinates vpn = Coordinates(_window->vpn().x_scn(), _window->vpn().y_scn(), _window->vpn().z_scn());
        Coordinates vup = Coordinates(_window->vup().x_scn(), _window->vup().y_scn(), _window->vup().z_scn());
        double n_vpn = Operations::norma(vpn);
        Coordinates n = Coordinates(vpn.x() / n_vpn, vpn.y() / n_vpn, vpn.z() / n_vpn);
        Coordinates cross = Operations::cross_product_3d(vup, n);
        double n_cross = Operations::norma(cross);
        Coordinates u = Coordinates(cross.x() / n_cross, cross.y() / n_cross, cross.z() / n_cross);
        Coordinates v = Operations::cross_product_3d(n, u);
        // Translating and Rotating the World using the projection matrix
        Matriz4x4 projection_matrix = Matrices::generate_projection_matrix(u.x(),u.y(),u.z(),v.x(),v.y(),v.z(),n.x(),n.y(),n.z(),cx,cy,cz);
        for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object *obj = (*it);
            obj->transform(projection_matrix, false, true);
        }
        // Calculating sx, sy for the normalization
        Coordinates center = _window->geometric_center(false, true);
        Coordinates window_min = _window->min();
        double sx = 1.0 / fabs(center.x() - window_min.x_scn());
        double sy = 1.0 / fabs(center.y() - window_min.y_scn());
        // Dropping Z and normalizing the world
        Matriz4x4 normalization_matrix = Matrices::generate_normalization_matrix(sx,sy);
        for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object *obj = (*it);
            obj->transform(normalization_matrix, true, true);
        }
    }
}