#pragma once
#include "Autodromo.h"
#include "DGV.h"
#include "Carro.h"
#include "Piloto.h"

using namespace std;

class Campeonato
{
	vector<Autodromo*> autodromos;
	vector<Carro*> participantes;
	vector<Piloto*> classificacao;
	size_t corridaAtual;
	DGV* dgv;

public:
	Campeonato(DGV *dgv, vector<Autodromo*> autodromos);

	void ordenaClassificacao();
	vector<Piloto*> getClassificacao();

	bool corrida();

	int getCorridaActual();
	Autodromo* getAutodromo();
};

