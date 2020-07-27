#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ostream>
#include <fstream>

class Piloto;
class Autodromo;

using namespace std;

class Carro
{
	int x, y;
	string marca;
	string modelo;
	float qtdEnergia;
	int maxQtdEnergia;
	char id;
	int velocidade;
	int maxVelocidade;
	int distanciaPercorrida;
	bool acelerador;
	bool travao;
	bool sinalEmergencia;
	bool danificado;

	static vector<char> listaIds;  // Guarda os ids utlizados
	Piloto* piloto;
	Autodromo* autodromo;

public:

	//CONSTRUTOR E DESTRUTOR
	Carro(int qtd, int qtdMax, int maxVelocidade, string marca, string modelo="base");
	~Carro();

	//SET's
	void setPiloto(Piloto* piloto);
	void setAutodromo(Autodromo* autodromo);

	//GET's
	float getQtdEnergia() const;
	int getQtdMaxEnergia() const;
	int getMaxVelocidade() const;
	int getVelocidade() const;
	string getMarca() const;
	string getModelo() const;
	Piloto* getPiloto();
	Autodromo* getAutodromo();
	char getId() const;
	int getDistanciaPercorrida() const;
	bool getSinalEmergencia() const;
	bool getDanificado() const;

	//
	void carrega(int n);
	void carrega();

	void acelera();
	void trava();
	void ligaSinalEmergencia();

	void acidente();

	bool accao();

	void reset();
	void resetDistanciaPercorrida();
	
	bool operator<(const Carro& c);
	bool operator>(const Carro& c);
};

