#include "curve.hpp"
#include "matriz4x1.hpp"
#include "matriz4x4.hpp"

Curve::Curve(std::vector<Coordinates> points, std::string name, Color* color){
	_points = points;
	_name = name;
	//_scn_points = _points;
	_color = color;
	_background_color = new Color(1, 1, 1, 1);
	_filled = false;
}

Curve::~Curve(){
}

void Curve::clip() {
	blending_functions(_scn_points);
}

// Desenha Bezier com blending functions
void Curve::blending_functions(
		std::vector<Coordinates> points)//Quero pontos, 'sejam eles quais forem'/'quaisquer que sejam'
{
	std::vector<Coordinates>::iterator it_points = points.begin();
	std::vector<Coordinates> new_scn_points;
	double passo = 0.001;
	// Criando a matriz de bezier
	double l1MB[] = {-1,  3, -3,  1};
	double l2MB[] = { 3, -6,  3,  0};
	double l3MB[] = {-3,  3,  0,  0};
	double l4MB[] = { 1,  0,  0,  0};
	Matriz4x4* MB = new Matriz4x4(l1MB, l2MB, l3MB, l4MB);//Matriz de Bezier
	// Desenhando a curva 4 pontos por vezes sempre repetindo o ultimo ponto de uma sequencia de quatro como primeiro da próxima sequência
	it_points++;// Simulando ter passado pelo último ponto de uma sequência de quatro.
	while(it_points != points.end()){
		double lGx[4], lGy[4];
		it_points--;// Repetindo o ultimo ponto da ultima sequencia de quatro como o primeiro dessa sequência
		for(char i = 0; i < 4; ++i){
			if(it_points == points.end()){// Nunca ocorre. Se ocorrer, há falha na quantidade de pontos.
				throw false;// Primeiramente implementado o algoritmo do avestruz.
				// Pode-se simplesmente sair do laço while, mas não quero pensar em como implementar isso agora.
			}
			Coordinates w_point = *it_points;
			lGx[i] = w_point.get_x();
			lGy[i] = w_point.get_y();
			it_points++;
		}
		// Criando a matriz geometrica Gx
		Matriz4x1* Gx = new Matriz4x1(lGx[0], lGx[1], lGx[2], lGx[3]);
		// Criando a matriz geometrica Gy
		Matriz4x1* Gy = new Matriz4x1(lGy[0], lGy[1], lGy[2], lGy[3]);
		// Guardando o último ponto
//			Coordinates pontoVelho = Coordinates(lGx[0], lGy[0]);
		for(double t = 0; t<=1; t += passo)
		{
			double l1T[] = {(t*t*t),(t*t),t,1};
			Matriz1x4* T  = new Matriz1x4(l1T);
			Matriz1x4* TMB = T->multiplicarPor4x4(MB);
			double x = TMB->multiplicarPor4x1(Gx);
			double y = TMB->multiplicarPor4x1(Gy);
			Coordinates pontoNovo = Coordinates(x, y);
//				if(/*ambos os pontos na window*/)
//				{// Desenha
				new_scn_points.push_back(pontoNovo);
//				}
//				else
//				if(/*apenas 1 ponto na window*/)
//				{// Clipping
//				}
//				else/*nenhum ponto na window*/
//				{//Do nothing
//				}
//				pontoVelho = pontoNovo;
		}
	}
	_scn_points.clear();
	_scn_points = new_scn_points;
}
