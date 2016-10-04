#include "curve.hpp"
#include "matriz4x1.hpp"
#include "matriz4x4.hpp"
#include <cmath>

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
	blending_functions();
}

/**
 *	Funções auxiliares para os cálculos na recursão da blending function
 */
struct BF_aux {
private:
	static const char
		above	= 1<<3,
		below	= 1<<2,
		right	= 1<<1,
		left	= 1<<0;
	static const char
		min_quota = 2,
		max_quota = 10;
	static constexpr double small = 0.1;
	//Retorna os region codes de 1 ponto
	static char get_region_codes(
			Coordinates c)
	{
		char RC = 0;//region codes
		if(c.get_x() < -1){
			RC |= left;
		}
		else if(1 < c.get_x()){
			RC |= right;
		}
		if(c.get_y() < -1){
			RC |= below;
		}
		else if(1 < c.get_y()){
			RC |= above;
		}
		return RC;
	}
	// Verifica se a window está entre dois pontos (a reta que passa pelos 2 pontos cruza a window)
	static bool pass_through_window(
			Coordinates c1,
			Coordinates c2)
	{
		char RC_c1 = get_region_codes(c1),
				RC_c2 = get_region_codes(c2);
		char RC = RC_c1 & RC_c2;//AND bit-a-bit
		return RC==0;// Se 0, há chances de passar pela window
	}
	/**
	 * Verifica se a distância entre 2 pontos é pequena o suficiente para não precisar seguir com a recursão da BF.
	 * Se for pequena, o próximo ponto médio calculado na BF será (quase) colinear com os 2 pontos.
	 */
	static bool are_close(
			Coordinates c1,
			Coordinates c2)
	{
		double diff_x = c1.get_x() - c2.get_x();
		double diff_y = c1.get_y() - c2.get_y();
		return std::hypot(diff_x, diff_y) <= small;
	}
	/** Clipping de uma reta
	 * pré-condição: um dos pontos está dentro da window
	 * pós-condição: o ponto de interseção da reta com uma das bordas da window é posto no fim do 'new_scn_points'
	 */
	static void clip(
			Coordinates c1, Coordinates c2,
			std::vector<Coordinates> &new_scn_points)
	{
		char RC = get_region_codes(c1) | get_region_codes(c2);
		double diff_y = c2.get_y() - c1.get_y();
		double diff_x = c2.get_x() - c1.get_x();
		if(diff_x == 0) {
			new_scn_points.push_back(Coordinates(c1.get_x(), ((RC & above) ? 1 : -1)));
			return;
		}
		double m = diff_y / diff_x;
		{
			if(RC & left)
			{
				double y = m * (-1 - c1.get_x()) + c1.get_y();
				if(-1 <= y && y <= 1){
					new_scn_points.push_back(Coordinates(-1, y));
					return;
				}
			}
			if(RC & right)
			{
				double y = m * (1 - c1.get_x()) + c1.get_y();
				if(-1 <= y && y <= 1){
					new_scn_points.push_back(Coordinates(1, y));
					return;
				}
			}
			if(RC & above)
			{
				double x = c1.get_x() + 1/m * (1 - c1.get_y());
				if(-1 <= x && x <= 1){
					new_scn_points.push_back(Coordinates(x, 1));
					return;
				}
			}
			if(RC & below)
			{
				double x = c1.get_x() + 1/m * (-1 - c1.get_y());
				if(-1 <= x && x <= 1){
					new_scn_points.push_back(Coordinates(x, -1));
					return;
				}
			}
		}
	}
public:
	// Verifica se o ponto está dentro da window
	static bool is_on_window(
			Coordinates c)
	{
		return get_region_codes(c)==0;
	}
	/**
	 * Blending function recursiva, por divisão e conquista
	 */
	static void BF_recursivo(
			unsigned n_esima_recursao,
			Matriz4x1* MB_Gx, Matriz4x1* MB_Gy,
			Coordinates previous_p, double previous_t,
			Coordinates next_p, double next_t,
			std::vector<Coordinates> &new_scn_points
			)
	{
		double t = (previous_t + next_t)/2;// média dos t's
		double l1T[] = {(t*t*t),(t*t),t,1};
		Matriz1x4* T  = new Matriz1x4(l1T);
		double x = T->multiplicarPor4x1(MB_Gx);
		double y = T->multiplicarPor4x1(MB_Gy);
		Coordinates point = Coordinates(x, y);
		{
			if(	n_esima_recursao <= min_quota// Se a cota minima de recursão não foi alcançada, ou
			||	(	n_esima_recursao <= max_quota// a cota máxima não foi alcançada, e
				&&	pass_through_window(previous_p, point)// a window estiver entre o ponto anterior e o ponto calculado, e
				&&	! are_close(previous_p, point)// o ponto anterior e o ponto calculado não estão próximos
				)
			){
				BF_recursivo(n_esima_recursao+1,
						MB_Gx, MB_Gy,
						previous_p, previous_t,
						point, t,
						new_scn_points);
			}
			else// Se exatamente 1 ponto estiver na window
			if( is_on_window(previous_p)
			^	is_on_window(point)
			){// Clip
				clip(previous_p, point, new_scn_points);
			}
			// Se o ponto calculado estiver na window
			if(is_on_window(point)) {
				new_scn_points.push_back(point);
			}
			if(	n_esima_recursao <= min_quota// Se a cota minima de recursão não foi alcançada, ou
			||	(	n_esima_recursao <= max_quota// a cota máxima não foi alcançada, e
				&&	pass_through_window(point, next_p)// a window estiver entre o ponto calculado e o próximo ponto, e
				&&	! are_close(point, next_p)// o ponto anterior e o ponto calculado não estão próximos
				)
			){
				BF_recursivo(n_esima_recursao+1,
						MB_Gx, MB_Gy,
						point, t,
						next_p, next_t,
						new_scn_points);
			}
			else// Se exatamente 1 ponto estiver na window
			if( is_on_window(point)
			^	is_on_window(next_p)
			){// Clip
				clip(point, next_p, new_scn_points);
			}
		}
	}
};
/**
 * Transforma os pontos de Bézier em pontos da curva, formando sequências de retas
 */
