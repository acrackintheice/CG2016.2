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
#include "bspline.hpp"
#include "matrices.cpp"

using namespace std;

static vector<Edge> edges_from_points(vector<Coordinates *> points) {
    vector<Edge> edges;
    vector<Coordinates *>::iterator it = points.begin();
    for (int i = 0; i < points.size() - 1; i++) {
        Coordinates *p1 = *it;
        it++;
        Coordinates *p2 = *it;
        edges.push_back(Edge(p1, p2));
    }
    return edges;
}

int main(int argc, char *argv[]) {

    Window *window = new Window(new Coordinates(-500, -500, 0), new Coordinates(-500, 500, 0),
                                new Coordinates(500, 500, 0), new Coordinates(500, -500, 0),
                                new Coordinates(0, 500, 0), new Coordinates(0, 0, 500),
                                new Coordinates(0,0, -2000));
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

    // (-200,-200,-200) (200,-200,-200) (-200,200,-200) (200,200,-200) (-200,-200,200) (200,-200,200) (-200,200,200) (200,200,200)
    // (0,1) (0,2) (0,4) (1,3) (1,5) (2,3) (2,6) (3,7) (4,6) (4,5) (5,7) (6,7)

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
    vector<Edge> wireframe_edges = edges_from_points(wireframe_points);
    Wireframe *w = new Wireframe(wireframe_points, wireframe_edges, "Wireframe", new Color(0, 0, 255, 1),
                                 new Color(1, 1, 1, 1), false);
    Line *l = new Line(new Coordinates(0, 0, 0), new Coordinates(100, 100, 0), "Line", new Color(0, 0, 0, 1));

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
    BSpline *c = new BSpline(curve_points, "Curve", new Color(0, 0, 255, 1));
    /* (0,-70) (-65,-30) (-65,30) (0,70) (65,30) (65,-30) (0,-70) (-65,-30) (-65,30) */
    world->add_object(c);
    world->add_object(pol);
    world->add_object(w);

    UI ui = UI(argc, argv, world);
    return 0;
}
