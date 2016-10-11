#include "bspline.hpp"
#include <iostream>
#include "line.hpp"

using namespace std;

BSpline::BSpline(std::vector<Coordinates> points, std::string name, Color* color){
	_points = points;
	_scn_points = points;
	_name = name;
	_color = color;
	_filled = false;
	_background_color = new Color(1, 1, 1, 1);
}
void BSpline::clip(){
}
/* The points to be drawn will be defined using the forward differences method*/
std::vector<Coordinates> BSpline::get_drawing_points(){
	std::vector<Coordinates> drawing_points;
	std::vector<Coordinates>::iterator it = _scn_points.begin();
    // 0 - Calculating the deltas.
	double deltao  = 0.001;
	double deltao2 = deltao*deltao;
	double deltao3 = deltao2 * deltao;
	double l1e[] = { 0, 0, 0, 1};
	double l2e[] = { deltao3, deltao2, deltao, 0};
	double l3e[] = { 6*deltao3, 2*deltao2, 0, 0};
	double l4e[] = { 6*deltao3, 0, 0, 0};
	Matriz4x4 e = Matriz4x4(l1e,l2e,l3e,l4e);
	/* 1 - Calculating C =  mbs * Gbs */
	/* Creating the B-Spline matrix in order to calculate the Cs */
	double l1mbs[] = { -1.0/6.0,  3.0/6.0, -3.0/6.0, 1.0/6.0};
	double l2mbs[] = {  3.0/6.0, -6.0/6.0,  3.0/6.0, 0      };
	double l3mbs[] = { -3.0/6.0,        0,  3.0/6.0, 0      };
	double l4mbs[] = {  1.0/6.0,  4.0/6.0,  1.0/6.0, 0      };
	Matriz4x4 mbs = Matriz4x4(l1mbs,l2mbs,l3mbs,l4mbs);
	/* Now for each curve */
	for (int i = 3; i < _scn_points.size(); i++,it++){
		/* Creating the Geometric matrixes in order to calculate the Cs */
		Matriz4x1 gx = Matriz4x1((*it).get_x(),(*(it+1)).get_x(), (*(it+2)).get_x(), (*(it+3)).get_x());
		Matriz4x1 gy = Matriz4x1((*it).get_y(),(*(it+1)).get_y(), (*(it+2)).get_y(), (*(it+3)).get_y());
		/* Calculating the Cs */
		Matriz4x1 Cx =  mbs.multiplicar4x1(gx);
		Matriz4x1 Cy =  mbs.multiplicar4x1(gy);
    	/* 2 - Calculating f0, delta(f0), delta²(f0) e delta³(f0) based on the first point of the bspline */
		Matriz4x1 dx = e.multiplicar4x1(Cx);
		Matriz4x1 dy = e.multiplicar4x1(Cy);
    	/* 3 - Calculating the points with desenharCurvaFwdDiff(...) from the slides */
		std::vector<Coordinates> some_points = getFwdDiffPoints(1/deltao,dx,dy);
		drawing_points.insert(drawing_points.end(), some_points.begin(), some_points.end());
	}
	/*  Clipping  */

	if(too_far_away(drawing_points[0]))
		drawing_points.clear();
	else {
		std::vector<Coordinates> new_drawing_points;
		it = drawing_points.begin();
		for (int i = 0; i < drawing_points.size()-2; ++i,it++){
			Coordinates c1 = *(it);
			Coordinates c2 = *(it+1);
			Line l = Line(c1,c2,"",new Color(1,1,1,1));
			l.clip();
			std::vector<Coordinates> clipped_points = l.get_scn_points();
			new_drawing_points.insert(new_drawing_points.end(), clipped_points.begin(), clipped_points.end());
		}
		drawing_points = new_drawing_points;
	}
	return drawing_points;
}

std::vector<Coordinates> BSpline::getFwdDiffPoints(double n, Matriz4x1 dx, Matriz4x1 dy){
	double x       = dx.get(0);
	double deltaX  = dx.get(1)	;
	double delta2X = dx.get(2);
	double delta3X = dx.get(3);

	double y       = dy.get(0);
	double deltaY  = dy.get(1);
	double delta2Y = dy.get(2);
	double delta3Y = dy.get(3);

	std::vector<Coordinates> some_points;
	for (int i = 0; i < n; ++i){
		x       = x + deltaX;
		deltaX  = deltaX + delta2X;
		delta2X = delta2X + delta3X;
		y       = y + deltaY;
		deltaY  = deltaY  + delta2Y;
		delta2Y = delta2Y + delta3Y;
		some_points.push_back(Coordinates(x,y));
	}
	return some_points;
}
bool BSpline::too_far_away(Coordinates c){
	if (c.get_x() < -10 || c.get_x() > 10 || c.get_y() > 10 || c.get_y() > 10 )
		return true;
	else
		return false;
}
bool BSpline::is_inside(Coordinates c){
	if (c.get_x() < 1 && c.get_x() >-1 && c.get_y() > -1 && c.get_y() < 1 )
		return true;
	else
		return false;
}
