#ifndef COR_HHPP
#define COr_HPP

class Cor
{
public:
    Cor(double r, double g, double b, double a);
    ~Cor();
    double get_r();
    double get_g();
    double get_b();
    double get_a();
private:
	double _r,_g,_b,_a;    
};

#endif // COR_HPP