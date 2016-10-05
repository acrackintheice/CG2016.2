#ifndef MATRIZ4X4_HPP
#define MATRIZ4X4_HPP

#include "matriz4x1.hpp"

class Matriz4x4
{
public:
    Matriz4x4(double l1[], double l2[], double l3[],double l4[]);
    Matriz4x1 multiplicar4x1(Matriz4x1 M2);
    double get(int linha, int coluna);
private:
    double M1[4][4];
};

#endif // MATRIZ4X4_HPP
