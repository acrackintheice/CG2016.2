#ifndef OPERATIONS_CPP
#define OPERATIONS_CPP

#include "coordinates_3d.hpp"
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
	static double norma_3d(Coordinates_3d* vector){
		return sqrt(vector->get_x()*vector->get_x() + vector->get_y()*vector->get_y() + vector->get_z()*vector->get_z());
	}
	static double norma(Coordinates_3d vector){
		return sqrt(vector.get_x()*vector.get_x() + vector.get_y()*vector.get_y());
	}
	// Returns the smallest angle(in radians) between two vectors, if vector 2 comes before vector 1, the angle value is negated
	static double angle_between_vectors(Coordinates_3d vector_1,Coordinates_3d vector_2){
		double norma_v1 = norma(vector_1);
		double norma_v2 = norma(vector_2);
		double angle = 0;
		if(vector_1.get_x() > vector_2.get_x()){
			angle = -acos((vector_1.get_x()*vector_2.get_x() + vector_1.get_y()*vector_2.get_y()) / (norma_v1*norma_v2));
		}else{
			angle = acos((vector_1.get_x()*vector_2.get_x() + vector_1.get_y()*vector_2.get_y()) / (norma_v1*norma_v2));
		}
		return angle;
	}
	// Returns the smallest angle(in radians) between two vectors, if vector 2 comes before vector 1, the angle value is negated
	static double angle_between_vectors_3d(Coordinates_3d* vector_1, Coordinates_3d* vector_2){
		double norma_v1 = norma_3d(vector_1);
		double norma_v2 = norma_3d(vector_2);
		return acos((vector_1->get_x()*vector_2->get_x() + vector_1->get_y()*vector_2->get_y() + vector_1->get_z()*vector_2->get_z()) / (norma_v1*norma_v2));
	}
	static Coordinates_3d* cross_product_3d(Coordinates_3d* vector_1, Coordinates_3d* vector_2){
		double a1 = vector_1->get_x();
		double a2 = vector_1->get_y();
		double a3 = vector_1->get_z();
		double b1 = vector_2->get_x();
		double b2 = vector_2->get_y();
		double b3 = vector_2->get_z();

		double x = a2*b3 - a3*b2;
		double y = a3*b1 - a1*b3;
		double z = a1*b2 - a2*b1;

		return new Coordinates_3d(x,y,z);
	}
	static Coordinates_3d intersection_between_lines(Coordinates_3d p0,Coordinates_3d p1, Coordinates_3d p2, Coordinates_3d p3){
		float p0_x = p0.get_x();
		float p0_y = p0.get_y();
		float p1_x = p1.get_x();
		float p1_y = p1.get_y(); 
		float p2_x = p2.get_x();
		float p2_y = p2.get_y();
		float p3_x = p3.get_x();
		float p3_y = p3.get_y();  
		float s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
		s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

		float s, t;
		s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		{
        // Collision detected
			double x = p0_x + (t * s1_x);
			double y = p0_y + (t * s1_y);
			return Coordinates_3d(x,y,0);;
		}
		cout << "Houston we had a problem" << endl;
    	return Coordinates_3d(-10000,-10000,0);; // No collision
    }
    static Coordinates_3d* intersection_between_lines_2(Coordinates_3d* p0,Coordinates_3d* p1, Coordinates_3d* p2, Coordinates_3d* p3){
		float p0_x = p0->get_x_scn();
		float p0_y = p0->get_y_scn();
		float p1_x = p1->get_x_scn();
		float p1_y = p1->get_y_scn(); 
		float p2_x = p2->get_x_scn();
		float p2_y = p2->get_y_scn();
		float p3_x = p3->get_x_scn();
		float p3_y = p3->get_y_scn();  
		float s1_x, s1_y, s2_x, s2_y;
		s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
		s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

		float s, t;
		s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
		t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		{
        // Collision detected
			double x = p0_x + (t * s1_x);
			double y = p0_y + (t * s1_y);

			return new Coordinates_3d(x,y,0);
		}
		cout << "The intersection returned a fucked up Coordinate" << endl;
    	return new Coordinates_3d(-10000,-10000,0);; // No collision
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


