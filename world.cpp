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
        double cx = _window->vrp().x();
        double cy = _window->vrp().y();
        double cz = _window->vrp().z();
        Matriz4x4 translation = Matrices::translation(-cx, -cy, -cz);
        for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object *obj = (*it);
                obj->transform(translation, false, true);
        }
        // Calculating the rotation vectors
        Coordinates vup = _window->vup();
        double n_vup = Operations::norma(vup, true);
        vup.set_xyz(vup.x_scn() / n_vup, vup.y_scn() / n_vup, vup.z_scn() / n_vup);
        Coordinates vpn = _window->vpn();
        n_vup = Operations::norma(vup, true);
        double n_vpn = Operations::norma(vpn, true);
        Coordinates n = Coordinates(vpn.x_scn() / n_vpn, vpn.y_scn() / n_vpn, vpn.z_scn() / n_vpn);
        double n_n = Operations::norma(n, true);
        Coordinates cross = Operations::cross_product_3d(vup, n, true);
        double n_cross = Operations::norma(cross);
        Coordinates u = Coordinates(cross.x() / n_cross, cross.y() / n_cross, cross.z() / n_cross);
        double n_u = Operations::norma(u, true);
        Coordinates v = Operations::cross_product_3d(n, u);
        double n_v = Operations::norma(v, true);
        // Translating and Rotating the World using the projection matrix
        //Matriz4x4 projection = Matrices::projection(u.x(), u.y(), u.z(), v.x(), v.y(), v.z(),
        //                                            n.x(), n.y(), n.z(), cx, cy, cz);
        Matriz4x4 projection = Matrices::projection_rotation(u.x(), u.y(), u.z(), v.x(), v.y(), v.z(),
                                                             n.x(), n.y(), n.z());
        for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object *obj = (*it);
            obj->transform(projection, true, true);
        }
        // Calculating sx, sy for the normalization
        double sx = 1.0 / fabs(_window->vrp().x_scn() - _window->min().x_scn());
        double sy = 1.0 / fabs(_window->vrp().x_scn() - _window->min().y_scn());
        // Dropping Z and normalizing the world
        Matriz4x4 normalization = Matrices::normalization(sx, sy);
        for (vector<Object *>::iterator it = _objects.begin(); it != _objects.end(); it++) {
            Object *obj = (*it);
            obj->transform(normalization, true, true);
        }
    }
}