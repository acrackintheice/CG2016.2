#include "drawing_edge.hpp"

Drawing_Edge::Drawing_Edge(Coordinates p1, Coordinates p2) : _p1(p1), _p2(p2) {
}

Drawing_Edge::~Drawing_Edge() {
}

Coordinates Drawing_Edge::p1() {
    return _p1;
}

Coordinates Drawing_Edge::p2() {
    return _p2;
}

std::string Drawing_Edge::to_string() {
    return "(" + _p1.to_string() + " ----> " + _p2.to_string() + ")";
}

void Drawing_Edge::set_p1(Coordinates _p1) {
    Drawing_Edge::_p1 = _p1;
}

void Drawing_Edge::set_p2(Coordinates _p2) {
    Drawing_Edge::_p2 = _p2;
}