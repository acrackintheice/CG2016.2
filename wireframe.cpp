#include "wireframe.hpp"

using namespace std;

Wireframe::Wireframe(vector<Coordinates *> points, vector<Edge> edges, string name, Color *color,
                     Color *background_color, bool filled) {
    _points = points;
    _edges = edges;
    _name = name;
    _color = color;
    _filled = filled;
    _background_color = background_color;
}

vector<Edge> Wireframe::clip() {
    vector<Edge> clip_edges;
    vector<int> edge_codes = {1, 2, 3, 4};
    Coordinates P1_LEFT = Coordinates(-1, -10000, 0);
    Coordinates P2_LEFT =  Coordinates(-1, 10000, 0);
    clip_edges.push_back(Edge(&P1_LEFT, &P2_LEFT));
    Coordinates P1_RIGHT = Coordinates(1, -10000, 0);
    Coordinates P2_RIGHT = Coordinates(1, 1000, 0);
    clip_edges.push_back(Edge(&P1_RIGHT, &P2_RIGHT));
    Coordinates P1_TOP = Coordinates(-10000, 1, 0);
    Coordinates P2_TOP = Coordinates(10000, 1, 0);
    clip_edges.push_back(Edge(&P1_TOP, &P2_TOP));
    Coordinates P1_BOTTOM = Coordinates(-10000, -1, 0);
    Coordinates P2_BOTTOM = Coordinates(10000, -1, 0);
    clip_edges.push_back(Edge(&P1_BOTTOM, &P2_BOTTOM));
    vector<Edge> in;
    vector<Edge> out = _edges;
    int x = 1;
    // For every edge of the window
    for (vector<Edge>::iterator i1 = clip_edges.begin(); i1 != clip_edges.end(); ++i1,x++) {
        int edge_code = edge_codes[x-1];
        Edge clip_edge = *i1;
        in = out;
        out.clear();
        if (fake_frame(in)) {
            return sub_clip(in);
        }
        bool went_out = false;
        Coordinates *out_buffer;
        // For every edge in the wireframe
        for (vector<Edge>::iterator i2 = in.begin(); i2 != in.end(); ++i2) {
            Edge edge = *i2;
            Coordinates *E = edge.p1();
            Coordinates *S = edge.p2();
            // If( S inside EDGE )
            if (inside(S, edge_code)) {
                // If( E inside EDGE )
                if (inside(E, edge_code)) {
                    out.push_back(Edge(new Coordinates(E->x_scn(), E->y_scn(), 0),
                                       new Coordinates(S->x_scn(), S->y_scn(), 0)));
                }
                    // If( E outside EDGE )
                else {
                    Coordinates *new_E = Operations::intersection_between_lines(E, S, clip_edge.p1(),
                                                                                  clip_edge.p2());
                    if (went_out) {
                        out.push_back(Edge(out_buffer, new_E));
                        went_out = false;
                    }
                    out.push_back(Edge(new_E, new Coordinates(S->x_scn(), S->y_scn(), 0)));
                }
            }
                // If(S outside EDGE )
            else {
                // IF ( E inside EDGE )
                if (inside(E, edge_code)) {
                    Coordinates *new_S = Operations::intersection_between_lines(E, S, clip_edge.p1(),
                                                                                  clip_edge.p2());
                    out.push_back(Edge(new Coordinates(E->x_scn(), E->y_scn(), 0), new_S));
                    out_buffer = new_S;
                    went_out = true;
                } else {

                }
            }
        }
    }
    if (fake_frame(in)) {
        return sub_clip(in);
    }
    return out;
}

// E1 => 0xb6b890, 0xb6b850
bool Wireframe::inside(Coordinates *point, int edge_code) {
    if (edge_code == 1) {
        return point->x_scn() >= -1;
    } else if (edge_code == 2) {
        return point->x_scn() <= 1;
    } else if (edge_code == 3) {
        return point->y_scn() <= 1;
    } else if (edge_code == 4) {
        return point->y_scn() >= -1;
    } else
        return false;
}

vector<Edge> Wireframe::sub_clip(std::vector<Edge> in) {
    vector<Edge> output;
    if (in.size() == 1) {
        Coordinates *p1 = in[0].p1();
        Coordinates *p2 = in[0].p2();
        Line l = Line(new Coordinates(p1->x_scn(), p1->y_scn(), 0),
                      new Coordinates(p2->x_scn(), p2->y_scn(), 0), "", new Color(1, 1, 1, 1));
        output = l.clip2();
    }
    return output;
}

bool Wireframe::fake_frame(std::vector<Edge> in) {
    return in.size() < 2;
}