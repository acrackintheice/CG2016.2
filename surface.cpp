#include "surface.hpp"
#include "wireframe.hpp"

Surface::Surface(std::vector<Coordinates *> points, std::string name, Color *color, bool bspline) {
    _points = points;
    _name = name;
    _color = color;
    _filled = false;
    _background_color = new Color(1, 1, 1, 1);
    _bspline = bspline;
}

void Surface::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                            Coordinates vp_min, Coordinates vp_max, bool clip_flag) {
    if (_bspline) {
    } else {
        double s = 1.0/16;
        double t = 1.0/16;
        // Creating the Bezier matrix
        Matriz4x4 M = Matrices::bezier();
        //  Mt is M transposed, for bezier its the same matrix
        Matriz4x4 Mt = M;
        // Checking if the points list has the correct size
        if (((_points.size() - 1) % 15) == 0) {
            // Finding the curves for every "patch" of the surface
            for (vector<Coordinates *>::iterator it = _points.begin(); it < _points.end() - 1; it = it + 15) {
                vector<Coordinates *> sub_points(it, it + 16);
                // Creating the Geometry matrices for the patch
                Matriz4x4 Gx = Matrices::GBx(sub_points);
                Matriz4x4 Gy = Matrices::GBy(sub_points);
                Matriz4x4 MGxMt = M.multiplicarPor4x4(Gx).multiplicarPor4x4(Mt);
                Matriz4x4 MGyMt = M.multiplicarPor4x4(Gy).multiplicarPor4x4(Mt);
                // Drawing many ts for a fixed S
                for (double k = 0; k <= 1; k += s) {
                    double l1S[] = {(k * k * k), (k * k), k, 1};
                    Matriz1x4 S = Matriz1x4(l1S);
                    Coordinates last_point = Coordinates(0, 0, 0);
                    for (double j = 0; j <= 1; j += t) {
                        Matriz4x1 T = Matriz4x1((j * j * j), (j * j), j, 1);
                        double x = S.multiplicarPor4x4(MGxMt).multiplicarPor4x1(T);
                        double y = S.multiplicarPor4x4(MGyMt).multiplicarPor4x1(T);
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
                    Matriz4x1 T = Matriz4x1((k * k * k), (k * k), k, 1);
                    vector<Coordinates *> curve_points;
                    Coordinates last_point = Coordinates(0, 0, 0);
                    for (double j = 0; j <= 1; j += s) {
                        double l1S[] = {(j * j * j), (j * j), j, 1};
                        Matriz1x4 S = Matriz1x4(l1S);
                        double x = S.multiplicarPor4x4(MGxMt).multiplicarPor4x1(T);
                        double y = S.multiplicarPor4x4(MGyMt).multiplicarPor4x1(T);
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
}
