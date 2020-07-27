#pragma once
#include <iostream>
#include <vector>
#include "Carros.h"
#include "Pilotos.h"
#include "Interface.h"
class Jogador
{
	int linhasJogo, colunasJogo;
	vector<Pilotos*> pilotos;
public:

	vector <Pilotos*> getPilotos();
	void mostraPilotos();

};


