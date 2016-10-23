#ifndef OPERATIONS_CPP
#define OPERATIONS_CPP

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
	static double norma(Coordinates vector){
		return sqrt(vector.x()*vector.x() + vector.y()*vector.y() + vector.z()*vector.z());
	}
	static Coordinates cross_product_3d(Coordinates vector_1, Coordinates vector_2){
		double a1 = vector_1.x(); double a2 = vector_1.y();	double a3 = vector_1.z();
		double b1 = vector_2.x(); double b2 = vector_2.y();	double b3 = vector_2.z();
		return Coordinates(a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1);
	}
    static Coordinates* intersection_between_lines_2(Coordinates* p0,Coordinates* p1, Coordinates* p2, Coordinates* p3){
		double p0_x = p0->x_scn(); double p0_y = p0->y_scn(); double p1_x = p1->x_scn(); double p1_y = p1->y_scn();
		double p2_x = p2->x_scn(); double p2_y = p2->y_scn(); double p3_x = p3->x_scn(); double p3_y = p3->y_scn();
		double s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
		s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;
		double s, t;
		s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
		if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		{
        // Collision detected
			double x = p0_x + (t * s1_x);
			double y = p0_y + (t * s1_y);
			return new Coordinates(x,y,0);
		}
		cout << "The intersection returned a fucked up Coordinate" << endl;
    	return new Coordinates(-10000,-10000,0);; // No collision
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


