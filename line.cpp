#include "line.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

Line::Line(Coordinates p1,Coordinates p2, string name)
{
	_points.push_back(p1);
	_points.push_back(p2);
	_name = name;
}
Line::~Line(){
}

/* Clipping Liang-Barsky*/
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
		cout << "kappa 2" << endl;
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