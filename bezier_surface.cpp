#include "bezier_surface.hpp"

Bezier_Surface::Bezier_Surface(std::vector<Coordinates *> points, std::string name, Color *color)
        : Surface(points, name, color) {}

void Bezier_Surface::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                                   Coordinates vp_min, Coordinates vp_max, bool clip_flag) {
    double s = 1.0 / 16;
    double t = 1.0 / 16;
    // Creating the Bezier matrix
    Matrix4x4 M = Matrices::bezier();
    //  Mt is M transposed, for bezier its the same matrix
    Matrix4x4 Mt = M;
    // Checking if the points list has the correct size
    if (((_points.size() - 1) % 15) == 0) {
        // Finding the curves for every "patch" of the surface
        for (vector<Coordinates *>::iterator it = _points.begin(); it < _points.end() - 1; it = it + 15) {
            vector<Coordinates *> sub_points(it, it + 16);
            // Creating the Geometry matrices for the patch
            Matrix4x4 Gx = Matrices::gx(sub_points);
            Matrix4x4 Gy = Matrices::gy(sub_points);
            Matrix4x4 MGxMt = M.multiply4x4(Gx).multiply4x4(Mt);
            Matrix4x4 MGyMt = M.multiply4x4(Gy).multiply4x4(Mt);
            // Drawing many ts for a fixed S
            for (double k = 0; k <= 1; k += s) {
                double l1S[] = {(k * k * k), (k * k), k, 1};
                Matrix1x4 S = Matrix1x4(l1S);
                Coordinates last_point = Coordinates(0, 0, 0);
                for (double j = 0; j <= 1; j += t) {
                    Matrix4x1 T = Matrix4x1((j * j * j), (j * j), j, 1);
                    double x = S.multiply4x4(MGxMt).multiplyPor4x1(T);
                    double y = S.multiply4x4(MGyMt).multiplyPor4x1(T);
                    if (j == 0) {
                        last_point = Coordinates(x, y, 0);
                    } else {
                        // Clipping and Drawing
                        Coordinates current_point = Coordinates(x, y, 0);
                        draw_edge(current_point, last_point, cr, win_min, win_max, vp_min, vp_max);
                        last_point = current_point;
                    }
                }
            }
            // Drawing many s for a fixed t
            for (double k = 0; k <= 1; k += t) {
                Matrix4x1 T = Matrix4x1((k * k * k), (k * k), k, 1);
                vector<Coordinates *> curve_points;
                Coordinates last_point = Coordinates(0, 0, 0);
                for (double j = 0; j <= 1; j += s) {
                    double l1S[] = {(j * j * j), (j * j), j, 1};
                    Matrix1x4 S = Matrix1x4(l1S);
                    double x = S.multiply4x4(MGxMt).multiplyPor4x1(T);
                    double y = S.multiply4x4(MGyMt).multiplyPor4x1(T);
                    if (j == 0) {
                        last_point = Coordinates(x, y, 0);
                    } else {
                        // Clipping and Drawing
                        Coordinates current_point = Coordinates(x, y, 0);
                        draw_edge(current_point, last_point, cr, win_min, win_max, vp_min, vp_max);
                        last_point = current_point;
                    }
                }
            }
        }
    }

}