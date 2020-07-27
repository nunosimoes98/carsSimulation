#include "Piloto.h"
#include "Carro.h"
#include "Autodromo.h"
#include "Logs.h"

vector<string> Piloto::nomesUtilizados;

bool Piloto::nomeUtilizado(const string& nome)
{
	for (auto n : nomesUtilizados) {
		if (n == nome) {
			return true;
		}
	}
	return false;
}


void Piloto::acelerar()
{
	if (carro == nullptr) {
		return;
	}
	stringstream ss;
	ss << nome << " acelerou o carro " << carro->getId();
	Logs::regista(ss.str(), Registo::Tipo::Piloto);
	carro->acelera();
}

void Piloto::travar()
{
	if (carro == nullptr) {
		return;
	}
	carro->trava();
}

/*
	Verifica se o carro do piloto já terminou a corrida no autodromo.
*/
bool Piloto::terminouCorrida(Autodromo* autodromo)
{
	if (carro == nullptr) {
		return true;  // Não tem carro, já terminou a corrida para este piloto
	}

	if (autodromo->getComprimento() < carro->getDistanciaPercorrida()) {
		if (carro->getVelocidade() > 0) {
			carro->trava();
		}
		return true;
	}
	return false;
}

Piloto::~Piloto()
{
	// remover o nome da da lista de nomes utilizados, para poder ser reutilçziado
	for (auto it = nomesUtilizados.begin(); it != nomesUtilizados.end(); it++) {
		if(*it == nome) {
			nomesUtilizados.erase(it);
			break;
		}
	}
}

Piloto::Piloto(string tipo, string nome):
	tipo(tipo), nome(nome), carro(nullptr), paraCarro(false), vivo(true)
{
	int contador = 1;
	// garantir que o nome é único
	while (nomeUtilizado(nome)) {
		stringstream ss;
		ss << nome << contador; // Adiciona um número no final
		contador++;
		nome = ss.str();
	}

	// guarda o nome utilizado, para evitar duplicações
	nomesUtilizados.push_back(nome);
}

string Piloto::getTipo()
{
	return tipo;
}


string Piloto::getNome()
{
	return nome;
}

Carro* Piloto::getCarro()
{
	return carro;
}

bool Piloto::entraCarro(Carro* carro)
{
	if (!vivo) {
		return false;
	}

	if (this->carro != nullptr) {
		// Já tem um carro, não pode entrar
		return false;
	}

	if (carro->getPiloto() != nullptr) {
		return false;
	}

	this->carro = carro;
	this->carro->setPiloto(this);
	return true;
}

void Piloto::stop()
{
	paraCarro = true;
}

void Piloto::reset()
{
	paraCarro = false;
}

void Piloto::morre()
{
	vivo = false;
}

void Piloto::saiCarro()
{
	if (carro != nullptr) {
		stringstream ss;
		ss << nome << " saiu do carro " << this->carro->getId();
		Logs::regista(ss.str(), Registo::Tipo::Piloto);

		this->carro = nullptr;
	}
}


int Piloto::getPontos()
{
	return pontos;
}

void Piloto::somaPontos(int pontos)
{
	this->pontos += pontos;

	stringstream ss;
	ss << nome << " ganhou mais " << pontos << " ficando com " << this->pontos;
	Logs::regista(ss.str(), Registo::Tipo::Piloto);

}

void Piloto::limpaPontos()
{
	pontos = 0;
}

/*
	Ações iguais em todos os pilotos, que devem ser executadas antes das especificas
	de cada piloto.
	Se devolver "false" não deve executar as ações especificas de cada piloto
*/
bool Piloto::accao(Autodromo* autodromo)
{
	auto c = getCarro();
	if (c == nullptr) {
		return false;
	}

	if (!vivo) {
		return false;
	}

	if (terminouCorrida(autodromo)) {
		return false;
	}

	if (paraCarro) {
		c->trava();
		return false;
	}
	return true;
}
