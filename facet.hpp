#ifndef FACET_HPP
#define FACET_HPP

#include <string>
#include "edge.hpp"
#include <vector>

class Facet
{
public:
    Facet(std::vector<Edge*> edges);
    std::vector<Edge*> get_edges();
    ~Facet();
    std::string to_string();
private:
	std::vector<Edge*> _edges;
};

#endif 