#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ostream>
#include <fstream>

using namespace std;

class Carro;
class Piloto;

class Autodromo
{
	int maxCarros, comprimento;
	string nome;
	bool corridaIniciada;
	bool corridaTerminada;
	int segundos;
	
	vector<Carro*> garagem;
	vector<Carro*> pista;

	vector<Piloto*> pontuacao;

public:

	//CONSTRUTOR E DESTRUTOR
	Autodromo(int maxCarros, int comprimento, string nome);
	~Autodromo();

	//GET'S
	int getMaxCarros();
	int getComprimento();
	string getNome();
	int getNumCarrosPista();
	Carro* getCarro(int posicao);
	bool getCorridaIniciada();
	bool getCorridaTerminada();
	int getSegundos();
	vector<Piloto*> getPontuacao();
	void adicionaPontuacao(Piloto* piloto);

	bool iniciaCorrida();
	void terminaCorrida();
	bool avancaTempo(int segundos = 1);
	vector<Carro*> getClassificacaoAtual();
	vector<Carro*> getGaragem();
	int getPosicao(Piloto* piloto);
	bool adicionaCarro(Carro* carro);
	bool removeCarro(Carro* carro);

	

	void removerCarrosComSinalEmergenciaLigado();
	


};
