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

vector<Drawing_Edge> Wireframe::clip(bool clip_flag) {
    vector<Drawing_Edge> clip_edges;
    vector<int> edge_codes = {1, 2, 3, 4};
    Coordinates P1_LEFT = Coordinates(-1, -10000, 0);
    Coordinates P2_LEFT = Coordinates(-1, 10000, 0);
    clip_edges.push_back(Drawing_Edge(P1_LEFT, P2_LEFT));
    Coordinates P1_RIGHT = Coordinates(1, -10000, 0);
    Coordinates P2_RIGHT = Coordinates(1, 1000, 0);
    clip_edges.push_back(Drawing_Edge(P1_RIGHT, P2_RIGHT));
    Coordinates P1_TOP = Coordinates(-10000, 1, 0);
    Coordinates P2_TOP = Coordinates(10000, 1, 0);
    clip_edges.push_back(Drawing_Edge(P1_TOP, P2_TOP));
    Coordinates P1_BOTTOM = Coordinates(-10000, -1, 0);
    Coordinates P2_BOTTOM = Coordinates(10000, -1, 0);
    clip_edges.push_back(Drawing_Edge(P1_BOTTOM, P2_BOTTOM));
    vector<Drawing_Edge> in;
    vector<Drawing_Edge> out;
    for (vector<Edge>::iterator it = _edges.begin(); it != _edges.end(); it++) {
        Edge e = *it;
        out.push_back(Drawing_Edge(Coordinates(e.p1()->x_scn(), e.p1()->y_scn(), e.p1()->z_scn()),
                                   Coordinates(e.p2()->x_scn(), e.p2()->y_scn(), e.p2()->z_scn())));
    }
    int x = 1;
    // For every edge of the window
    for (vector<Drawing_Edge>::iterator i1 = clip_edges.begin(); i1 != clip_edges.end(); ++i1, x++) {
        int edge_code = edge_codes[x - 1];
        Drawing_Edge clip_edge = *i1;
        if (fake_frame(out)) {
            return sub_clip(out);
        }
        in = out;
        out.clear();
        bool went_out = false;
        Coordinates out_buffer = Coordinates(0, 0, 0);
        // For every edge in the wireframe
        for (vector<Drawing_Edge>::iterator i2 = in.begin(); i2 != in.end(); ++i2) {
            Drawing_Edge edge = *i2;
            Coordinates E = edge.p1();
            Coordinates S = edge.p2();
            if (inside(S, edge_code)) { // If( S inside EDGE )
                if (inside(E, edge_code)) { // If( E inside EDGE )
                    out.push_back(Drawing_Edge(E, S));
                } else { // If( E outside EDGE )
                    Coordinates new_E = Operations::intersection(E, S, clip_edge.p1(), clip_edge.p2());
                    if (went_out) {
                        out.push_back(Drawing_Edge(out_buffer, new_E));
                        went_out = false;
                    }
                    out.push_back(Drawing_Edge(new_E, S));
                }
            } else { // If(S outside EDGE )
                if (inside(E, edge_code)) { // IF ( E inside EDGE )
                    Coordinates new_S = Operations::intersection(E, S, clip_edge.p1(), clip_edge.p2());
                    out.push_back(Drawing_Edge(E, new_S));
                    out_buffer = new_S;
                    went_out = true;
                }
            }
        }
    }
    if (fake_frame(out)) {
        return sub_clip(out);
    }
    return out;
}

bool Wireframe::inside(Coordinates point, int edge_code) {
    if (edge_code == 1) {
        return point.x_scn() >= -1;
    } else if (edge_code == 2) {
        return point.x_scn() <= 1;
    } else if (edge_code == 3) {
        return point.y_scn() <= 1;
    } else if (edge_code == 4) {
        return point.y_scn() >= -1;
    } else
        return false;
}

vector<Drawing_Edge> Wireframe::sub_clip(vector<Drawing_Edge> in) {
    vector<Drawing_Edge> output;
    if (in.size() == 1) {
        Coordinates p1 = in[0].p1();
        Coordinates p2 = in[0].p2();
        Line l = Line(new Coordinates(p1.x(), p1.y(), p1.z()), new Coordinates(p2.x(), p2.y(), p2.z()), "",
                      new Color(1, 1, 1, 1));
        output = l.clip();
    }
    return output;
}

bool Wireframe::fake_frame(std::vector<Drawing_Edge> in) {
    return in.size() < 2;
}