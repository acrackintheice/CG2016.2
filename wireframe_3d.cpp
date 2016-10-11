#include "wireframe_3d.hpp"

using namespace std;


Wireframe_3d::Wireframe_3d(vector<Coordinates_3d*> points,vector<Edge*> edges, vector<Facet*> facets, string name){
	_points = points;
	_edges = edges;
	_facets = facets;
	_name = name;
}

Wireframe_3d::~Wireframe_3d(){
/*
	Need to delete some things now
*/
}
vector<Edge*> Wireframe_3d::get_edges(){
	return _edges;
}
vector<Facet*> Wireframe_3d::get_facets(){
	return _facets;
}