#ifndef MATRIZ4X1_HPP
#define MATRIZ4X1_HPP

class Matriz4x1
{
public:
    Matriz4x1(double l1,double l2, double l3, double l4);
    double get(int linha);
private:
    double M1[4][1];
};

#endif // MATRIZ4X1_HPP
