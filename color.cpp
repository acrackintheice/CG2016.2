#include "color.hpp"

Color::Color(double r, double g, double b, double a) {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

Color::~Color() {}

double Color::r() {
    return _r;
}

double Color::g() {
    return _g;
}

double Color::b() {
    return _b;
}

double Color::a() {
    return _a;
}
