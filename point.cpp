#include "point.hpp"

using namespace std;

Point::Point(Coordinates* xy, string name, Color* color)
{
	_points.push_back(xy);
	_edges.push_back(Edge(xy,xy));
	_name = name;
	_color = color;
	_filled = false;
	_background_color = new Color(1, 1, 1, 1);
}
vector<Edge> Point::clip()
{
	vector<Edge> output;
	double x = _points[0]->x_scn();
	double y = _points[0]->y_scn();

	if(x < -1 || x > 1 || y < -1 || y > 1)
	{
		return output;
	}
	else
	{
		output.push_back(Edge(new Coordinates(x,y,0), new Coordinates(x,y,0)));
	}
}