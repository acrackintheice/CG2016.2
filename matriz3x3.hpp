#ifndef Matriz3x3_HPP
#define Matriz3x3_HPP

class Matriz3x3
{
public:
    Matriz3x3(double l1[], double l2[], double l3[]);
    Matriz3x3 multiplicarPor3x3(Matriz3x3 M2);
    double get(int linha, int coluna);
private:
    double M1[3][3];
};

#endif // Matriz3x3_HPP