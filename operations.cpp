#include "coordinates.hpp"
#include "math.h"

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
};

