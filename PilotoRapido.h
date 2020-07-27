#pragma once
#include "Piloto.h"


class Autodromo;

class PilotoRapido : public Piloto
{
public:
	PilotoRapido(string nome);
	~PilotoRapido();

	static const string TIPO;

	virtual bool accao(Autodromo* autodromo);
};

