#include "PilotoSurpresa.h"
#include "Carro.h"
#include "Autodromo.h"

const string PilotoSurpresa::TIPO = "surpresa";
PilotoSurpresa::PilotoSurpresa(string nome):Piloto(TIPO, nome)
{
	
}

bool PilotoSurpresa::accao(Autodromo *autodromo)
{
	if (!Piloto::accao(autodromo)) {
		return false;
	}

	int posicao = autodromo->getPosicao(this);
	if (posicao > 3) {
		acelerar();
	}
	else if (posicao == 1) {
		// em primeiro, pode ter um acidente 5%
		if (rand() % 100 < 5) {
			getCarro()->acidente();
		}
	}
	else if(rand() % 100 < 50) {
		// 50% de probabilidade de acelerar
		acelerar();
	}

	return true;
}



PilotoSurpresa::~PilotoSurpresa()
{
}