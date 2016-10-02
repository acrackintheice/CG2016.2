#include "matriz4x4.hpp"

Matriz4x4::Matriz4x4(double l1[], double l2[], double l3[], double l4[])
{
    for(int i = 0; i <= 3 ; i++){
        this->M1[0][i] = l1[i];
        this->M1[1][i] = l2[i];
        this->M1[2][i] = l3[i];
        this->M1[3][i] = l4[i];
    }
}
double Matriz4x4::get(int linha,int coluna){
    return M1[linha][coluna];
}
Matriz4x1* Matriz4x4::multiplicar4x1(Matriz4x1 *M2){
    double l1 = (M1[0][0] * M2->get(0)) + (M1[0][1] * M2->get(1)) + (M1[0][2] * M2->get(2)) + (M1[0][3] * M2->get(3));
    double l2 = (M1[1][0] * M2->get(0)) + (M1[1][1] * M2->get(1)) + (M1[1][2] * M2->get(2)) + (M1[1][3] * M2->get(3));
    double l3 = (M1[2][0] * M2->get(0)) + (M1[2][1] * M2->get(1)) + (M1[2][2] * M2->get(2)) + (M1[2][3] * M2->get(3));
    double l4 = (M1[3][0] * M2->get(0)) + (M1[3][1] * M2->get(1)) + (M1[3][2] * M2->get(2)) + (M1[3][3] * M2->get(3));

    return new Matriz4x1(l1,l2,l3,l4);
}
