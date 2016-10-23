#include "matriz4x4.hpp"

using namespace std;

Matriz4x4::Matriz4x4(double l1[], double l2[], double l3[], double l4[])
{
    for(int i = 0; i <= 3 ; i++){
        M1[0][i] = l1[i];
        M1[1][i] = l2[i];
        M1[2][i] = l3[i];
        M1[3][i] = l4[i];
    }
}
double Matriz4x4::get(int linha,int coluna){
    return M1[linha][coluna];
}
Matriz4x1 Matriz4x4::multiplicar4x1(Matriz4x1 M2){
    double l1 = (M1[0][0] * M2.get(0)) + (M1[0][1] * M2.get(1)) + (M1[0][2] * M2.get(2)) + (M1[0][3] * M2.get(3));
    double l2 = (M1[1][0] * M2.get(0)) + (M1[1][1] * M2.get(1)) + (M1[1][2] * M2.get(2)) + (M1[1][3] * M2.get(3));
    double l3 = (M1[2][0] * M2.get(0)) + (M1[2][1] * M2.get(1)) + (M1[2][2] * M2.get(2)) + (M1[2][3] * M2.get(3));
    double l4 = (M1[3][0] * M2.get(0)) + (M1[3][1] * M2.get(1)) + (M1[3][2] * M2.get(2)) + (M1[3][3] * M2.get(3));

    return Matriz4x1(l1,l2,l3,l4);
}
Matriz4x4 Matriz4x4::multiplicarPor4x4(Matriz4x4 M2){
    double l1[4];
    double l2[4];
    double l3[4];
    double l4[4];

    l1[0] = (M1[0][0] * M2.get(0,0)) + (M1[0][1] * M2.get(1,0)) + (M1[0][2] * M2.get(2,0)) + (M1[0][3] * M2.get(3,0));
    l1[1] = (M1[0][0] * M2.get(0,1)) + (M1[0][1] * M2.get(1,1)) + (M1[0][2] * M2.get(2,1)) + (M1[0][3] * M2.get(3,1));
    l1[2] = (M1[0][0] * M2.get(0,2)) + (M1[0][1] * M2.get(1,2)) + (M1[0][2] * M2.get(2,2)) + (M1[0][3] * M2.get(3,2));
    l1[3] = (M1[0][0] * M2.get(0,3)) + (M1[0][1] * M2.get(1,3)) + (M1[0][2] * M2.get(2,3)) + (M1[0][3] * M2.get(3,3));

    l2[0] = (M1[1][0] * M2.get(0,0)) + (M1[1][1] * M2.get(1,0)) + (M1[1][2] * M2.get(2,0)) + (M1[1][3] * M2.get(3,0));
    l2[1] = (M1[1][0] * M2.get(0,1)) + (M1[1][1] * M2.get(1,1)) + (M1[1][2] * M2.get(2,1)) + (M1[1][3] * M2.get(3,1));
    l2[2] = (M1[1][0] * M2.get(0,2)) + (M1[1][1] * M2.get(1,2)) + (M1[1][2] * M2.get(2,2)) + (M1[1][3] * M2.get(3,2));
    l2[3] = (M1[1][0] * M2.get(0,3)) + (M1[1][1] * M2.get(1,3)) + (M1[1][2] * M2.get(2,3)) + (M1[1][3] * M2.get(3,3));

    l3[0] = (M1[2][0] * M2.get(0,0)) + (M1[2][1] * M2.get(1,0)) + (M1[2][2] * M2.get(2,0)) + (M1[2][3] * M2.get(3,0));
    l3[1] = (M1[2][0] * M2.get(0,1)) + (M1[2][1] * M2.get(1,1)) + (M1[2][2] * M2.get(2,1)) + (M1[2][3] * M2.get(3,1));
    l3[2] = (M1[2][0] * M2.get(0,2)) + (M1[2][1] * M2.get(1,2)) + (M1[2][2] * M2.get(2,2)) + (M1[2][3] * M2.get(3,2));
    l3[3] = (M1[2][0] * M2.get(0,3)) + (M1[2][1] * M2.get(1,3)) + (M1[2][2] * M2.get(2,3)) + (M1[2][3] * M2.get(3,3));

    l4[0] = (M1[3][0] * M2.get(0,0)) + (M1[3][1] * M2.get(1,0)) + (M1[3][2] * M2.get(2,0)) + (M1[3][3] * M2.get(3,0));
    l4[1] = (M1[3][0] * M2.get(0,1)) + (M1[3][1] * M2.get(1,1)) + (M1[3][2] * M2.get(2,1)) + (M1[3][3] * M2.get(3,1));
    l4[2] = (M1[3][0] * M2.get(0,2)) + (M1[3][1] * M2.get(1,2)) + (M1[3][2] * M2.get(2,2)) + (M1[3][3] * M2.get(3,2));
    l4[3] = (M1[3][0] * M2.get(0,3)) + (M1[3][1] * M2.get(1,3)) + (M1[3][2] * M2.get(2,3)) + (M1[3][3] * M2.get(3,3));

    return Matriz4x4(l1,l2,l3,l4);
}
