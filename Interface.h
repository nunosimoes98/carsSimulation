#pragma once

#include "Consola.h"
#include "Interface.h"
#include "Dados.h"
#include <string>
#include <vector>
#include <sstream>


class DGV;
class Autodromo;
class Piloto;
class Carro;


using namespace std;


class Interface
{
	enum class Modo {
		Modo1,
		Modo2
	};

	Dados dados;
	Modo modo;
	bool desenhaPista;

public:
	Interface();
	~Interface();
	//FUNÇÕES
	void initGame();

private:
	void comandos();
	void comandosModo1(string& cmd, stringstream& ss);
	void comandosModo2(string& cmd, stringstream& ss);
	
	void comandoInvalido();

	void comandoCarregaPilotos(stringstream &ss);
	void comandoCarregaCarros(stringstream &ss);
	void comandoCarregaAutodromos(stringstream& ss);
	void comandoLista();
	void comandoCriar(stringstream &ss);
	void comandoCriaPiloto(stringstream& ss);
	void comandoCriaCarro(stringstream& ss);
	void comandoCriaAutodromo(stringstream& ss);
	void comandoApaga(stringstream& ss);
	void comandoApagaPiloto(stringstream& ss);
	void comandoApagaCarro(stringstream& ss);
	void comandoApagaAutodromo(stringstream& ss);
	void comandoEntraNoCarro(stringstream& ss);
	void comandoSaiDoCarro(stringstream& ss);
	void comandoCampeonato(stringstream& ss);

	// Comando MOdo 2
	void comandoTermina(stringstream& ss);
	void comandoPontuacao();
	void comandoPassatempo(stringstream& ss);
	void comandoCorrida();
	void comandoListaCarros();
	void comandoCarregaBat(stringstream& ss);
	void comandoTudo();
	void comandoAcidente(stringstream& ss);
	void comandoStop(stringstream& ss);
	void comandoDestroi(stringstream& ss);
	void comandoLog();


	//MOSTRA
	void comandoAjudaModo1();
	void comandoAjudaModo2();
	void mostraInicio();

	void mostraPiloto(Piloto* p);
	void mostraCarro(Carro* c);
	void mostraCarro(Carro* c, int x, int y);
	void mostraAutodromo(Autodromo* autodromo);
	void mostraPista();
	void mostraDetalhesCarros();
	void mostraGaragem(int &y);
	void mostraClassificacao(vector<Piloto*> pilotos, int &y);

	// Auxiliares
	void enviaMensagem(string mensagem);
	void esperaEnter();
	void limpaEcra();
	void corFundo();
	void mensagemSucesso();
	void mensagemErro();
};
