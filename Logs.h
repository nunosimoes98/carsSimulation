#pragma once
// https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern

#include <string>
#include <list>

using namespace std;

class Registo
{
public:
	enum class Tipo
	{
		Carro,
		Piloto,
		Outros
	};

	Registo(const string& texto, Tipo tipo);
	string getTexto();
	Tipo getTipo();

private:
	string texto;
	Tipo tipo;

};

class Logs
{
private:
	static Logs* instance;

	list<Registo> registos;
	size_t maximoRegistos;
	Logs();

	void limparRegistosAntigos();

public:
	static Logs* getInstance();

	static void regista(string texto, Registo::Tipo tipo);
	static void setMaximoRegistos(size_t max);
	static const list<Registo>& getRegistos();

};

