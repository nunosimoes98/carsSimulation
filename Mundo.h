#pragma once
#include "Pilotos.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>


class Jogador;

class Mundo
{
	vector<Pilotos*> piloto;
public:
	string GetInformacaoPilotos();
};

