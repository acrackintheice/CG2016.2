#include "edge.hpp"

Edge::Edge(Coordinates *p1, Coordinates *p2) {
    _p1 = p1;
    _p2 = p2;
}

Edge::~Edge() {
}

Coordinates *Edge::p1() {
    return _p1;
}

Coordinates *Edge::p2() {
    return _p2;
}

std::string Edge::to_string() {
    return "(" + _p1->to_string() + " ----> " + _p2->to_string() + ")";
}

void Edge::set_p1(Coordinates *_p1) {
    Edge::_p1 = _p1;
}

void Edge::set_p2(Coordinates *_p2) {
    Edge::_p2 = _p2;
}
