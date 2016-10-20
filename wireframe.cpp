#include "wireframe.hpp"

using namespace std;

Wireframe::Wireframe(vector<Coordinates_3d*> points, vector<Edge> edges, string name, Color* color,  Color* background_color, bool filled){
	_points = points;
	_edges = edges;
	_name = name;
	_color = color;
	_filled = filled;
	_background_color = background_color;
}
vector<Edge> Wireframe::clip(){
	vector<Edge> clip_edges;
	Coordinates_3d* P1_LEFT = new Coordinates_3d(-1,-10000,0);
	Coordinates_3d* P2_LEFT = new Coordinates_3d(-1,10000,0);
	clip_edges.push_back(Edge(P1_LEFT, P2_LEFT));
	Coordinates_3d* P1_RIGHT = new Coordinates_3d(1,-10000,0);
	Coordinates_3d* P2_RIGHT = new Coordinates_3d(1,1000,0);
	clip_edges.push_back(Edge(P1_RIGHT, P2_RIGHT));
	Coordinates_3d* P1_TOP = new Coordinates_3d(-10000,1,0);
	Coordinates_3d* P2_TOP = new Coordinates_3d(10000,1,0);
	clip_edges.push_back(Edge(P1_TOP, P2_TOP));
	Coordinates_3d* P1_BOTTOM = new Coordinates_3d(-10000,-1,0);
	Coordinates_3d* P2_BOTTOM = new Coordinates_3d(10000,-1,0);
	clip_edges.push_back(Edge(P1_BOTTOM, P2_BOTTOM));
	vector<Edge> in;
	vector<Edge> out = _edges;
	int x = 0;
	// For every edge of the window
	for (vector<Edge>::iterator i1 = clip_edges.begin(); i1 != clip_edges.end(); ++i1){
		string string_edge = "";
		Edge clip_edge = *i1;
		in = out;
		out.clear();
		if (fake_frame(in)){
			return sub_clip(in);
		}
		if(x==0){
			string_edge = "LEFT";
		}
		if(x==1){
			string_edge = "RIGHT";
		}
		if(x==2){
			string_edge = "TOP";
		}
		if(x==3) {
			string_edge = "BOTTOM";
		}
		x++;
		bool went_out = false;
		Coordinates_3d* out_buffer;
		// For every edge in the wireframe
		for (vector<Edge>::iterator i2 = in.begin(); i2 != in.end(); ++i2){
			Edge edge = *i2;
			Coordinates_3d* E = edge.get_p1();
			Coordinates_3d* S = edge.get_p2();

			// If( S inside EDGE )
			if(inside(S, string_edge)){ 
				// If( E inside EDGE )
				if(inside(E, string_edge)){ 
					out.push_back(Edge(new Coordinates_3d(E->get_x_scn(), E->get_y_scn(),0), new Coordinates_3d(S->get_x_scn(), S->get_y_scn(),0)));
				}
				// If( E outside EDGE )
				else{
					Coordinates_3d* new_E = Operations::intersection_between_lines_2(E, S, clip_edge.get_p1(), clip_edge.get_p2());
					if(went_out){
						out.push_back(Edge(out_buffer, new_E));
						went_out = false;
					}
					out.push_back(Edge(new_E, new Coordinates_3d(S->get_x_scn(), S->get_y_scn(),0)));
				}
			}
			// If(S outside EDGE )
			else{
				// IF ( E inside EDGE ) 
				if(inside(E, string_edge)){ 
					Coordinates_3d* new_S = Operations::intersection_between_lines_2(E, S, clip_edge.get_p1(), clip_edge.get_p2());
					out.push_back(Edge(new Coordinates_3d(E->get_x_scn(), E->get_y_scn(),0), new_S));
					out_buffer = new_S;
					went_out = true;
				}
				else{
					
				}
			}
		}
		/* Deleting the objects created to represent the clipping edges */
		delete clip_edge.get_p1();
		delete clip_edge.get_p2();
	}
	if (fake_frame(in)){
		return sub_clip(in);
	}
	return out;
}

bool Wireframe::inside(Coordinates_3d* point, string edge){
	if(edge == "LEFT"){
		if(point->get_x_scn() < -1)
			return false;
		else 
			return true;
	}
	else if(edge == "RIGHT"){
		if(point->get_x_scn() > 1)
			return false;
		else 
			return true;
	}
	else if(edge == "TOP"){
		if(point->get_y_scn() > 1)
			return false;
		else 
			return true;
	}
	else if(edge == "BOTTOM") {
		if(point->get_y_scn() < -1)
			return false;
		else 
			return true;
	}
	else
		return false;
}
vector<Edge> Wireframe::sub_clip(std::vector<Edge> in){
	vector<Edge> output;
	if(in.size() == 1){
		Coordinates_3d* p1 = in[0].get_p1();
		Coordinates_3d* p2 = in[0].get_p2();
		Line l = Line(new Coordinates_3d(p1->get_x_scn(), p1->get_y_scn(),0), new Coordinates_3d(p2->get_x_scn(), p2->get_y_scn(),0),"",new Color(1,1,1,1));
		output = l.clip2();
	}
	return output;
}
bool Wireframe::fake_frame(std::vector<Edge> in){
	if(in.size() < 2)
		return true;
	else
		return false;
}