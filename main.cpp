#include <vector>
#include <iostream>
#include <algorithm>
#include "point.hpp"
#include "line.hpp"
#include "object.hpp"
#include "wireframe.hpp"
#include "ui.hpp"
#include "world.hpp"
#include "window.hpp"
#include "math.h"
#include "operations.cpp"
#include "curve.hpp"
#include "spline_curve.hpp"
#include "matrices.cpp"
#include "surface.hpp"
#include "bezier_surface.hpp"
#include "spline_surface.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    Window *window = new Window(new Coordinates(-500, -500, 0), new Coordinates(-500, 500, 0),
                                new Coordinates(500, 500, 0), new Coordinates(500, -500, 0),
                                new Coordinates(0, 500, 0), new Coordinates(0, 0, 500),
                                new Coordinates(0, 0, -2000));
    World *world = new World(window);

    vector<Coordinates *> cube_points;
    Coordinates *A = new Coordinates(-200, -200, 400);
    Coordinates *B = new Coordinates(200, -200, 400);
    Coordinates *C = new Coordinates(-200, 200, 400);
    Coordinates *D = new Coordinates(200, 200, 400);
    Coordinates *E = new Coordinates(-200, -200, 200);
    Coordinates *F = new Coordinates(200, -200, 200);
    Coordinates *G = new Coordinates(-200, 200, 200);
    Coordinates *H = new Coordinates(200, 200, 200);

    cube_points.push_back(A);
    cube_points.push_back(B);
    cube_points.push_back(C);
    cube_points.push_back(D);
    cube_points.push_back(E);
    cube_points.push_back(F);
    cube_points.push_back(G);
    cube_points.push_back(H);

    vector<Edge> cube_edges;
    cube_edges.push_back(Edge(A, B));
    cube_edges.push_back(Edge(A, C));
    cube_edges.push_back(Edge(A, E));
    cube_edges.push_back(Edge(B, D));
    cube_edges.push_back(Edge(B, F));
    cube_edges.push_back(Edge(C, D));
    cube_edges.push_back(Edge(C, G));
    cube_edges.push_back(Edge(D, H));
    cube_edges.push_back(Edge(E, G));
    cube_edges.push_back(Edge(E, F));
    cube_edges.push_back(Edge(F, H));
    cube_edges.push_back(Edge(G, H));

    Wireframe *pol = new Wireframe(cube_points, cube_edges, "Cube", new Color(0, 0, 0, 1), new Color(1, 1, 1, 1),
                                   false);

    vector<Coordinates *> wireframe_points;
    wireframe_points.push_back(new Coordinates(0, 0, 0));
    wireframe_points.push_back(new Coordinates(0, 200, 0));
    wireframe_points.push_back(new Coordinates(200, 200, 0));
    wireframe_points.push_back(new Coordinates(200, 0, 0));
    wireframe_points.push_back(new Coordinates(100, -100, 0));
    vector<Edge> wireframe_edges = Operations::edges_from_points(wireframe_points);
    Wireframe *w = new Wireframe(wireframe_points, wireframe_edges, "Wireframe", new Color(0, 0, 255, 1),
                                 new Color(1, 1, 1, 1), false);
    Line *l = new Line(new Coordinates(-600, -600, -2000), new Coordinates(600, 600, -2000), "Line",
                       new Color(0, 0, 0, 1));

    vector<Coordinates *> curve_points;
    curve_points.push_back(new Coordinates(0, -70, 0));
    curve_points.push_back(new Coordinates(-65, -30, 0));
    curve_points.push_back(new Coordinates(-65, 30, 0));
    curve_points.push_back(new Coordinates(0, 70, 0));
    curve_points.push_back(new Coordinates(65, 30, 0));
    curve_points.push_back(new Coordinates(65, -30, 0));
    curve_points.push_back(new Coordinates(0, -70, 0));
    curve_points.push_back(new Coordinates(-65, -30, 0));
    curve_points.push_back(new Coordinates(-65, 30, 0));


    Spline_Curve *c = new Spline_Curve(curve_points, "Curve", new Color(0, 0, 0, 1));

    vector<Coordinates *> s_points;
    s_points.push_back(new Coordinates(-200, 200, 0)); // p11
    s_points.push_back(new Coordinates(-100, 200, 400));
    s_points.push_back(new Coordinates(100, 200, 400));
    s_points.push_back(new Coordinates(200, 200, 0)); // p14
    s_points.push_back(new Coordinates(-200, 100, 400));
    s_points.push_back(new Coordinates(-100, 100, 400));
    s_points.push_back(new Coordinates(100, 100, 400));
    s_points.push_back(new Coordinates(200, 100, 400));
    s_points.push_back(new Coordinates(-200, -100, 400));
    s_points.push_back(new Coordinates(-100, -100, 400));
    s_points.push_back(new Coordinates(100, -100, 400));
    s_points.push_back(new Coordinates(200, -100, 400));
    s_points.push_back(new Coordinates(-200, -200, 0)); // p41
    s_points.push_back(new Coordinates(-100, -200, 400));
    s_points.push_back(new Coordinates(100, -200, 400));
    s_points.push_back(new Coordinates(200, -200, 0)); // p44

    vector<Coordinates *> s2_points;
    s2_points.push_back(new Coordinates(-100, 300, 100));
    s2_points.push_back(new Coordinates(000, 300, 100));
    s2_points.push_back(new Coordinates(100, 300, 100));
    s2_points.push_back(new Coordinates(200, 300, 100));

    s2_points.push_back(new Coordinates(-100, 300, 200));
    s2_points.push_back(new Coordinates(000, -200, 200));
    s2_points.push_back(new Coordinates(100, -200, 200));
    s2_points.push_back(new Coordinates(200, 300, 200));

    s2_points.push_back(new Coordinates(-100, 300, 300));
    s2_points.push_back(new Coordinates(000, -200, 300));
    s2_points.push_back(new Coordinates(100, -200, 300));
    s2_points.push_back(new Coordinates(200, 300, 300));

    s2_points.push_back(new Coordinates(-100, 300, 400));
    s2_points.push_back(new Coordinates(000, 300, 400));
    s2_points.push_back(new Coordinates(100, 300, 400));
    s2_points.push_back(new Coordinates(200, 300, 400));

    Surface *s = new Bezier_Surface(s2_points, "Surface", new Color(0, 0, 0, 1), true);

    pol->translate(200, 200, 0);
    w->translate(200, 200, 0);
    c->translate(200, 200, 0);

    //world->add_object(pol);
    //world->add_object(w);
    world->add_object(c);
    world->add_object(s);

    UI ui = UI(argc, argv, world);
    return 0;
}
