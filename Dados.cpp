#include "Dados.h"
#include "DGV.h"
#include "Campeonato.h"
#include "Carro.h"

Dados::Dados(): dgv(new DGV()), campeonato(nullptr)
{
}

Dados::~Dados()
{
	if (campeonato != nullptr) {
		delete campeonato;
	}
	delete dgv;

	for (auto a : autodromos) {
		delete a;
	}
}

void Dados::carregaFicheiros()
{
	dgv->carregaFichCarros("carros.txt");
	dgv->carregaFichPilotos("pilotos.txt");
	carregaFicheiroAutodromos("autodromos.txt");
}

bool Dados::carregaFicheiroPilotos(string nomeFicheiro)
{
	return dgv->carregaFichPilotos(nomeFicheiro);
}

bool Dados::carregaFicheiroCarros(string nomeFicheiro)
{
	return dgv->carregaFichCarros(nomeFicheiro);
}

bool Dados::carregaFicheiroAutodromos(string nomeFicheiro)
{
	fstream fichAutodromos;

	fichAutodromos.open(nomeFicheiro, ios::in);

	if (fichAutodromos.fail()) {
		return false;
	}

	int nCarros, comprimento;
	string nome;


	while (fichAutodromos >> nCarros >> comprimento >> nome)
	{
		Autodromo* a = new Autodromo(nCarros, comprimento, nome);
		autodromos.push_back(a);
	}

	fichAutodromos.close();
	return true;
}

const vector<Piloto*>& Dados::getPilotos()
{
	return dgv->getPilotos();
}

const vector<Carro*>& Dados::getCarros()
{
	return dgv->getCarros();
}

const vector<Autodromo*>& Dados::getAutodromos()
{
	return autodromos;
}

Piloto* Dados::getPiloto(string& nome)
{
	return dgv->getPiloto(nome);
}

Carro* Dados::getCarro(char id)
{
	return dgv->getCarro(id);
}

Autodromo* Dados::getAutodromo(string nome)
{
	for (auto a : autodromos) {
		if (a->getNome() == nome) {
			return a;
		}
	}
	return nullptr;
}

Autodromo* Dados::getAutodromo()
{
	return campeonato->getAutodromo();
}

void Dados::adicionaPiloto(Piloto* p)
{
	dgv->adicionaPiloto(p);
}

void Dados::adicionaCarro(Carro* c)
{
	dgv->adicionaCarro(c);
}

bool Dados::apagaPiloto(string nome)
{
	return dgv->apagaPiloto(nome);
}

bool Dados::apagaCarro(char id)
{
	return dgv->apagaCarro(id);

}

bool Dados::apagaAutodromo(string nome) {

	for (int i = 0; i < autodromos.size(); i++) {

		if (autodromos[i]->getNome() == nome) {
			autodromos.erase(autodromos.begin() + i);
			return true;
		}
	}
	return false;
}

void Dados::novoCampeonato(vector<Autodromo*> autodromosCampoenato)
{
	if (campeonato != nullptr) {
		delete campeonato;
	}
	campeonato = new Campeonato(dgv, autodromos);


}

const vector<Piloto*> Dados::getPontuacao()
{
	return campeonato->getClassificacao();
}

void Dados::criaAutodromo(int maxCarros, int comprimento, string nome)
{
	auto a = new Autodromo(maxCarros, comprimento, nome);
	autodromos.push_back(a);
}

bool Dados::corrida()
{
	return campeonato->corrida();
}

