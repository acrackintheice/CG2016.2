#include "spline_surface.hpp"

Spline_Surface::Spline_Surface(std::vector<Coordinates *> points, std::string name, Color *color)
        : Surface(points, name, color) {}

void Spline_Surface::clip_and_draw(cairo_t *cr, Coordinates win_min, Coordinates win_max,
                                   Coordinates vp_min, Coordinates vp_max, bool clip_flag) {

    double ns = 100;
    double nt = 100;
    // Creating the coefficient matrices
    Matrix4x4 Cx = Matrices::forward_diff_cx(_points, Matrices::bezier());
    Matrix4x4 Cy = Matrices::forward_diff_cy(_points, Matrices::bezier());
    // Creating the delta matrices
    Matrix4x4 Es = Matrices::forward_diff_es(1.0 / (ns));
    Matrix4x4 Et = Matrices::forward_diff_et(1.0 / (nt));
    // Creating the Fwd Diff (DDx, DDy) matrices
    Matrix4x4 DDx = Es.multiply4x4(Cx).multiply4x4(Et);
    Matrix4x4 DDy = Es.multiply4x4(Cy).multiply4x4(Et);
    // Draw ns curves along t.
    for (int i = 0; i <= ns; i++) {
        draw_fwd_diff(nt,
                      DDx.get(0,0),DDx.get(0,1),DDx.get(0,2),DDx.get(0,3),
                      DDy.get(0,0),DDy.get(0,1),DDy.get(0,2),DDy.get(0,3),
                      cr, win_min, win_max, vp_min, vp_max);
        DDx = update(DDx);
        DDy = update(DDy);
    }
    // Regenerating the matrices that were changed
    DDx = Es.multiply4x4(Cx).multiply4x4(Et).tranpose();
    DDy = Es.multiply4x4(Cy).multiply4x4(Et).tranpose();
    // Draw nt curves along s.
    for (int i = 0; i <= nt; i++) {
        draw_fwd_diff(ns,
                      DDx.get(0,0),DDx.get(0,1),DDx.get(0,2),DDx.get(0,3),
                      DDy.get(0,0),DDy.get(0,1),DDy.get(0,2),DDy.get(0,3),
                      cr, win_min, win_max, vp_min, vp_max);
        DDx = update(DDx);
        DDy = update(DDy);
    }
}

void
Spline_Surface::draw_fwd_diff(double n,
                              double x,
                              double Dx,
                              double D2x,
                              double D3x,
                              double y,
                              double Dy,
                              double D2y,
                              double D3y,
                              cairo_t *cr, Coordinates win_min, Coordinates win_max, Coordinates vp_min,
                              Coordinates vp_max) {
    Coordinates last_point = Coordinates(x, y, 0);
    for (int i = 0; i < n; ++i) {
        x = x + Dx;
        Dx = Dx + D2x;
        D2x = D2x + D3x;
        y = y + Dy;
        Dy = Dy + D2y;
        D2y = D2y + D3y;
        // Clipping and Drawing
        Coordinates current_point = Coordinates(x, y, 0);
        draw_edge(current_point, last_point, cr, win_min, win_max, vp_min, vp_max);
        last_point = current_point;
    }
}

Matrix4x4 Spline_Surface::update(Matrix4x4 D) {
    double l0[] = {D.get(0, 0) + D.get(1, 0), D.get(0, 1) + D.get(1, 1),
                   D.get(0, 2) + D.get(1, 2), D.get(0, 3) + D.get(1, 3)};

    double l1[] = {D.get(1, 0) + D.get(2, 0), D.get(1, 1) + D.get(2, 1),
                   D.get(1, 2) + D.get(2, 2), D.get(1, 3) + D.get(2, 3)};

    double l2[] = {D.get(2, 0) + D.get(3, 0), D.get(2, 1) + D.get(3, 1),
                   D.get(2, 2) + D.get(3, 2), D.get(2, 3) + D.get(3, 3)};

    double l3[] = {D.get(3, 0), D.get(3, 1), D.get(3, 2), D.get(3, 3)};
    return Matrix4x4(l0, l1, l2, l3);
}