void Curve::blending_functions()
{
	std::vector<Coordinates> old_scn_points = _scn_points;
	std::vector<Coordinates>::iterator it_points = old_scn_points.begin();
	_scn_points.clear();
	// Criando a matriz de bezier
	double l1MB[] = {-1,  3, -3,  1};
	double l2MB[] = { 3, -6,  3,  0};
	double l3MB[] = {-3,  3,  0,  0};
	double l4MB[] = { 1,  0,  0,  0};
	Matriz4x4* MB = new Matriz4x4(l1MB, l2MB, l3MB, l4MB);//Matriz de Bezier
	// Desenhando a curva 4 pontos por vezes sempre repetindo o ultimo ponto de uma sequencia de quatro como primeiro da próxima sequência
	it_points++;// Simulando ter passado pelo último ponto de uma sequência de quatro.
	while(it_points != old_scn_points.end()){
		double lGx[4], lGy[4];
		it_points--;// Repetindo o ultimo ponto da ultima sequencia de quatro como o primeiro dessa sequência
		for(unsigned char i = 0; i < 4; ++i){
			if(it_points == old_scn_points.end()){// Nunca ocorre. Se ocorrer, há falha na quantidade de pontos.
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
		// Multiplicando a matriz de Bézier pelas matrizes de geometria
		Matriz4x1* MB_Gx = MB->multiplicar4x1(Gx);
		Matriz4x1* MB_Gy = MB->multiplicar4x1(Gy);
		// Primeiro e último ponto
		Coordinates first_p = Coordinates(lGx[0], lGy[0]);
		Coordinates last_p = Coordinates(lGx[3], lGy[3]);
		// Verificando se o primeiro ponto está na window
		if(BF_aux::is_on_window(first_p)) {
			_scn_points.push_back(first_p);
		}
		// Realizando a chamada recursiva para a obtenção dos pontos da curva
		BF_aux::BF_recursivo(0,
				MB_Gx, MB_Gy,
				first_p, 0,
				last_p, 1,
				_scn_points);
		// Verificando se o último ponto está na window
		if(BF_aux::is_on_window(last_p)) {
			_scn_points.push_back(last_p);
		}
	}
}
