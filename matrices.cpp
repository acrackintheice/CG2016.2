#ifndef MATRICES_CPP
#define MATRICES_CPP

#include "math.h"
#include "matriz4x4.hpp"

using namespace std;

class Matrices {

public:
    static Matriz4x4 translation(double dx, double dy, double dz) {
        double l0[] = {1, 0, 0, dx};
        double l1[] = {0, 1, 0, dy};
        double l2[] = {0, 0, 1, dz};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 scaling(double sx, double sy, double sz, double cx, double cy, double cz) {
        double l0[] = {sx, 0, 0, (-cx * sx) + cx};
        double l1[] = {0, sy, 0, (-cy * sy) + cy};
        double l2[] = {0, 0, sz, (-cz * sz) + cz};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 rotate_x(double angle) {
        double l0[] = {1, 0, 0, 0};
        double l1[] = {0, cos(angle), -sin(angle), 0};
        double l2[] = {0, sin(angle), cos(angle), 0};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 rotate_y(double angle) {
        double l0[] = {cos(angle), 0, sin(angle), 0};
        double l1[] = {0, 1, 0, 0};
        double l2[] = {-sin(angle), 0, cos(angle), 0};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 rotate_z(double angle) {
        double l0[] = {cos(angle), -sin(angle), 0, 0};
        double l1[] = {sin(angle), cos(angle), 0, 0};
        double l2[] = {0, 0, 1, 0};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 arbitrary_rotation(double u, double v, double w, double a, double b,
                                        double c, double j, double k, double l) {
        double l0_0 = pow(u, 2) + (pow(v, 2) + pow(w, 2)) * j;
        double l0_1 = u * v * (1 - j) - w * sqrt(l) * k;
        double l0_2 = u * w * (1 - j) + v * sqrt(l) * k;
        double l0_3 = (a * (pow(v, 2) + pow(w, 2)) - u * (b * v + c * w)) * (1 - j) + (b * w - c * v) * sqrt(l) * k;

        double l1_0 = u * v * (1 - j) + w * sqrt(l) * k;
        double l1_1 = pow(v, 2) + (pow(u, 2) + pow(w, 2)) * j;
        double l1_2 = v * w * (1 - j) - u * sqrt(l) * k;
        double l1_3 = (b * (pow(u, 2) + pow(w, 2)) - v * (a * u + c * w)) * (1 - j) + (c * u - a * w) * sqrt(l) * k;

        double l2_0 = u * w * (1 - j) - v * sqrt(l) * k;
        double l2_1 = v * w * (1 - j) + u * sqrt(l) * k;
        double l2_2 = pow(w, 2) + (pow(u, 2) + pow(v, 2)) * j;
        double l2_3 = (c * (pow(u, 2) + pow(v, 2)) - w * (a * u + b * v)) * (1 - j) + (a * v - b * u) * sqrt(l) * k;

        double l0[] = {l0_0 / l, l0_1 / l, l0_2 / l, l0_3 / l};
        double l1[] = {l1_0 / l, l1_1 / l, l1_2 / l, l1_3 / l};
        double l2[] = {l2_0 / l, l2_1 / l, l2_2 / l, l2_3 / l};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 world_to_view(double ux, double uy, double uz, double vx, double vy, double vz,
                                   double nx, double ny, double nz, double cx, double cy, double cz) {
        double l0[] = {ux, uy, uz, -cx};
        double l1[] = {vx, vy, vz, -cy};
        double l2[] = {nx, ny, nz, -cz};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 parallel(double ux, double uy, double uz, double vx, double vy, double vz,
                              double nx, double ny, double nz, double cx, double cy, double cz,
                              double sx, double sy) {
        double l0[] = {sx * ux, sx * uy, sx * uz, -(cx * sx * ux) - cy * sx * uy - cz * sx * uz};
        double l1[] = {sy * vx, sy * vy, sy * vz, -(cx * sy * vx) - cy * sy * vy - cz * sy * vz};
        double l2[] = {nx, ny, nz, -(cx * nx) - cy * ny - cz * nz};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 perspective(double ux, double uy, double uz, double vx, double vy, double vz,
                                 double nx, double ny, double nz, double cx, double cy, double cz,
                                 double sx, double sy, double d) {
        double l0[] = {sx * ux, sx * uy, sx * uz, -(cx * sx * ux) - cy * sx * uy - cz * sx * uz};
        double l1[] = {sy * vx, sy * vy, sy * vz, -(cx * sy * vx) - cy * sy * vy - cz * sy * vz};
        double l2[] = {nx, ny, nz, -(cx * nx) - cy * ny - cz * nz};
        double l3[] = {nx / d, ny / d, nz / d, -((cx * nx) / d) - (cy * ny) / d - (cz * nz) / d};
        return Matriz4x4(l0, l1, l2, l3);
    }

    static Matriz4x4 rotations(double ux, double uy, double uz, double vx, double vy, double vz,
                               double nx, double ny, double nz) {
        double l0[] = {ux, uy, uz, 0};
        double l1[] = {vx, vy, vz, 0};
        double l2[] = {nx, ny, nz, 1};
        double l3[] = {0, 0, 0, 1};
        return Matriz4x4(l0, l1, l2, l3);
    }
};

#endif 


