#ifndef MATRIZ1X4_HPP
#define MATRIZ1X4_HPP

#include <iostream>
#include "matriz4x4.hpp"
#include "matrix4x1.hpp"

class Matriz1x4
{
public:
    Matriz1x4(double _linha[]);
    Matriz1x4 multiplicarPor4x4(Matriz4x4 M2);
    double multiplicarPor4x1(Matriz4x1 M2);
    double get(int coluna);
    void print();
private:
    double M1[1][4];
};

#endif // MATRIZ1X4_HPP
