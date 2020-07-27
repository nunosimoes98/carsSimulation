#include "Autodromo.h"
#include "Carro.h"
#include "Piloto.h"
#include <algorithm>
#include "Logs.h"

Autodromo::Autodromo(int maxCarros, int comprimento, string nome):
	maxCarros(maxCarros), comprimento(comprimento), nome(nome), corridaIniciada(false), corridaTerminada(false), segundos(0)
{
}

Autodromo::~Autodromo()
{

}


string Autodromo::getNome()
{
	return nome;
}

int Autodromo::getNumCarrosPista()
{
	return pista.size();
}

Carro* Autodromo::getCarro(int posicao)
{
	if (posicao >= pista.size()) {
		return nullptr;
	}
	return pista.at(posicao);
}

bool Autodromo::getCorridaIniciada()
{
	return corridaIniciada;
}

bool Autodromo::getCorridaTerminada()
{
	return corridaTerminada;
}

int Autodromo::getSegundos()
{
	return segundos;
}

vector<Piloto*> Autodromo::getPontuacao()
{
	return pontuacao;
}

void Autodromo::adicionaPontuacao(Piloto* piloto)
{
	// verificar se já está na pontuação
	for (auto p : pontuacao) {
		if (piloto == p) {
			return; // Já teve na pontuação do autodromo
		}
	}

	if (pontuacao.size() == 0) {
		piloto->somaPontos(10);  // primeiro lugar
		pontuacao.push_back(piloto);
	}
	else if (pontuacao.size() == 1) {
		piloto->somaPontos(5);  // segundo lugar
		pontuacao.push_back(piloto);
	}
	else if (pontuacao.size() == 2) {
		piloto->somaPontos(2);  // terceiro lugar
		pontuacao.push_back(piloto);
	}
	else {
		pontuacao.push_back(piloto);
	}
}

bool Autodromo::iniciaCorrida()
{
	for (auto c : pista) {
		c->reset();
		if (c->getPiloto() != nullptr) {
			c->getPiloto()->reset();
		}
	}

	if (pista.size() < 2) {
		return false;
	}

	corridaIniciada = true;
	corridaTerminada = false;
	segundos = 0;

	pontuacao.clear();

	return true;
}

void Autodromo::terminaCorrida()
{
	if (corridaIniciada) {
		corridaTerminada = true;
		// Atribuir a pontuação aos pilotos

		int pontos[3] = { 10, 5, 2 };
		int i = 0;
		auto classificacao = getClassificacaoAtual();
		for (auto c : classificacao) {
			if (c->getPiloto() != nullptr && c->getPiloto()->terminouCorrida(this)) {
				c->getPiloto()->somaPontos(pontos[i]);
				i++;

				if (i == 3) {
					break;
				}
			}
			else {
				break;  // Já não há carros que devem ter pontos apra os seus pilotos
			}
		}
	}
}

bool Autodromo::avancaTempo(int segundos)
{
	bool result;

	if (!corridaIniciada) {
		return false;
	}

	// para cada piltoo de cada carro chamar a acacao, n segundos
	for (int i = 0; i < segundos; i++) {
		result = false;
		this->segundos++;
		stringstream ss;
		ss << "Tempo " << this->segundos << " segundos";
		Logs::regista(ss.str(), Registo::Tipo::Outros);
		for (auto c : pista) {
			bool r1 = false;
			if (c->getPiloto() != nullptr) {
				r1 = c->getPiloto()->accao(this);
			}
			bool r2 = c->accao();

			if (c->getPiloto() != nullptr && c->getPiloto()->terminouCorrida(this)) {
				adicionaPontuacao(c->getPiloto());
			}

			result = result || r1 || r2;
		}
		if (result == false) {
			terminaCorrida();
			break;
		}
		// remover os carros que tem sinal de emergencia ligado
		removerCarrosComSinalEmergenciaLigado();
	}

	return result;
}

bool ordenaCarrosDistancia(Carro* c1, Carro* c2)
{
	return c1->getDistanciaPercorrida() > c2->getDistanciaPercorrida();
}

vector<Carro*> Autodromo::getClassificacaoAtual()
{
	vector<Carro*> clasificacao(pista.begin(), pista.end());

	sort(clasificacao.begin(), clasificacao.end(), ordenaCarrosDistancia);

	return clasificacao;
}

vector<Carro*> Autodromo::getGaragem()
{
	return garagem;
}

int Autodromo::getPosicao(Piloto* piloto)
{
	vector<Carro*> carros(pista); // Copia dos carros da pista

	sort(carros.begin(), carros.end()); // Ordenar pela distancia percorrida, mais pequena para a maior
	reverse(carros.begin(), carros.end()); // Inverte para ficar em primeiro o que está mais longe

	for (size_t i = 0; i < carros.size(); i++)
	{
		if (carros[i]->getPiloto() == piloto) {
			return i + 1;
		}
	}
	return -1;
}

bool Autodromo::adicionaCarro(Carro* carro)
{
	carro->setAutodromo(this);
	if (pista.size() == maxCarros || carro->getPiloto() == nullptr) {
		garagem.push_back(carro);
		return false;
	}
	else {
		pista.push_back(carro);
		return true;
	}

}

bool Autodromo::removeCarro(Carro* carro)
{
	for (int i = 0; i < pista.size(); i++) {
		Carro* c = pista[i];
		if (c == carro) {
			// remover da pista
			pista.erase(pista.begin() + i);
			carro->setAutodromo(nullptr);
			return true;
		}
	}

	for (int i = 0; i < garagem.size(); i++) {
		Carro* c = garagem[i];
		if (c == carro) {
			// remover da pista
			garagem.erase(garagem.begin() + i);
			carro->setAutodromo(nullptr);
			return true;
		}
	}

	return false;
}

void Autodromo::removerCarrosComSinalEmergenciaLigado()
{
	for (int i = 0; i < pista.size(); i++) {
		Carro* c = pista[i];
		if (c->getSinalEmergencia()) {
			// remover da pista
			pista.erase(pista.begin() + i);
			garagem.push_back(c);
			c->getPiloto()->saiCarro();
			c->setPiloto(nullptr);
		}
	}
}



int Autodromo::getMaxCarros()
{
	return maxCarros;
}

int Autodromo::getComprimento()
{
	return comprimento;
}


