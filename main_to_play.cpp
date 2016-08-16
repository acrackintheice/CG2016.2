#include <iostream>
#include <string>
#include <vector>
#include <gtk/gtk.h>
#include <limits>
#include "cor.hpp"
#include <utility>
using namespace std;

int main (int argc, char *argv[]){

	pair<Cor*, Cor*> cores(new Cor(1,1,1,1), new Cor(1,1,1,1));

	return 0;
}
