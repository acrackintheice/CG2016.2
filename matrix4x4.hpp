#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include <iostream>
#include "matrix4x1.hpp"

class Matrix4x4
{
public:
    Matrix4x4(double l1[], double l2[], double l3[],double l4[]);
    Matrix4x1 multiply4x1(Matrix4x1 M2);
    Matrix4x4 multiply4x4(Matrix4x4 M2);
    double get(int linha, int coluna);
    Matrix4x4 tranpose();
private:
    double M1[4][4];
};

#endif // MATRIZ4X4_HPP
