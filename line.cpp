#include "line.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

Line::Line(Coordinates p1,Coordinates p2, string name, Color* color)
{
	_points.push_back(p1);
	_points.push_back(p2);
	_scn_points.push_back(p1);
	_scn_points.push_back(p2);
	_name = name;	
	_color = color;
	_filled = false;
	_background_color = new Color(1, 1, 1, 1);
}
/* Cohen-Sutherland Clipping */
void Line::clip2(){
	vector<Coordinates> new_scn_points;
	Coordinates p1 = _scn_points[0];
	Coordinates p2 = _scn_points[1];
	const int INSIDE = 0; // 0000
	const int LEFT = 1;   // 0001
	const int RIGHT = 2;  // 0010
	const int BOTTOM = 4; // 0100
	const int TOP = 8;    // 1000
	/* Defining the region codes */
	/* Define RC = 0000 and go changing it with consecutie OR operations*/
	int RC1 = INSIDE;          
	if (p1.get_x() < -1)           
		RC1 = (RC1 | LEFT);
	else if (p1.get_x() > 1)      
		RC1 = (RC1 | RIGHT);
	if (p1.get_y() < -1)          
		RC1 = (RC1 | BOTTOM);
	else if (p1.get_y() > 1)      
		RC1 =  (RC1 | TOP);
	/* The same for for p2 */
	int RC2 = INSIDE; 
	if (p2.get_x() < -1)           
		RC2 = (RC2 | LEFT);
	else if (p2.get_x() > 1)      
		RC2 = (RC2 | RIGHT);
	if (p2.get_y() <-1)          
		RC2 = (RC2 | BOTTOM);
	else if (p2.get_y() > 1)      
		RC2 =  (RC2 | TOP);
	/* Checking whether the  line is fully visibile, invisble or partially visible*/
	if ((RC1 | RC2) == 0){ /* First, checking if the line is contained in the window(RC1=RC2=[0,0,0,0])*/
		return;/* If it is, all the points in the scn representation  are kept cause everything will be drawn*/
	}
	else if((RC1 & RC2) != 0){ /* Now, checking if the line completely out of the window(RC1^RC2 != [0,0,0,0]) */
		_scn_points.clear(); /* If it is, all scn points are removed cause nothing will be drawn*/
	}
	else{ /* If it is partially in/out*/
		double x, y;
		double m = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x()); 
		/* Checking if RC1 is out of the window*/
		if (RC1 != 0) { 
			if ((RC1 & TOP) != 0) {   /* point is above the clip rectangle */    
				x = p1.get_x() + 1/m * (1 - p1.get_y());
				y = 1;
				if (x > -1 && x < 1)
					new_scn_points.push_back(Coordinates(x,1));
			}
			if ((RC1 & BOTTOM) != 0) { /* point is below the clip rectangle */
				x = p1.get_x() + 1/m * (-1 - p1.get_y());
				if (x > -1 && x < 1)
					new_scn_points.push_back(Coordinates(x,-1));
			} 
			if ((RC1 & RIGHT) != 0) {  /* point is to the right of clip rectangle */
				y = m * (1 - p1.get_x()) + p1.get_y();
				if (y > -1 && y < 1)
					new_scn_points.push_back(Coordinates(1,y));
			} 
			if ((RC1 & LEFT) != 0) {  /* point is to the left of clip rectangle */
				y = m * (-1 - p1.get_x()) + p1.get_y();
				if (y > -1 && y < 1)
					new_scn_points.push_back(Coordinates(-1,y));
			}
		}
		else
			new_scn_points.push_back(p1);
		/* Checking if RC2 is out of the window*/
		if (RC2 != 0)
		{
			if ((RC2 & TOP) != 0) { /* point is above the clip rectangle */ 
				x = p2.get_x() + 1/m * (1 - p2.get_y());
				y = 1;
				if (x > -1 && x < 1)
					new_scn_points.push_back(Coordinates(x,y));
			} 
			if ((RC2 & BOTTOM) != 0) { /* point is below the clip rectangle */
				x = p2.get_x() + 1/m * (-1 - p2.get_y());
				y = -1;
				if (x > -1 && x < 1)
					new_scn_points.push_back(Coordinates(x,y));
			} 
			if ((RC2 & RIGHT) != 0) {/* point is to the right of clip rectangle */
				y = m * (1 - p2.get_x()) + p2.get_y();
				x = 1;
				if (y > -1 && y < 1)
					new_scn_points.push_back(Coordinates(x,y));
			} 
			if ((RC2 & LEFT) != 0) { /* point is to the left of clip rectangle */
				y = m * (-1 - p2.get_x()) + p2.get_y();
				x = -1;
				if (y > -1 && y < 1)
					new_scn_points.push_back(Coordinates(x,y));
			}
		}
		else
			new_scn_points.push_back(p2);
	}
	_scn_points = new_scn_points;
}
/* Liang-Barsky Clipping, no comments cause it works by magic */
void Line::clip(){
	Coordinates p1 = _scn_points[0];
	Coordinates p2 = _scn_points[1];
	vector<double> ps;
	ps.push_back( -(p2.get_x() - p1.get_x()) );
	ps.push_back(   p2.get_x() - p1.get_x() );
	ps.push_back( -(p2.get_y() - p1.get_y()) );
	ps.push_back(   p2.get_y() - p1.get_y() );
	vector<double> qs;
	qs.push_back( p1.get_x() + 1 );
	qs.push_back( 1 - p1.get_x() );
	qs.push_back( p1.get_y() + 1 );
	qs.push_back( 1 - p1.get_y() );
	vector<double> rs_less_than_zero, rs_more_than_zero;

	vector<double>::iterator it_ps;
	vector<double>::iterator it_qs;
	for(it_ps = ps.begin(), it_qs = qs.begin(); it_ps != ps.end(); it_ps++,it_qs++){
		double p = *(it_ps);
		double q = *(it_qs);
		if(p == 0 & q < 0)
		{
			_scn_points.clear();
			return;
		}
		else if(p < 0){
			rs_less_than_zero.push_back( q/p );
		}
		else if(p > 0)
		{
			rs_more_than_zero.push_back( q/p );
		}
	}
	double u1 = 0;
	vector<double>::iterator it;
	for(it = rs_less_than_zero.begin(); it != rs_less_than_zero.end(); it++){
		double r = *(it);
		u1 = max(u1,r);
	}	
	double u2 = 1;
	for(it = rs_more_than_zero.begin(); it != rs_more_than_zero.end(); it++){
		double r = *(it);
		u2 = min(u2,r);
	}
	if(u1 >  u2)
	{
		_scn_points.clear();
	}else{
		vector<Coordinates> new_scn_points;
		Coordinates new_p1 = 
		Coordinates(
			p1.get_x() + u1 * (p2.get_x() - p1.get_x()), 
			p1.get_y() + u1 * (p2.get_y() - p1.get_y())
			);
		Coordinates new_p2 = 
		Coordinates(
			p1.get_x() + u2 * (p2.get_x() - p1.get_x()), 
			p1.get_y() + u2 * (p2.get_y() - p1.get_y())
			);
		new_scn_points.push_back(new_p1);
		new_scn_points.push_back(new_p2);
		_scn_points = new_scn_points;
	}
}