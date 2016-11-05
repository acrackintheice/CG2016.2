#ifndef MATRIX1X4_HPP
#define MATRIX1X4_HPP

#include <iostream>
#include "matrix4x4.hpp"
#include "matrix4x1.hpp"

class Matrix1x4
{
public:
    Matrix1x4(double _linha[]);
    Matrix1x4 multiply4x4(Matrix4x4 M2);
    double multiplyPor4x1(Matrix4x1 M2);
    double get(int coluna);
private:
    double M1[1][4];
};

#endif // MATRIZ1X4_HPP
