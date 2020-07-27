
#include "PilotoCrazy.h"
#include "Carro.h"
#include "Autodromo.h"

const string PilotoCrazy::TIPO = "crazy";

PilotoCrazy::PilotoCrazy(string nome) :Piloto(TIPO, nome), segundosEspera(0)
{
}

PilotoCrazy::~PilotoCrazy()
{
}

bool PilotoCrazy::accao(Autodromo* autodromo)
{
	if (!Piloto::accao(autodromo)) {
		return false;
	}

	// Defini o numero de segundos que espera quando começa a corrida
	if (autodromo->getSegundos() == 1) {
		segundosEspera = (rand() % 5) + 1;
	}

	if (autodromo->getSegundos() <= segundosEspera) {
		// Aguarda X segundos
		return true;
	}

	int p = autodromo->getPosicao(this);
	if (p == autodromo->getNumCarrosPista()) {
		// está em ultimo
		travar();
	}
	else if (p != 1) {
		acelerar();
	}

	// validar se acende o sinal de emergencia
	if (getCarro()->getQtdEnergia() == 0) {
		getCarro()->ligaSinalEmergencia();
	}

	if (rand() % 100 < 5) { // Probalilidead de 5%
		getCarro()->acidente();
		// TODO -> buscar o carro que está na posição atrás dele, e acidente nesse carro.
	}

	return true;
}
