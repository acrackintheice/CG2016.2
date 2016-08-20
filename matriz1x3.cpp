#include "matriz1x3.hpp"

Matriz1x3::Matriz1x3(double l1[])
{
    d1 = 1;
    d2 = 3;

    for(int i = 0; i <= 2 ; i++){
        this->M1[0][i] = l1[i];
    }
}

Matriz1x3* Matriz1x3::multiplicarPor3x3(Matriz3x3* M2){
    double l1[3];

    l1[0] = (M1[0][0] * M2->get(0,0)) + (M1[0][1] * M2->get(1,0)) + (M1[0][2] * M2->get(2,0));
    l1[1] = (M1[0][0] * M2->get(0,1)) + (M1[0][1] * M2->get(1,1)) + (M1[0][2] * M2->get(2,1));
    l1[2] = (M1[0][0] * M2->get(0,2)) + (M1[0][1] * M2->get(1,2)) + (M1[0][2] * M2->get(2,2));

    return new Matriz1x3(l1);
}
double Matriz1x3::get(int coluna){
    return M1[0][coluna];
}
