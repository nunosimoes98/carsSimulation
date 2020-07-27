#include "Carro.h"
#include "Piloto.h"
#include "Autodromo.h"
#include "Logs.h"

vector<char> Carro::listaIds;


Carro::Carro(int qtd, int qtdMax, int maxVelocidade, string marca, string modelo)
{
	this->qtdEnergia = (float) qtd;
	this->maxQtdEnergia = qtdMax;
	this->marca = marca;
	this->modelo = modelo;
	this->id = 'a';
	this->velocidade = 0;
	this->maxVelocidade = maxVelocidade;
	this->acelerador = false;
	this->travao = false;
	this->sinalEmergencia = false;
	this->danificado = false;
	this->distanciaPercorrida = 0;

	//
	bool letraValida = false;
	while (!letraValida) {
		letraValida = true;
		for (char c : listaIds) {
			if (c == this->id) {
				if (c == 'z') {
					// não há mais letras disponíveis
					this->id = '?';
					break;
				}

				// Passar para próxima letra
				this->id++;
				letraValida = false;
				break;
			}
		}
	}
	if (this->id != '?') {
		listaIds.push_back(this->id);
	}
}

Carro::~Carro()
{
	// Apagar o Id da lista de Ids utilizados.
	auto it = listaIds.begin();
	while (it != listaIds.end()) {
		if (*it == id) {
			listaIds.erase(it);
			break;
		}
		it++;
	}

	// Se há um piloto, removê-lo do carro
	if (piloto) {
		piloto->saiCarro();
	}

	if (autodromo) {
		autodromo->removeCarro(this);
	}
}



float Carro::getQtdEnergia() const
{
	return this->qtdEnergia;
}

int Carro::getQtdMaxEnergia() const
{
	return this->maxQtdEnergia;
}

int Carro::getMaxVelocidade() const
{
	return this->maxVelocidade;
}

int Carro::getVelocidade() const
{
	return velocidade;
}


string Carro::getMarca() const
{
	return this->marca;
}


void Carro::setPiloto(Piloto* piloto)
{
	if (danificado) {
		return;
	}
	this->piloto = piloto;
}

void Carro::setAutodromo(Autodromo* autodromo)
{
	if (danificado) {
		return;
	}
	this->autodromo = autodromo;
}

string Carro::getModelo() const
{
	return this->modelo;
}

Piloto* Carro::getPiloto()
{
	return piloto;
}

Autodromo* Carro::getAutodromo()
{
	return autodromo;
}

char Carro::getId() const
{
	return id;
}

int Carro::getDistanciaPercorrida() const
{
	return distanciaPercorrida;
}

bool Carro::getSinalEmergencia() const
{
	return sinalEmergencia;
}

bool Carro::getDanificado() const
{
	return danificado;
}

void Carro::carrega(int n)
{
	if (danificado) {
		return;
	}

	qtdEnergia += n;
	if (qtdEnergia > maxQtdEnergia) {
		qtdEnergia = (float)maxQtdEnergia;
	}
}

/*
	Carrega o carro até ao máximo possi´vel
*/
void Carro::carrega()
{
	if (danificado) {
		return;
	}
	qtdEnergia = (float)maxQtdEnergia;
}

void Carro::acelera()
{
	if (danificado) {
		return;
	}
	acelerador = true;
	stringstream ss;
	ss << "carro " << id << " acelerador pressionado";
	Logs::regista(ss.str(), Registo::Tipo::Carro);
}

void Carro::trava()
{
	if (danificado) {
		return;
	}
	travao = true;
	stringstream ss;
	ss << "carro " << id << " travão pressionado";
	Logs::regista(ss.str(), Registo::Tipo::Carro);
}

void Carro::ligaSinalEmergencia()
{
	sinalEmergencia = true;
	stringstream ss;
	ss << "carro " << id << " sinal de emergência ligado";
	Logs::regista(ss.str(), Registo::Tipo::Carro);
}

void Carro::acidente()
{
	danificado = true;
	velocidade = 0;
	if (piloto != nullptr) {
		stringstream ss;
		ss << "carro " << id << " teve um acidente";
		Logs::regista(ss.str(), Registo::Tipo::Carro);
		piloto->saiCarro();
		piloto->morre();
		piloto = nullptr;
	}
}

bool Carro::accao()
{
	if (danificado) {
		return false;
	}

	if (piloto == nullptr) {
		return false;
	}

	if (qtdEnergia > 0) {
		if (acelerador) {
			if (velocidade < maxVelocidade) {
				velocidade++;
				stringstream ss;
				ss << "carro " << id << " aumentou de velocidade para " << velocidade << "m/s";
				Logs::regista(ss.str(), Registo::Tipo::Carro);
			}
			acelerador = false;
		}
		if (travao) {
			if (velocidade > 0) {
				velocidade--;
				stringstream ss;
				ss << "carro " << id << " diminuiu de velocidade para " << velocidade << "m/s";
				Logs::regista(ss.str(), Registo::Tipo::Carro);
			}
			travao = false;
		}

		qtdEnergia -= 0.1 * velocidade;
	}
	else if(velocidade > 0) {
		velocidade--;
	}

	if (velocidade == 0) {
		return false; // O Carro não andou, devolve falso porque não fez nenhuma acção
	}

	distanciaPercorrida += velocidade;
	return true;
}

void Carro::reset()
{
	resetDistanciaPercorrida();
	velocidade = 0;
	sinalEmergencia = false;
	travao = false;
	acelerador = false;
}

void Carro::resetDistanciaPercorrida()
{
	distanciaPercorrida = 0;
}

bool Carro::operator<(const Carro& c)
{
	return distanciaPercorrida < c.distanciaPercorrida;
}

bool Carro::operator>(const Carro& c)
{
	return distanciaPercorrida > c.distanciaPercorrida;
}

