#include "facet.hpp"

Facet::Facet(std::vector<Edge*> edges){
	_edges = edges;
}

Facet::~Facet(){
}

std::vector<Edge*> Facet::get_edges(){
    return _edges;
}

std::string Facet::to_string(){
	return "Kappa";
}