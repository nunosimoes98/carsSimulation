#include "PilotoRapido.h"
#include "Piloto.h"
#include "Carro.h"
#include "Autodromo.h"

const string PilotoRapido::TIPO = "rapido";

PilotoRapido::PilotoRapido(string nome):Piloto(TIPO, nome)
{
}

PilotoRapido::~PilotoRapido()
{
}

bool PilotoRapido::accao(Autodromo *autodromo)
{
	if (!Piloto::accao(autodromo)) {
		return false;
	}

	if (getCarro()->getQtdMaxEnergia() / 2 >= getCarro()->getQtdEnergia()) {
		acelerar();
	}
	else {
		if (autodromo->getSegundos() % 3 == 0) {
			// Executa a cada 3 segundos, com a energia a menos de metade
			acelerar();
		}
	}

	// Em cada 10 segundos
	if (autodromo->getSegundos() % 10 == 0) {
		if (rand() % 10 == 0) {
			getCarro()->ligaSinalEmergencia();
		}
	}

	return true;
}
