#include "matrix4x1.hpp"

Matriz4x1::Matriz4x1(double l1, double l2, double l3, double l4)
{
    M1[0][0] = l1;
    M1[1][0] = l2;
    M1[2][0] = l3;
    M1[3][0] = l4;
}
double Matriz4x1::get(int linha){
    return M1[linha][0];
}
