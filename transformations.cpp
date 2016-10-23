#include "coordinates.hpp"

using namespace std;

class Transformations{

public:
	static Coordinates viewport(Coordinates cw, Coordinates window_min, Coordinates window_max,Coordinates vp_min, Coordinates vp_max)
	{
		double xw     = cw.x_scn();
		double xwmin  = window_min.x();
		double xwmax  = window_max.x();
		double xvpmax = vp_max.x();
		double xvpmin = vp_min.x();

		double yw     = cw.y_scn();
		double ywmin  = window_min.y();
		double ywmax  = window_max.y();
		double yvpmax = vp_max.y();
		double yvpmin = vp_min.y();

		double xvp =      (((xw - xwmin) / (xwmax - xwmin))  * (xvpmax - xvpmin)) + xvpmin;
		double yvp =  ((1- ((yw - ywmin) / (ywmax - ywmin))) * (yvpmax - yvpmin)) + yvpmin;

		return Coordinates(xvp, yvp, 0);
	}
};



