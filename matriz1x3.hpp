#ifndef MATRIZ1X3_HPP
#define MATRIZ1X3_HPP
#include "matriz3x3.hpp"

class Matriz1x3
{
public:
    Matriz1x3(double l1[]);
    Matriz1x3 *multiplicarPor3x3(Matriz3x3* M2);
    double get(int coluna);
private:
    double M1[1][3];
    int d1;
    int d2;
};

#endif // MATRIZ1X3_HPP
