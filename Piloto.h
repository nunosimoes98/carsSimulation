#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Carro;
class Autodromo;

using namespace std;
class Piloto
{
private:
	string nome;
	string tipo;
	static vector<string> nomesUtilizados;
	bool paraCarro;
	bool vivo;
	Carro* carro;
	int pontos;

	bool nomeUtilizado(const string& nome);

protected:
	void acelerar();
	void travar();


public:

	//CONSTRUTOR E DESTRUTOR
	virtual ~Piloto();
	Piloto(string tipo, string nome);

	//GET's
	string getTipo();
	string getNome();

	Carro* getCarro();
	void saiCarro();
	bool entraCarro(Carro* carro);

	void stop();
	void reset();
	void morre();

	int getPontos();
	void somaPontos(int pontos);
	void limpaPontos();

	bool terminouCorrida(Autodromo* autodromo);

	virtual bool accao(Autodromo *autodromo) = 0;
};

