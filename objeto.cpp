#include "objeto.hpp"
#include <iostream>

using namespace std;

string Objeto::get_name(){
	return _name;
}
vector<Coordenadas*> Objeto::get_pontos(){
	return _pontos;
}

void Objeto::print(){
	cout << _name << endl;
	vector<Coordenadas*>::iterator it;
	int i = 0;
	for(it = _pontos.begin(); it != _pontos.end(); it++){
		Coordenadas* point = (*it);
		cout << "Ponto " << i << " ==> (" << point->get_x() << ", " << point->get_y() << ")" << endl;
		i++;
	}
}

Coordenadas* Objeto::geometric_center(){
	double somaX = 0;
	double somaY = 0;
	vector<Coordenadas*>::iterator it;
	for(it = _pontos.begin(); it != _pontos.end(); it++){
		Coordenadas* point = (*it);
		somaX = somaX + point->get_x();
		somaY = somaY + point->get_y();
	}
	Coordenadas* center = new Coordenadas((somaX/_pontos.size()),(somaY/_pontos.size()));
	return center;
}

void Objeto::transform(Matriz3x3* transformation){
	vector<Coordenadas*>::iterator it;
	for(it = _pontos.begin(); it != _pontos.end(); it++){
		double l4[] = {0,0,1};
		Coordenadas* point = (*it);
		l4[0] = point->get_x();
		l4[1] = point->get_y();
		Matriz1x3* point_matrix = new Matriz1x3(l4);
		Matriz1x3* transformed_point = point_matrix->multiplicarPor3x3(transformation);
		(*it) = new Coordenadas(transformed_point->get(0), transformed_point->get(1));
		delete point;
		delete point_matrix;
	}
	print();
}
void Objeto::translate(double Dx, double Dy){
	double l1[] = {1,0,0};
	double l2[] = {0,1,0};
	double l3[] = {Dx,Dy,1};
	Matriz3x3* translater = new Matriz3x3(l1,l2,l3);
	transform(translater);
	delete translater;
}
void Objeto::scale(double Sx, double Sy){
	Coordenadas* center = geometric_center();
	double Cx =  center->get_x();
	double Cy =  center->get_y();
	double l1[] = {Sx,0,0};
	double l2[] = {0,Sy,0};
	double l3[] = {(((-Cx)*Sx)+Cx),(((-Cy)*Sy)+Cy),1};
	Matriz3x3* scaling = new Matriz3x3(l1,l2,l3);
	transform(scaling);
	delete center;
	delete scaling;
}


