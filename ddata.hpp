#ifndef DDATA_HPP
#define DDATA_HPP

#include "objeto.hpp"
#include "window.hpp"

class D_Data
{
public:
    D_Data(Objeto* obj, Window* window){_obj = obj; _window = window;}
    ~D_Data();
	Window* _window;
    Objeto* _obj;
};

#endif // D_DATA_HPP