#include "Mundo.h"

string Mundo::GetInformacaoPilotos() {

	ostringstream os;

	for (unsigned int i = 0; i < this->piloto.size(); i++) {

		os << this->piloto[i]->getInfoPiloto();

	}

	return os.str();

}
