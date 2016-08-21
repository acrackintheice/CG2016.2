#ifndef COLOR_HHPP
#define COLOR_HPP

class Color
{
public:
    Color(double r, double g, double b, double a);
    ~Color();
    double get_r();
    double get_g();
    double get_b();
    double get_a();
private:
	double _r,_g,_b,_a;    
};

#endif // COLOR_HPP