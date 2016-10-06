#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "coordinates.hpp"
#include "math.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

class Operations{

public:
	// Returns the smallest angle(in radians) between two vectors, if vector 2 comes before vector 1, the angle value is negated
	static double angle_between_vectors(Coordinates vector_1,Coordinates vector_2){
		double norma_v1 = sqrt(vector_1.get_x()*vector_1.get_x()  + vector_1.get_y()*vector_1.get_y());
		double norma_v2 = sqrt(vector_2.get_x()*vector_2.get_x()  + vector_2.get_y()*vector_2.get_y());
		double angle = 0;
		if(vector_1.get_x() > vector_2.get_x()){
			angle = -acos((vector_1.get_x()*vector_2.get_x() + vector_1.get_y()*vector_2.get_y()) / (norma_v1*norma_v2));
		}else{
			angle = acos((vector_1.get_x()*vector_2.get_x() + vector_1.get_y()*vector_2.get_y()) / (norma_v1*norma_v2));
		}
		return angle;
	}
	static Coordinates intersection_between_lines(Coordinates p1,Coordinates p2, Coordinates p3, Coordinates p4){
		double a1 = 0;
		double a2 = 0;
		double b1 = 0;
		double b2 = 0;
    // Pontos da Interseccao
		double x=0;
		double y=0;
    // Calculando a interseccao
		if(p1.get_x()==p2.get_x()){
			x = p1.get_x();
			a2 = (p3.get_y()-p4.get_y())/(p3.get_x()-p4.get_x());
			b2 = p3.get_y() - a2*p3.get_x();
			y=x*a2+b2;
		}
		else{
			a1 = (p1.get_y()-p2.get_y())/(p1.get_x()-p2.get_x());
			b1 = p1.get_y() - a1*p1.get_x();
			if(p3.get_x()==p4.get_x()){
				x =p3.get_x();
			}
			else{
				a2 = (p3.get_y()-p4.get_y())/(p3.get_x()-p4.get_x());
				b2 = p3.get_y() - a2*p3.get_x();
				x = -(b1-b2)/(a1-a2);
			}
			y = x*a1 + b1;
		}
		return Coordinates(x,y);
	}
	static void split(const std::string &s, char delim, std::vector<string> &elems) {
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	static std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
	static void remove_char_from_string( string &str, char* charsToRemove ) {
		for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
			str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
		}
	}
};

#endif 


