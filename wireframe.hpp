#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP

#include "coordinates.hpp"
#include "object.hpp"
#include <vector>
#include <string>

class Wireframe : public Object
{
public:
    Wireframe(std::vector<Coordinates> pontos, std::string name, Color* color);
    ~Wireframe();
};

#endif // WIREFRAME_HPP