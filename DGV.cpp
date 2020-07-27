#include <sstream>
#include <fstream>

#include "DGV.h"
#include "Piloto.h"
#include "PilotoRapido.h"
#include "PilotoSurpresa.h"
#include "PilotoCrazy.h"
#include "Carro.h"

DGV::DGV(): nome("")
{
}

DGV::DGV(const DGV& dgv)
{
}

DGV::~DGV()
{
	for (auto p : pilotos) {
		delete p;
	}
	for (auto c : carros) {
		delete c;
	}
}

void DGV::setNome(const string& nome)
{
	this->nome = nome;
}

const string& DGV::getNome() const
{
	return nome;
}

bool DGV::carregaFichPilotos(string nomeFicheiro)
{
	fstream fichPilotos;
	int i = 0;
	fichPilotos.open(nomeFicheiro, ios::in);

	if (fichPilotos.fail()) {
		return false;
	}

	string tipo;
	while (getline(fichPilotos, tipo, ' '))
	{
		string nome;
		getline(fichPilotos, nome);

		Piloto* p = nullptr;
		if (tipo == PilotoRapido::TIPO) {
			p = new PilotoRapido(nome);
		}
		else if (tipo == PilotoCrazy::TIPO) {
			p = new PilotoCrazy(nome);
		}
		else if (tipo == PilotoSurpresa::TIPO) {
			p = new PilotoSurpresa(nome);
		}

		if (p != nullptr) {
			pilotos.push_back(p);
		}
	}

	fichPilotos.close();
	return true;
}

bool DGV::carregaFichCarros(string nomeFicheiro)
{
	fstream fichCarros;
	fichCarros.open(nomeFicheiro, ios::in);

	if (fichCarros.fail()) {
		return false;
	}

	int qtdEnergia, qtdMaxEnergia, maxVelocidade;
	string marca, modelo;

	while (fichCarros >> qtdEnergia >> qtdMaxEnergia >> maxVelocidade >> marca >> modelo)
	{
		Carro* c = new Carro(qtdEnergia, qtdMaxEnergia, maxVelocidade, marca, modelo);
		carros.push_back(c);
	}

	fichCarros.close();
	return true;
}

const vector<Piloto*>& DGV::getPilotos()
{
	return pilotos;
}

const vector<Carro*>& DGV::getCarros()
{
	return carros;
}

Piloto* DGV::getPiloto(string &nome)
{
	for (auto p : pilotos) {
		if (p->getNome() == nome) {
			return p;
		}
	}
	return nullptr;
}

Carro* DGV::getCarro(char id)
{
	for (auto c : carros) {
		if (c->getId() == id) {
			return c;
		}
	}
	return nullptr;
}

void DGV::adicionaPiloto(Piloto* p)
{
	pilotos.push_back(p);
}

bool DGV::apagaPiloto(string nome)
{
		for (int i = 0; i < pilotos.size(); i++) {

			if (pilotos[i]->getNome() == nome) {
				pilotos.erase(pilotos.begin() + i);
				return true;
			}
		}
	return false;
}

bool DGV::apagaCarro(char id)
{
	for (int i = 0; i < carros.size(); i++) {

		if (carros[i]->getId() == id) {
			Carro* c = carros[i];
			carros.erase(carros.begin() + i);
			delete c;
			return true;
		}
	}
	return false;
}

void DGV::adicionaCarro(Carro* c)
{
	carros.push_back(c);
}
