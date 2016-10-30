#include "line.hpp"

using namespace std;

Line::Line(Coordinates *p1, Coordinates *p2, string name, Color *color) {
    _points.push_back(p1);
    _points.push_back(p2);
    _edges.push_back(Edge(p1, p2));
    _name = name;
    _color = color;
    _filled = false;
    _background_color = new Color(1, 1, 1, 1);
}

vector<Drawing_Edge> Line::clip(bool clip_flag) {
    vector<Drawing_Edge> output;
    Coordinates p1 = Coordinates(_points[0]->x_scn(), _points[0]->y_scn(), 0);
    Coordinates p2 = Coordinates(_points[1]->x_scn(), _points[1]->y_scn(), 0);
    if (clip_flag) {
        // Cohen-Sutherland
        const int INSIDE = 0; // 0000
        const int LEFT = 1;   // 0001
        const int RIGHT = 2;  // 0010
        const int BOTTOM = 4; // 0100
        const int TOP = 8;    // 1000
        /* Defining the region codes */
        /* Define RC = 0000 and go changing it with consecutive OR operations*/
        int RC1 = INSIDE;
        if (p1.x() <= -1)
            RC1 = (RC1 | LEFT);
        else if (p1.x() >= 1)
            RC1 = (RC1 | RIGHT);
        if (p1.y() <= -1)
            RC1 = (RC1 | BOTTOM);
        else if (p1.y() >= 1)
            RC1 = (RC1 | TOP);
        /* The same for for p2 */
        int RC2 = INSIDE;
        if (p2.x() <= -1)
            RC2 = (RC2 | LEFT);
        else if (p2.x() >= 1)
            RC2 = (RC2 | RIGHT);
        if (p2.y() <= -1)
            RC2 = (RC2 | BOTTOM);
        else if (p2.y() >= 1)
            RC2 = (RC2 | TOP);
        /* Checking whether the  line is fully visibile, invisble or partially visible*/
        /* First, checking if the line is contained in the window(RC1=RC2=[0,0,0,0])*/
        if ((RC1 | RC2) == 0) {
            /* If it is, everything will be drawn, so we add the whole line to the output list*/
            output.push_back(Drawing_Edge(Coordinates(p1.x(), p1.y(), 0), Coordinates(p2.x(), p2.y(), 0)));
        }
            /* Now, checking if the line completely out of the window(RC1^RC2 != [0,0,0,0]) */
        else if ((RC1 & RC2) != 0) {
            /* If it is, nothing will be drawn and a empty output list is returned*/
            output.clear();
        }
            /* Then, if the line is not all in or all out, its partially in/out */
        else {
            Coordinates new_p1 = Coordinates(0, 0, 0);
            Coordinates new_p2 = Coordinates(0, 0, 0);
            double x, y;
            double m = (p2.y() - p1.y()) / (p2.x() - p1.x());
            /* Checking if RC1 is out of the window*/
            if (RC1 != 0) {
                if ((RC1 & TOP) != 0) {
                    /* point is above the clip rectangle */
                    x = p1.x() + 1 / m * (1 - p1.y());
                    y = 1;
                    if (x >= -1 && x <= 1)
                        new_p1 = Coordinates(x, 1, 0);
                }
                if ((RC1 & BOTTOM) != 0) {
                    /* point is below the clip rectangle */
                    x = p1.x() + 1 / m * (-1 - p1.y());
                    if (x >= -1 && x <= 1)
                        new_p1 = Coordinates(x, -1, 0);
                }
                if ((RC1 & RIGHT) != 0) {
                    /* point is to the right of clip rectangle */
                    y = m * (1 - p1.x()) + p1.y();
                    if (y >= -1 && y <= 1)
                        new_p1 = Coordinates(1, y, 0);
                }
                if ((RC1 & LEFT) != 0) {
                    /* point is to the left of clip rectangle */
                    y = m * (-1 - p1.x()) + p1.y();
                    if (y >= -1 && y <= 1)
                        new_p1 = Coordinates(-1, y, 0);
                }
            }
                /* Else, it is inside the window*/
            else
                new_p1 = Coordinates(p1.x(), p1.y(), 0);
            /* Checking if RC2 is out of the window*/
            if (RC2 != 0) {
                if ((RC2 & TOP) != 0) {
                    /* point is above the clip rectangle */
                    x = p2.x() + 1 / m * (1 - p2.y());
                    y = 1;
                    if (x >= -1 && x <= 1)
                        new_p2 = Coordinates(x, y, 0);
                }
                if ((RC2 & BOTTOM) != 0) {
                    /* point is below the clip rectangle */
                    x = p2.x() + 1 / m * (-1 - p2.y());
                    y = -1;
                    if (x >= -1 && x <= 1)
                        new_p2 = Coordinates(x, y, 0);
                }
                if ((RC2 & RIGHT) != 0) {
                    /* point is to the right of clip rectangle */
                    y = m * (1 - p2.x()) + p2.y();
                    x = 1;
                    if (y >= -1 && y <= 1)
                        new_p2 = Coordinates(x, y, 0);
                }
                if ((RC2 & LEFT) != 0) {
                    /* point is to the left of clip rectangle */
                    y = m * (-1 - p2.x()) + p2.y();
                    x = -1;
                    if (y >= -1 && y <= 1)
                        new_p2 = Coordinates(x, y, 0);
                }
            } else {
                new_p2 = Coordinates(p2.x(), p2.y(), 0);
            }
            output.push_back(Drawing_Edge(new_p1, new_p2));
        }
        return output;
    } else {
        // Liang-Barsky
        vector<double> ps;
        ps.push_back(-(p2.x() - p1.x()));
        ps.push_back(p2.x() - p1.x());
        ps.push_back(-(p2.y() - p1.y()));
        ps.push_back(p2.y() - p1.y());
        vector<double> qs;
        qs.push_back(p1.x() + 1);
        qs.push_back(1 - p1.x());
        qs.push_back(p1.y() + 1);
        qs.push_back(1 - p1.y());
        vector<double> rs_less_than_zero, rs_more_than_zero;
        vector<double>::iterator it_ps;
        vector<double>::iterator it_qs;
        for (it_ps = ps.begin(), it_qs = qs.begin(); it_ps != ps.end(); it_ps++, it_qs++) {
            double p = *(it_ps);
            double q = *(it_qs);
            if (p == 0 & q < 0) {
                return output;
            } else if (p < 0) {
                rs_less_than_zero.push_back(q / p);
            } else if (p > 0) {
                rs_more_than_zero.push_back(q / p);
            }
        }
        double u1 = 0;
        vector<double>::iterator it;
        for (it = rs_less_than_zero.begin(); it != rs_less_than_zero.end(); it++) {
            double r = *(it);
            u1 = max(u1, r);
        }
        double u2 = 1;
        for (it = rs_more_than_zero.begin(); it != rs_more_than_zero.end(); it++) {
            double r = *(it);
            u2 = min(u2, r);
        }
        if (u1 > u2) {
            return output;
        } else {
            output.push_back(
                    Drawing_Edge(Coordinates(p1.x() + u1 * (p2.x() - p1.x()), p1.y() + u1 * (p2.y() - p1.y()), 0),
                                 Coordinates(p1.x() + u2 * (p2.x() - p1.x()), p1.y() + u2 * (p2.y() - p1.y()), 0)));
            return output;
        }
    }
}