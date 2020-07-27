#include "Jogador.h"

vector<Pilotos*> Jogador::getPilotos()
{
	return pilotos;
}

void Jogador::mostraPilotos()
{
	cout << "Dados dos pilotos: \n\n";
	for (unsigned int i = 0; i < pilotos.size(); i++)
	{
		cout << pilotos[i]->getNome() << " " << pilotos[i]->getTipo << "\n";
	}
}
