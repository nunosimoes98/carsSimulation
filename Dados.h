#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class DGV;
class Autodromo;
class Piloto;
class Carro;
class Campeonato;


class Dados
{
private:

	DGV* dgv;
	vector <Autodromo*> autodromos;
	Campeonato* campeonato;

public:
	Dados();
	~Dados();

	void carregaFicheiros();
	bool carregaFicheiroPilotos(string nomeFicheiro);
	bool carregaFicheiroCarros(string nomeFicheiro);
	bool carregaFicheiroAutodromos(string nomeFicheiro);

	const vector<Piloto*>& getPilotos();
	const vector<Carro*>& getCarros();
	const vector<Autodromo*>& getAutodromos();
	Piloto* getPiloto(string& nome);
	Carro* getCarro(char id);
	Autodromo* getAutodromo(string nome);
	Autodromo* getAutodromo();

	void adicionaPiloto(Piloto* p);
	void adicionaCarro(Carro* c);

	bool apagaPiloto(string nome);
	bool apagaCarro(char id);
	bool apagaAutodromo(string nome);

	void novoCampeonato(vector<Autodromo*> autodromosCampoenato);
	const vector<Piloto*> getPontuacao();

	void criaAutodromo(int maxCarros, int comprimento, string nome);

	bool corrida();
	
	
};

