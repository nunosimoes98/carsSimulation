#pragma once

#include "Piloto.h"
#include <string>

class Autodromo;

class PilotoCrazy : public Piloto
{
	int segundosEspera;

public:
	PilotoCrazy(string nome);
	~PilotoCrazy();

	static const string TIPO;

	virtual bool accao(Autodromo* autodromo);
};

