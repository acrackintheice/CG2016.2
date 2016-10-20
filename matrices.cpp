#ifndef MATRICES_CPP
#define MATRICES_CPP

#include "math.h"
#include "matriz4x4.hpp"

using namespace std;

class Matrices{

public:
	static Matriz4x4 generate_translation_matrix(double dx, double dy, double dz)
	{
		double l0[] = { 1,  0, 0, 0};
		double l1[] = { 0,  1, 0, 0};
		double l2[] = { 0,  0, 1, 0};
		double l3[] = {dx, dy, dz, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_scaling_matrix(double sx,double  sy,double  sz,double  cx,double  cy,double  cz)
	{
		double l0[] = {sx,              0,               0,               0};
		double l1[] = {0,               sy,              0,               0};
		double l2[] = {0,               0,               sz,              0};
		double l3[] = {(-cx * sx) + cx, (-cy * sy) + cy, (-cz * sz) + cz, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_rotate_x_matrix(double angle)
	{
		double l0[] = {1,		   0,		   0, 0};
		double l1[] = {0, cos(angle), sin(angle), 0};
		double l2[] = {0,-sin(angle), cos(angle), 1};
		double l3[] = {0,0,0,1};
	}
	static Matriz4x4 generate_rotate_y_matrix(double angle)
	{
		double l0[] = {cos(angle), 0, -sin(angle), 0};
		double l1[] = {0,1,0,0};
		double l2[] = {sin(angle), 0,  cos(angle), 0};
		double l3[] = {0,0,0,1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_rotate_z_matrix(double angle)
	{
		double l0[] = {cos(angle), 0, sin(angle), 0};
		double l1[] = {-sin(angle),cos(angle), 0, 0};
		double l2[] = {0, 0, 1, 0};
		double l3[] = {0, 0, 0, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_tr(double x, double y, double z)
	{
		double l0[] = {1,0,0,-x};
		double l1[] = {0,1,0,-y};
		double l2[] = {0,0,1,-z};
		double l3[] = {0,0,0, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_ra(double b, double c, double d)
	{
		double l0[] = {1,0,0,0};
		double l1[] = {0, c/d, -b/d, 0};
		double l2[] = {0, b/d,  c/d, 0};
		double l3[] = {0,0,0,1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_rb(double a, double d)
	{
		double l0[] = { d, 0, -a, 0};
		double l1[] = { 0, 1,  0, 0};
		double l2[] = { a, 0,  d, 0};
		double l3[] = { 0, 0,  0, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_r(double cos_x, double sin_x)
	{
		double l0[] = {cos_x, -sin_x, 0, 0};
		double l1[] = {sin_x,  cos_x, 0, 0};
		double l2[] = {    0,      0, 1, 0};
		double l3[] = {    0,      0, 0, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_ra_inv(double b, double c, double d)
	{
		double l0[] = {1,0,0,0};
		double l1[] = {0,  c/d, b/d, 0};
		double l2[] = {0, -b/d, c/d, 0};
		double l3[] = {0,0,0,1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_rb_inv(double a, double d)
	{
		double l0[] = { d, 0,  a, 0};
		double l1[] = { 0, 1,  0, 0};
		double l2[] = {-a, 0,  d, 0};
		double l3[] = { 0, 0,  0, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_tr_inv(double x, double y, double z)
	{
		double l0[] = {1,0,0, x};
		double l1[] = {0,1,0, y};
		double l2[] = {0,0,1, z};
		double l3[] = {0,0,0, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
	static Matriz4x4 generate_rotation_matrix(double a, double b, double c, double d, double o,double x, double y, double z)
	{
		double l0_0 = a*a+d*d*cos(o);
		double l0_1 = (b*(a*d-a*d*cos(o)))/d-c*sin(o);
		double l0_2 = (c*(a*d-a*d*cos(o)))/d+b*sin(o);
		double l0_3 = x-x*(a*a+d*d*cos(o))-z*((c*(a*d-a*d*cos(o)))/d+b*sin(o))-y*((b*(a*d-a*d*cos(o)))/d-c*sin(o));

		double l1_0 = a*b+d*(-((a*b*cos(o))/d)+(c*sin(o))/d);
		double l1_1 = (c*((c*cos(o))/d+(a*b*sin(o))/d))/d+(b*(b*d-a*(-((a*b*cos(o))/d)+(c*sin(o))/d)))/d;
		double l1_2 = -((b*((c*cos(o))/d + (a*b*sin(o))/d))/d) + (c*(b*d - a*(-((a*b*cos(o))/d) + (c*sin(o))/d)))/d;
		double l1_3 = y-x*(a*b+d*(-((a*b*cos(o))/d)+(c*sin(o))/d))- y*((c*((c*cos(o))/d+(a*b*sin(o))/d))/d+ 
			(b*(b*d-a*(-((a*b*cos(o))/d)+(c*sin(o))/d)))/d)-z*(-((b*((c*cos(o))/d+(a*b*sin(o))/d))/d)+(c*(b*d-a*(-((a*b*cos(o))/d)+(c*sin(o))/d)))/d);

		double l2_0 = a*c+d*(-((a*c*cos(o))/d)-(b*sin(o))/d);
		double l2_1 =  (c*(-((b*cos(o))/d)+(a*c*sin(o))/d))/d+(b*(c*d-a*(-((a*c*cos(o))/d)-(b*sin(o))/d)))/d;
		double l2_2 = -((b*(-((b*cos(o))/d)+(a*c*sin(o))/d))/d)+(c*(c*d-a*(-((a*c*cos(o))/d)-(b*sin(o))/d)))/d;
		double l2_3 = z-x*(a*c+d*(-((a*c*cos(o))/d)-(b*sin(o))/d))-y*((c*(-((b*cos(o))/d)+(a*c*sin(o))/d))/d+
			(b*(c*d-a*(-((a*c*cos(o))/d)-(b*sin(o))/d)))/d)-z*(-((b*(-((b*cos(o))/d)+(a*c*sin(o))/d))/d) +(c*(c*d-a*(-((a*c*cos(o))/d)-(b*sin(o))/d)))/d);

		double l0[] = {l0_0,l0_1,l0_2, l0_3};
		double l1[] = {l1_0,l1_1,l1_2, l1_3};
		double l2[] = {l2_0,l2_1,l2_2, l2_3};
		double l3[] = {0,0,0, 1};
		return Matriz4x4(l0,l1,l2,l3);
	}
};

#endif 


