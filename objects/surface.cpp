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

// Drawing with blending functions
std::vector<Drawing_Edge> Surface::clip(bool clip_flag) {
    std::vector<Drawing_Edge> output;
    std::vector<Wireframe*> curves;
    if (_bspline) {

    } else {
        double s = 0.01;
        double t = 0.01;
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
                    vector<Coordinates *> curve_points;
                    for (double j = 0; j <= 1; j += t) {
                        Matriz4x1 T = Matriz4x1((j * j * j), (j * j), j, 1);
                        double x = S.multiplicarPor4x4(MGxMt).multiplicarPor4x1(T);
                        double y = S.multiplicarPor4x4(MGyMt).multiplicarPor4x1(T);
                        // Finding the curve points
                        curve_points.push_back(new Coordinates(x, y, 0));
                    }
                    // Turning the curve points into a wireframe
                    vector<Edge> curve_edges = Operations::edges_from_points(curve_points);
                    // Adding to the list of curves(wireframes)
                    curves.push_back(new Wireframe(curve_points, curve_edges));
                }
                // Drawing many s for a fixed t
                for (double k = 0; k <= 1; k += t) {
                    Matriz4x1 T = Matriz4x1((k * k * k), (k * k), k, 1);
                    vector<Coordinates *> curve_points;
                    for (double j = 0; j <= 1; j += s) {
                        double l1S[] = {(j * j * j), (j * j), j, 1};
                        Matriz1x4 S = Matriz1x4(l1S);
                        double x = S.multiplicarPor4x4(MGxMt).multiplicarPor4x1(T);
                        double y = S.multiplicarPor4x4(MGyMt).multiplicarPor4x1(T);
                        // Finding the curve points
                        curve_points.push_back(new Coordinates(x, y, 0));
                    }
                    // Turning the curve points into a wireframe
                    vector<Edge> curve_edges = Operations::edges_from_points(curve_points);
                    // Adding to the list of curves(wireframes)
                    curves.push_back(new Wireframe(curve_points, curve_edges));
                }
            }
        }
        // Adding the wireframes edges to a list of edges, in order to draw them
        for(vector<Wireframe*>::iterator it = curves.begin(); it != curves.end(); it++){
            vector<Drawing_Edge> edges = (*it)->clip();
            output.insert(output.end(), edges.begin(), edges.end());
        }
    }
    return output;
}
