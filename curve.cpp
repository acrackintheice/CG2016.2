#include "curve.hpp"
#include "matriz4x4.hpp"
#include "matriz4x1.hpp"
#include "matriz1x4.hpp"

using namespace std;

Curve::Curve(vector<Coordinates> points, string name, Color* color){
	_points = points;
	_scn_points = points;
	_name = name;
	_color = color;
	_filled = false;
	_background_color = new Color(1, 1, 1, 1);
}
Curve::~Curve(){
}

void Curve::clip(){
	/* O clipping não ocorre aqui pois ainda não sabemos os pontos que serão desenhados */
}
/* The points to be drawn will be defined using the blending functions method*/
std::vector<Coordinates> Curve::get_drawing_points(){
	vector<Coordinates> drawing_points;
	std::vector<Coordinates>::iterator it = _scn_points.begin();
	double step = 0.001; 
	/* Creating the Bezier matrix */
	double l1MB[] = {-1,  3, -3,  1};
	double l2MB[] = { 3, -6,  3,  0};
	double l3MB[] = {-3,  3,  0,  0};
	double l4MB[] = { 1,  0,  0,  0};
	Matriz4x4 MB = Matriz4x4(l1MB,l2MB,l3MB,l4MB);

	if(_scn_points.size()-1 % 3){
		for( int i = 0; i < _scn_points.size()-1; i = i+3){
			Matriz4x1 Gx = Matriz4x1((*it).get_x(), (*(it+1)).get_x(), (*(it+2)).get_x(), (*(it+3)).get_x());
			Matriz4x1 Gy = Matriz4x1((*it).get_y(), (*(it+1)).get_y(), (*(it+2)).get_y(), (*(it+3)).get_y());
			for(double t = 0; t<=1;t = t+step )
			{
				double l1T[] = {(t*t*t),(t*t),t,1};
				Matriz1x4 T  = Matriz1x4(l1T);
				Matriz1x4 TMB = T.multiplicarPor4x4(MB);
				double x = TMB.multiplicarPor4x1(Gx);
				double y = TMB.multiplicarPor4x1(Gy);
				drawing_points.push_back(Coordinates(x,y));
			}
		it = it+3;
		}
	}
	/*
		Implementar o clipping aqui
	*/
	return drawing_points;
}