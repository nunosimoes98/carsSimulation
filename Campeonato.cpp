#include <algorithm>

#include "Campeonato.h"


bool comparaPontos(Piloto* p1, Piloto* p2)
{
	// Faz se a comparação assim para ordenar por ordem decrescente
	return p1->getPontos() > p2->getPontos();
}


Campeonato::Campeonato(DGV* dgv, vector<Autodromo*> autodromos): dgv(dgv), autodromos(autodromos), corridaAtual(0)
{
	for (auto carro : dgv->getCarros()) {
		if (carro->getPiloto() != nullptr) {
			participantes.push_back(carro);
			carro->carrega();
			carro->getPiloto()->limpaPontos();
			classificacao.push_back(carro->getPiloto());
		}
	}
}

/*
	http://www.cplusplus.com/reference/algorithm/sort/
*/
void Campeonato::ordenaClassificacao()
{
	sort(classificacao.begin(), classificacao.end(), comparaPontos);
}

vector<Piloto*> Campeonato::getClassificacao()
{
	ordenaClassificacao();
	return classificacao;
}

bool Campeonato::corrida()
{
	if (corridaAtual >= autodromos.size()) {
		return false;
	}

	corridaAtual++;
	Autodromo* a = autodromos.at(corridaAtual - 1);
	
	for (auto carro : participantes) {
		a->adicionaCarro(carro);
	}

	return a->iniciaCorrida();
}

int Campeonato::getCorridaActual()
{
	return corridaAtual;
}

Autodromo* Campeonato::getAutodromo()
{
	if (corridaAtual == 0) {
		return nullptr;
	}
	return autodromos.at(corridaAtual - 1);
}
