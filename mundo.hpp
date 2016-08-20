#ifndef MUNDO_HPP
#define MUNDO_HPP

#include <vector>
#include <string>
#include "objeto.hpp"
#include "window.hpp"

class Mundo
{
public:
    Mundo(Window* window);
    ~Mundo();
    void add_object(Objeto* obj);
    void remove_object(std::string name);
    Objeto* get_object(std::string name);
    void move_window(double x1_offset, double y1_offset, double x2_offset, double y2_offset);
    std::vector<Objeto*> get_objects();
    Window* get_window();
private:
	Window* _window;
    std::vector<Objeto*> _objetos;
};

#endif // MUNDO_HPP