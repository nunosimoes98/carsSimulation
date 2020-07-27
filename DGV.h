#pragma once

#include <vector>
#include <string>

using namespace std;

class Piloto;
class Carro;

class DGV
{
	vector<Piloto*> pilotos;
	vector<Carro*> carros;
	string nome;

public:
	DGV();
	DGV(const DGV& dgv);
	~DGV();

	void setNome(const string& nome);
	const string& getNome() const;

	bool carregaFichPilotos(string nomeFicheiro);
	bool carregaFichCarros(string nomeFicheiro);

	const vector<Piloto*>& getPilotos();
	const vector<Carro*>& getCarros();
	Piloto* getPiloto(string &nome);
	Carro* getCarro(char id);

	void adicionaPiloto(Piloto* p);
	void adicionaCarro(Carro* c);

	bool apagaPiloto(string nome);
	bool apagaCarro(char id);
};

