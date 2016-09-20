#include "polygon.hpp"
#include "operations.cpp"
#include <iostream>

using namespace std;

Polygon::Polygon(vector<Coordinates> points, string name, Color* color, Color* background_color, bool filled){
	_points = points;
	_name = name;
	_scn_points = _points;
	_color = color;
	_background_color = _background_color;
	_filled = filled;
}
Polygon::~Polygon(){
}
std::vector<Coordinates> Polygon::get_drawing_points(){
	vector<Coordinates> drawing_points = _scn_points;
	Coordinates first_point = _scn_points[0];
	drawing_points.push_back(first_point);
	return drawing_points;
}
/* Sutherland-Hodgeman */
void Polygon::clip(){
	vector<Coordinates> input = _scn_points;
	vector<Coordinates> output;
	if(input.size() == 0){
		_scn_points.clear();
		return;
	}
	input.push_back(input[0]);
    // Clipping Left
	vector<Coordinates>::iterator it;
	for(it = input.begin(); it != input.end()-1; it++){
		Coordinates c1 = *(it);
		Coordinates c2 = *(it+1);
        // Out -> In
		if(c1.get_x() < -1 && c2.get_x() >= -1){
			output.push_back(Operations::intersection_between_lines(c1,c2,Coordinates(-1,-1), Coordinates(-1,1)));
			output.push_back(c2);
		}
        // Out -> Out
		else if(c1.get_x() < -1 && c2.get_x() < -1){
            // Não adiciona nada
		}
        // In -> In
		else if(c1.get_x() >= -1 && c2.get_x() >= -1){
			output.push_back(c2);
		}
        // In -> Out
		else if(c1.get_x() >= -1  && c2.get_x() < -1){
			output.push_back(Operations::intersection_between_lines(c1,c2,Coordinates(-1,-1), Coordinates(-1,1)));
		}
	}
	if(output.size() == 0){
		_scn_points.clear();
		return;
	}
	input.clear();
	input = output;
	input.push_back(output[0]);
	output.clear();
    // Clipping Right
	for(it = input.begin(); it != input.end()-1; it++){
		Coordinates c1 = *(it);
		Coordinates c2 = *(it+1);
        // Out -> In
		if(c1.get_x() > 1 && c2.get_x() <= 1){
			output.push_back(Operations::intersection_between_lines(c1,c2,Coordinates(1,-1),Coordinates(1,1)));
			output.push_back(c2);
		}
        // Out -> Out
		else if(c1.get_x() > 1 && c2.get_x() > 1){
            // Não adiciona nada
		}
        // In -> In
		else if(c1.get_x() <= 1 && c2.get_x() <= 1){
			output.push_back(c2);
		}
        // In -> Out
		else if(c1.get_x() <= 1  && c2.get_x() > 1){
			output.push_back(Operations::intersection_between_lines(c1,c2, Coordinates(1,-1), Coordinates(1,1)));
		}
	}
	if(output.size() == 0){
		_scn_points.clear();
		return;
	}
	input.clear();
	input = output;
	input.push_back(output[0]);
	output.clear();
    // Clipping Bottom
	for(it = input.begin(); it != input.end()-1; it++){
		Coordinates c1 = *(it);
		Coordinates c2 = *(it+1);
        // Out -> In
		if(c1.get_y() < -1 && c2.get_y() >= -1){
			output.push_back(Operations::intersection_between_lines(c1,c2, Coordinates(-1,-1), Coordinates(1,-1)));
			output.push_back(c2);
		}
        // Out -> Out
		else if(c1.get_y() < -1 && c2.get_y() < -1){
            // Não adiciona nada
		}
        // In -> In
		else if(c1.get_y() >= -1 && c2.get_y() >= -1){
			output.push_back(c2);
		}
        // In - > Out
		else if(c1.get_y() >= -1  && c2.get_y() < -1){
			output.push_back(Operations::intersection_between_lines(c1,c2, Coordinates(-1,-1), Coordinates(1,-1)));
		}
	}
	if(output.size() == 0){
		_scn_points.clear();
		return;
	}
	input.clear();
	input = output;
	input.push_back(output[0]);
	output.clear();
    // Clipping Top
	for(it = input.begin(); it != input.end()-1; it++){
		Coordinates c1 = *(it);
		Coordinates c2 = *(it+1);
        // Out -> In
		if(c1.get_y() > 1 && c2.get_y() <= 1){
			output.push_back(Operations::intersection_between_lines(c1,c2, Coordinates(-1,1), Coordinates(1,1)));
			output.push_back(c2);
		}
        // Out -> Out
		else if(c1.get_y() > 1 && c2.get_y() > 1){
            // Não adiciona nada
		}
        // In -> In
		else if(c1.get_y() <= 1 && c2.get_y() <= 1){
			output.push_back(c2);
		}
        // In -> Out
		else if(c1.get_y() <= 1  && c2.get_y() > 1){
			output.push_back(Operations::intersection_between_lines(c1,c2, Coordinates(-1,1), Coordinates(1,1)));
		}
	}
	_scn_points = output;
}