#include "matriz3x3.hpp"

Matriz3x3::Matriz3x3(double l1[], double l2[], double l3[])
{
    for(int i = 0; i <= 2 ; i++){
        M1[0][i] = l1[i];
        M1[1][i] = l2[i];
        M1[2][i] = l3[i];
    }
}
Matriz3x3 Matriz3x3::multiplicarPor3x3(Matriz3x3 M2){
    double l1[3];
    double l2[3];
    double l3[3];

    l1[0] = (M1[0][0] * M2.get(0,0)) + (M1[0][1] * M2.get(1,0)) + (M1[0][2] * M2.get(2,0));
    l1[1] = (M1[0][0] * M2.get(0,1)) + (M1[0][1] * M2.get(1,1)) + (M1[0][2] * M2.get(2,1));
    l1[2] = (M1[0][0] * M2.get(0,2)) + (M1[0][1] * M2.get(1,2)) + (M1[0][2] * M2.get(2,2));

    l2[0] = (M1[1][0] * M2.get(0,0)) + (M1[1][1] * M2.get(1,0)) + (M1[1][2] * M2.get(2,0));
    l2[1] = (M1[1][0] * M2.get(0,1)) + (M1[1][1] * M2.get(1,1)) + (M1[1][2] * M2.get(2,1));
    l2[2] = (M1[1][0] * M2.get(0,2)) + (M1[1][1] * M2.get(1,2)) + (M1[1][2] * M2.get(2,2));

    l3[0] = (M1[2][0] * M2.get(0,0)) + (M1[2][1] * M2.get(1,0)) + (M1[2][2] * M2.get(2,0));
    l3[1] = (M1[2][0] * M2.get(0,1)) + (M1[2][1] * M2.get(1,1)) + (M1[2][2] * M2.get(2,1));
    l3[2] = (M1[2][0] * M2.get(0,2)) + (M1[2][1] * M2.get(1,2)) + (M1[2][2] * M2.get(2,2));

    return Matriz3x3(l1,l2,l3);
}
double Matriz3x3::get(int linha,int coluna){
    return M1[linha][coluna];
}
