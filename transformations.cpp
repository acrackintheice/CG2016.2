#include "coordenadas.hpp"

class Transformations{

	public:
		static Coordenadas* viewport(Coordenadas* cw,Coordenadas* window_min, Coordenadas* window_max,Coordenadas* vp_min, Coordenadas* vp_max)
	{
		double xw     = cw->get_x();
		double xwmin  = window_min->get_x();
		double xwmax  = window_max->get_x();
		double xvpmax = vp_max->get_x();
		double xvpmin = vp_min->get_x();

		double yw     = cw->get_y();
		double ywmin  = window_min->get_y();
		double ywmax  = window_max->get_y();
		double yvpmax = vp_max->get_y();
		double yvpmin = vp_min->get_y();

		double xvp =      (((xw - xwmin) / (xwmax - xwmin))  * (xvpmax - xvpmin));
		double yvp =  ((1- ((yw - ywmin) / (ywmax - ywmin))) * (yvpmax - yvpmin));

		return new Coordenadas(xvp, yvp);
	}
};


