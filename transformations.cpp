#include "coordinates_3d.hpp"

using namespace std;

class Transformations{

public:
	static Coordinates_3d viewport(Coordinates_3d* cw, Coordinates_3d window_min, Coordinates_3d window_max,Coordinates_3d vp_min, Coordinates_3d vp_max)
	{
		double xw     = cw->get_x_scn();
		double xwmin  = window_min.get_x();
		double xwmax  = window_max.get_x();
		double xvpmax = vp_max.get_x();
		double xvpmin = vp_min.get_x();

		double yw     = cw->get_y_scn();
		double ywmin  = window_min.get_y();
		double ywmax  = window_max.get_y();
		double yvpmax = vp_max.get_y();
		double yvpmin = vp_min.get_y();

		double xvp =      (((xw - xwmin) / (xwmax - xwmin))  * (xvpmax - xvpmin)) + xvpmin;
		double yvp =  ((1- ((yw - ywmin) / (ywmax - ywmin))) * (yvpmax - yvpmin)) + yvpmin;

		return Coordinates_3d(xvp, yvp, 0);
	}
};



