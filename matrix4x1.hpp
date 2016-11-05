#ifndef MATRIX4X1_HPP
#define MATRIX4X1_HPP

class Matrix4x1
{
public:
    Matrix4x1(double l1,double l2, double l3, double l4);
    double get(int linha);
private:
    double M1[4][1];
};

#endif // MATRIZ4X1_HPP
