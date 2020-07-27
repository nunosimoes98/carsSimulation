#include "Logs.h"

Logs* Logs::instance = nullptr;

Logs::Logs(): maximoRegistos(30)
{
}

void Logs::limparRegistosAntigos()
{
	size_t contagem = 0;
	for (auto it = registos.begin(); it != registos.end(); it++) {
		if (contagem >= maximoRegistos) {
			it = registos.erase(it, registos.end());
			break;
		}
		contagem++;
	}
}

Logs* Logs::getInstance()
{
	if (!Logs::instance) {
		instance = new Logs();
	}
	return instance;
}

void Logs::regista(string texto, Registo::Tipo tipo)
{
	Logs* l = getInstance();
	l->registos.insert(l->registos.begin(), Registo(texto, tipo));
	l->limparRegistosAntigos();
}

void Logs::setMaximoRegistos(size_t max)
{
	Logs* l = getInstance();
	l->maximoRegistos = max;
	l->limparRegistosAntigos();
}

const list<Registo>& Logs::getRegistos()
{
	return getInstance()->registos;
}

Registo::Registo(const string& texto, Tipo tipo):
	texto(texto), tipo(tipo)
{
}

string Registo::getTexto()
{
	return texto;
}

Registo::Tipo Registo::getTipo()
{
	return tipo;
}
