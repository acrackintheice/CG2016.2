#include "matriz4x1.hpp"

Matriz4x1::Matriz4x1(double l1, double l2, double l3, double l4)
{
    this->M1[0][0] = l1;
    this->M1[1][0] = l2;
    this->M1[2][0] = l3;
    this->M1[3][0] = l4;
}
double Matriz4x1::get(int linha){
    return M1[linha][0];
}
