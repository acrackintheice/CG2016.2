#ifndef OPERATIONS_CPP
#define OPERATIONS_CPP

#include "coordinates.hpp"
#include "math.h"
#include "edge.hpp"
#include "drawing_edge.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

class Operations {

public:

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

    static double norma(Coordinates vector, bool use_scn = false) {
        if (use_scn)
            return sqrt(vector.x_scn() * vector.x_scn() + vector.y_scn() * vector.y_scn() +
                        vector.z_scn() * vector.z_scn());
        else
            return sqrt(vector.x() * vector.x() + vector.y() * vector.y() + vector.z() * vector.z());

    }

    static Coordinates cross_product_3d(Coordinates v1, Coordinates v2, bool use_scn = false) {
        if (use_scn) {
            return Coordinates(v1.y_scn() * v2.z_scn() - v1.z_scn() * v2.y_scn(),
                               v1.z_scn() * v2.x_scn() - v1.x_scn() * v2.z_scn(),
                               v1.x_scn() * v2.y_scn() - v1.y_scn() * v2.x_scn());
        } else {
            return Coordinates(v1.y() * v2.z() - v1.z() * v2.y(),
                               v1.z() * v2.x() - v1.x() * v2.z(),
                               v1.x() * v2.y() - v1.y() * v2.x());
        }
    }

    static Coordinates
    intersection(Coordinates p0, Coordinates p1, Coordinates p2, Coordinates p3) {
        double p0_x = p0.x_scn();
        double p0_y = p0.y_scn();
        double p1_x = p1.x_scn();
        double p1_y = p1.y_scn();
        double p2_x = p2.x_scn();
        double p2_y = p2.y_scn();
        double p3_x = p3.x_scn();
        double p3_y = p3.y_scn();
        double s1_x, s1_y, s2_x, s2_y;
        s1_x = p1_x - p0_x;
        s1_y = p1_y - p0_y;
        s2_x = p3_x - p2_x;
        s2_y = p3_y - p2_y;
        double s, t;
        s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
        t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
            // Collision detected
            double x = p0_x + (t * s1_x);
            double y = p0_y + (t * s1_y);
            return Coordinates(x, y, 0);
        }
        cout << "The intersection returned a fucked up Coordinate" << endl;
        return Coordinates(-10000, -10000, 0);; // No collision
    }

    static void split(const std::string &s, char delim, std::vector<string> &elems) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
    }

    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }

    static void remove_char_from_string(string &str, char *charsToRemove) {
        for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
            str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
        }
    }

    template<typename T>
    static bool contains(vector<T> v, T x) {
        return (std::find(v.begin(), v.end(), x) != v.end());
    }

    static vector<Drawing_Edge> liang_barsky(double x1, double y1, double x2, double y2) {
        vector<Drawing_Edge> output;
        vector<double> ps;
        ps.push_back(-(x2 - x1));
        ps.push_back(x2 - x1);
        ps.push_back(-(y2 - y1));
        ps.push_back(y2 - y1);
        vector<double> qs;
        qs.push_back(x1 + 1);
        qs.push_back(1 - x1);
        qs.push_back(y1 + 1);
        qs.push_back(1 - y1);
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
                    Drawing_Edge(Coordinates(x1 + u1 * (x2 - x1), y1 + u1 * (y2 - y1), 0),
                                 Coordinates(x1 + u2 * (x2 - x1), y1 + u2 * (y2 - y1), 0)));
            return output;
        }
    }

};

#endif 


