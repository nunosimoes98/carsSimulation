#pragma once
#include "Piloto.h"

class Autodromo;

class PilotoSurpresa : public Piloto
{
	//string tipo;
public:
	PilotoSurpresa(string nome);
	~PilotoSurpresa();

	static const string TIPO;

	virtual bool accao(Autodromo* autodromo);
};

