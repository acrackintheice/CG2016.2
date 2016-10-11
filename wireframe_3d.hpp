#ifndef WIREFRAME_3d_HPP
#define WIREFRAME_3d_HPP

#include <string>
#include "coordinates_3d.hpp"
#include "object_3d.hpp"
#include "edge.hpp"
#include "facet.hpp"


class Wireframe_3d : public  Object_3d
{
public:
	Wireframe_3d(std::vector<Coordinates_3d*> points, std::vector<Edge*> edges, std::vector<Facet*> facets, std::string name);
	std::vector<Edge*> get_edges();
	std::vector<Facet*> get_facets();
	~Wireframe_3d();
private:
	std::vector<Edge*> _edges;
	std::vector<Facet*> _facets;
};

#endif 