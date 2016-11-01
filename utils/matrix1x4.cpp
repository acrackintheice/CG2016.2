#include "matrix1x4.hpp"

using namespace std;

Matriz1x4::Matriz1x4(double _l1[])
{
    M1[0][0] = _l1[0];
    M1[0][1] = _l1[1];
    M1[0][2] = _l1[2];
    M1[0][3] = _l1[3];
}
Matriz1x4 Matriz1x4::multiplicarPor4x4(Matriz4x4 M2){
    double l1[4];
    l1[0] = (M1[0][0] * M2.get(0,0)) + (M1[0][1] * M2.get(1,0)) + (M1[0][2] * M2.get(2,0)) + (M1[0][3] * M2.get(3,0));
    l1[1] = (M1[0][0] * M2.get(0,1)) + (M1[0][1] * M2.get(1,1)) + (M1[0][2] * M2.get(2,1)) + (M1[0][3] * M2.get(3,1));
    l1[2] = (M1[0][0] * M2.get(0,2)) + (M1[0][1] * M2.get(1,2)) + (M1[0][2] * M2.get(2,2)) + (M1[0][3] * M2.get(3,2));
    l1[3] = (M1[0][0] * M2.get(0,3)) + (M1[0][1] * M2.get(1,3)) + (M1[0][2] * M2.get(2,3)) + (M1[0][3] * M2.get(3,3));
    return Matriz1x4(l1);
}
double Matriz1x4::multiplicarPor4x1(Matriz4x1 M2){
    return ((M1[0][0] * M2.get(0)) + (M1[0][1] * M2.get(1)) + (M1[0][2] * M2.get(2)) + (M1[0][3])* M2.get(3));
}
double Matriz1x4::get(int coluna){
    return M1[0][coluna];
}