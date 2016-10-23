#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
public:
    Color(double r, double g, double b, double a);

    ~Color();

    double r();

    double g();

    double b();

    double a();

private:
    double _r, _g, _b, _a;
};

#endif // COLOR_HPP