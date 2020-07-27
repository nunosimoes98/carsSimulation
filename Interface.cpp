#include <iostream>
#include <ostream>
#include <fstream>

#include "Interface.h"
#include "Piloto.h"
#include "PilotoRapido.h"
#include "PilotoSurpresa.h"
#include "PilotoCrazy.h"
#include "DGV.h"
#include "Carro.h"
#include "Autodromo.h"
#include "Campeonato.h"
#include "Dados.h"
#include "Logs.h"

Interface::Interface() : modo(Interface::Modo::Modo1), desenhaPista(false)
{
	dados.carregaFicheiros();

	// Para testes
	stringstream ss1("a Nuno");
	comandoEntraNoCarro(ss1);
	stringstream ss2("b Ana");
	comandoEntraNoCarro(ss2);
	stringstream ss5("c Tiago");
	comandoEntraNoCarro(ss5);
	stringstream ss4("d Joao");
	comandoEntraNoCarro(ss4);
	stringstream ss6("e Carlos Lopes");
	comandoEntraNoCarro(ss6);

	stringstream ss3("Porto Lisboa");
	comandoCampeonato(ss3);
	comandoCorrida();
}

Interface::~Interface() {}


/*
** Função que serve para ajudar com comandos antes da simulação
*/
void Interface::comandoAjudaModo1() {

	Consola::clrscr();
	Consola::setTextColor(Consola::AMARELO);
	cout << "  Lista de comandos antes de comeCar a simulacao: \n\n";
	Consola::setTextColor(Consola::BRANCO);
	cout << "\tcarregaP <nomeFicheiro>:\n\t\t -Para criar pilotos a partir do ficheiro\n\n";
	cout << "\tcarregaC <nomeFicheiro>:\n\t\t -Para criar carros a partir do ficheiro\n\n";
	cout << "\tcarregaA <nomeFicheiro>:\n\t\t -Para criar autodromos a partir do ficheiro\n\n";
	cout << "\tcria <letraTipo> <dados>:\n\t\t -Acrescenta um objeto (c = carro, p = piloto, a = autodromo) c/ as suas carateristicas\n\n";
	cout << "\tapaga <letraTipo> ident:\n\t\t -Sendo ident o nome que identifica o objeto\n\n";
	cout << "\tentranocarro <letraCarro> <nomePiloto>:\n\t\t -Faz o piloto nomepiloto entrar no carro letracarro\n\n";
	cout << "\tsaidacarro <letraCarro>:\n\t\t -Faz o piloto que estiver na letra no carro nomeCarro sair\n\n";
	cout << "\tlista:\n\t\t -Mostra no ecra a info relativa aos carros, pilotos e autodromos\n\n";
	cout << "\tcampeonato <nomeAutodromo1> <nomeAutodromoN> - Para criar campeonato com n autodromos\n";


}

/*
** Função que serve para ajudar com comandos assim que iniciada a simulação
*/
void Interface::comandoAjudaModo2() {
	Consola::clrscr();
	Consola::setTextColor(Consola::AMARELO);
	cout << "  Lista de comandos durante a simulacao: \n\n";
	Consola::setTextColor(Consola::BRANCO);
	cout << "\tlistacarros:\n\t\t -Mosta a info relativa aos carros\n\n";
	cout << "\tcarregabat <letraCarro> <Q>:\n\t\t -Carrega Q mAH de energia no carro identificado por letraCarro\n\n";
	cout << "\tcarregatudo - Carrega todos os carros ficando com as suas baterias no máximo\n\n";
	cout << "\tcorrida:\n\t\t -A corrida seguinte é iniciada\n\n";
	cout << "\tacidente <letraCarro>:\n\t\t -Provoca um dano irreparável no carro identificado por letraCarro\n\n";
	cout << "\tstop <nomePiloto>:\n\t\t -o Carro conduzido pelo piloto nomePiloto pára\n\n";
	cout << "\tdestroi <letraCarro>:\n\t\t -Remove o carro de existência\n\n";
	cout << "\tpassatempo:\n\t\t -Faz passar n segundos do tempo de simulação\n\n";
	cout << "\tlog:\n\t\t -Mostra o log de mensagens que o simulador tem registado\n\n";

}


/*
** Função que mostra inicio
*/
void Interface::mostraInicio() {

	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << endl;
	
	cout << "**************************************************************\n"
		"**************************************************************\n"
		"**                                                          **\n"
		"**     +---+---+---+---+                                    **\n"
		"**     | R | A | C | E |                                    **\n"
		"**     +---+---+---+---+---+---+---+---+---+---+---+        **\n"
		"**         | S | I | M | U | L | A | T | I | O | N |        **\n"
		"**         +---+---+---+---+---+---+---+---+---+---+        **\n"
		"**             | G | A | M | E |                            **\n"
		"**             +---+---+---+---+                            **\n"
		"**                                                          **\n"
		"**                                                          **\n"
		"**************************************************************\n"
		"**      Programacao Orientada a Objetos [2019/2020]         **\n"
		"**************************************************************\n"
		"**              Nuno Simoes / Joao coelho                   **\n"
		"**************************************************************\n";

	Consola::gotoxy(20,20);
	esperaEnter();
	Consola::clrscr();

}

/*
** Função principal que é chamada na main
*/
void Interface::initGame() {

	mostraInicio();
	comandos();
}

/*
** Função que serve para ler comandos
*/
void Interface::comandos()
{

	while (1)
	{
		mostraPista();
		Consola::setTextColor(Consola::AMARELO_CLARO);
		cout << "\n\n \t\tEscreve ajuda para lista de comandos\n" << endl << endl;
		cout << "\t\tComando >> ";
		Consola::setTextColor(Consola::BRANCO);
		string comando, cmd;
		getline(cin, comando);
		stringstream ss(comando);
		getline(ss, cmd, ' ');

		if (cmd == "sair")
		{
			break;
		}

		if (modo == Modo::Modo1) {
			comandosModo1(cmd, ss);
		}
		else if (modo == Modo::Modo2) {
			comandosModo2(cmd, ss);
		}
		esperaEnter();
		limpaEcra();
	}
}

/*
** Função com comandos do modo 1 (antes da simulação)
*/
void Interface::comandosModo1(string& cmd, stringstream& ss)
{
	if (cmd == "carregaP")
	{
		comandoCarregaPilotos(ss);
	}
	else if (cmd == "carregaC")
	{
		comandoCarregaCarros(ss);
	}
	else if (cmd == "carregaA")
	{
		comandoCarregaAutodromos(ss);
	}
	else if (cmd == "lista")
	{
		comandoLista();
	}
	else if (cmd == "cria")
	{
		comandoCriar(ss);
	}
	else if (cmd == "apaga")
	{
		comandoApaga(ss);
	}
	else if (cmd == "entranocarro") {
		comandoEntraNoCarro(ss);
	}
	else if (cmd == "saidocarro") {
		comandoSaiDoCarro(ss);
	}
	else if (cmd == "campeonato") {
		comandoCampeonato(ss);
	}
	else if (cmd == "ajuda") {
		comandoAjudaModo1();
	}
	else {
		comandoInvalido();
	}
}
/*
** Função com comandos do modo 2 (assim que iniciada a simulação)
*/
void Interface::comandosModo2(string& cmd, stringstream& ss)
{
	if (cmd == "termina") {
		comandoTermina(ss);
	}
	else if (cmd == "pontuacao") {
		comandoPontuacao();
	}
	else if (cmd == "passatempo") {
		comandoPassatempo(ss);
	}
	else if (cmd == "corrida") {
		comandoCorrida();
	}
	else if (cmd == "listacarros") {
		comandoListaCarros();
	}
	else if (cmd == "carregabat") {
		comandoCarregaBat(ss);
	}
	else if (cmd == "carregatudo") {
		comandoTudo();
	}
	else if (cmd == "acidente") {
		comandoAcidente(ss);
	}
	else if (cmd == "stop") {
		comandoStop(ss);
	}
	else if (cmd == "destroi") {
		comandoDestroi(ss);
	}
	else if (cmd == "log") {
		comandoLog();
	}
	else if (cmd == "ajuda") {
		comandoAjudaModo2();
	}
	else {
		comandoInvalido();
	}
}

void Interface::comandoInvalido()
{
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	cout << "\tComando Inválido" << endl;
}


/*
** Função que lê comando carregaP
*/
void Interface::comandoCarregaPilotos(stringstream &ss)
{
	string nomeFicheiro;


	if (ss.rdbuf()->in_avail() == 0) {
		mensagemErro();
		enviaMensagem("Comando sem parametro. Deve utilizar: carregaP <nomeFicheiro>\n");
		return;
	}

	// lê o nome do ficheiro
	ss >> nomeFicheiro;
	if (dados.carregaFicheiroPilotos(nomeFicheiro)) {
		mensagemSucesso();
		cout << "Pilotos carregados com sucesso do ficheiro " << nomeFicheiro << "." << endl;

	}
	else {
		mensagemErro();
		cout << "Problema a carregar pilotos do ficheiro " << nomeFicheiro << "." << endl;

	}
}

/*
** Função que lê comando carregaC
*/
void Interface::comandoCarregaCarros(stringstream &ss)
{

	string nomeFicheiro;


	if (ss.rdbuf()->in_avail() == 0) {
		mensagemErro();
		enviaMensagem("Comando sem parametro. Deve utilizar: carregaC <nomeFicheiro>\n");
		return;
	}

	ss >> nomeFicheiro;
	if (dados.carregaFicheiroCarros(nomeFicheiro)) {
		mensagemSucesso();
		cout << "Carros carregados com sucesso do ficheiro " << nomeFicheiro << "." << endl;
	}
	else {
		mensagemErro();
		cout << "Problema a carregar carros do ficheiro " << nomeFicheiro << "." << endl;
	}
	
}

/*
** Função que lê comando carregaA
*/
void Interface::comandoCarregaAutodromos(stringstream& ss)
{
	string nomeFicheiro;
	

	if (ss.rdbuf()->in_avail() == 0) {
		mensagemErro();
		enviaMensagem("Comando sem parametro. Deve utilizar: carregaA <nomeFicheiro>\n");
		return;
	}

	ss >> nomeFicheiro;

	if (nomeFicheiro != "autodromos.txt")
	{
		enviaMensagem("Nome do ficheiro invalido!");
	}
	else
	{
		dados.carregaFicheiroAutodromos(nomeFicheiro);
		mensagemSucesso();
		cout << "Autodromos carregados com sucesso do ficheiro";
	}
}

/**
 * Função que serve para identificar que tipo de criar nos estamos a referir
 */
void Interface::comandoCriar(stringstream& ss)
{
	string type_s;

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Parâmetro não válido!" << endl;
		return;
	}

	getline(ss, type_s, ' ');
	if (type_s.length() > 1) {
		mensagemErro();
		cout << "Parâmetro não válido!";
		return;
	}
	
	switch (type_s.at(0))
	{
	case 'p':
		comandoCriaPiloto(ss);
		break;
	case 'c':
		comandoCriaCarro(ss);
		break;
	case 'a':
		comandoCriaAutodromo(ss);
		break;
	default:
		cout << "\nTipo inválido, consulta a ajuda" << endl;
		esperaEnter();
	}
}

/*
** Função que lê comando cria p ( e cria um piloto com um determinado tipo)
*/
void Interface::comandoCriaPiloto(stringstream& ss)
{
	string tipo, nome;

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Parâmetro não válido!" << endl;
		return;
	}

	getline(ss, tipo, ' ');

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Nome do piloto em falta!" << endl;
		return;
	}

	getline(ss, nome);
	
	if (tipo == PilotoCrazy::TIPO)
	{
		Piloto* p = new PilotoCrazy(nome);
		dados.adicionaPiloto(p);
		mostraPiloto(p);
	}
	else if (tipo == PilotoRapido::TIPO)
	{
		Piloto* p = new PilotoRapido(nome);
		dados.adicionaPiloto(p);
		mostraPiloto(p);
	}
	else if (tipo == PilotoSurpresa::TIPO)
	{
		Piloto* p = new PilotoSurpresa(nome);
		dados.adicionaPiloto(p);
		mostraPiloto(p);
	}
	else {
		mensagemErro();
		cout << "O tipo do piloto nao e' valido!!";
	}
}

/*
** Função que lê comando cria c (e cria um carro)
*/
void Interface::comandoCriaCarro(stringstream& ss)
{
	int qtd, qtdMax, maxVelocidade;
	string marca, modelo;

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Parâmetro não válido!" << endl;
	}

	ss >> qtd >> qtdMax >> maxVelocidade >> marca;

	// validar se há modelo para ler, tem de se validar
	Carro* c;
	ss >> modelo;
	if (modelo.size() > 0) {
		c = new Carro(qtd, qtdMax, maxVelocidade, marca, modelo);
	}
	else {
		c = new Carro(qtd, qtdMax, maxVelocidade, marca);
	}

	dados.adicionaCarro(c);
	mostraCarro(c);
}

/*
** Função que lê comando cria a (e cria um autodromo)
*/
void Interface::comandoCriaAutodromo(stringstream& ss)
{
	int nCarros, comprimento;
	string nome;

	if(ss.fail() || ss.eof())
		mensagemErro();
		cout << "Parâmetro não válido!" << endl;

	ss >> nCarros >> comprimento >> nome;

	if ((nCarros > 0) && (comprimento > 0))
	{
		dados.criaAutodromo(nCarros, comprimento, nome);
	}
	else {
		cout << "Não é possivel criar autodromo!";
		mensagemErro();
	}

}

void Interface::comandoApaga(stringstream& ss)
{
	char type;

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Parâmetro não válido!" << endl;
	}

	ss >> type;

	switch (type)
	{
	case 'p':
		comandoApagaPiloto(ss);
		break;
	case 'c':
		comandoApagaCarro(ss);
		break;
	case 'a':
		comandoApagaAutodromo(ss);
		break;
	default:
		cout << "\nTipo inválido, consulta a ajuda" << endl;
		esperaEnter();
	}
}

void Interface::comandoApagaPiloto(stringstream& ss)
{
	string nomePiloto; 
	ss >> nomePiloto;

	if (dados.apagaPiloto(nomePiloto)) {
		mensagemSucesso();
		cout << "Piloto apagado com sucesso." << endl;
	}
	else {
		mensagemErro();
		cout << "Não foi possivel apagar o piloto." << endl;
		return;
	}
}

void Interface::comandoApagaCarro(stringstream& ss)
{
	char id;
	ss >> id;

	if (dados.apagaCarro(id)) {
		mensagemSucesso();
		cout << "Carro apagado com sucesso." << endl;
	}
	else {
		mensagemErro();
		cout << "Nao foi possivel apagar o carro." << endl;
		return;
	}
}

void Interface::comandoApagaAutodromo(stringstream& ss)
{
	string nomeAutodromo = ss.rdbuf()->str();

	if (dados.apagaAutodromo(nomeAutodromo)) {
		mensagemSucesso();
		cout << "Autodromo apagado com sucesso." << endl;
	}
	else {
		mensagemErro();
		cout << "Nao foi possivel apagar o autodromo" << endl;
		return;
	}
}

void Interface::comandoEntraNoCarro(stringstream& ss)
{
	string idCarro;
	string nomePiloto;

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Parâmetro não válido! Falta o id do carro e nome do piloto" << endl;
		return;
	}

	getline(ss, idCarro, ' ');

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Falta o nome do piloto!" << endl;
		return;
	}

	getline(ss, nomePiloto);

	Carro* carro = dados.getCarro(idCarro.at(0));
	if (carro == nullptr) {
		mensagemErro();
		cout << "Não foi encontrado um carro com o id " << idCarro << "." << endl;
		return;
	}

	if (carro->getPiloto() != nullptr) {
		mensagemErro();
		cout << "O carro já tem piloto." << endl;
		return;
	}

	Piloto* piloto = dados.getPiloto(nomePiloto);
	if (piloto == nullptr) {
		mensagemErro();
		cout << "Não foi encontrado um piloto com o nome \"" << nomePiloto << "\"." << endl;
		return;
	}

	if (piloto->entraCarro(carro)) {
		mensagemSucesso();
		cout << "O piloto entrou com sucesso no carro." << endl;
	}else {
		mensagemErro();
		cout << "Não foi possivel entrar no carro." << endl;
		return;
	}

}

void Interface::comandoSaiDoCarro(stringstream& ss)
{
	string idCarro_s;
	char idCarro;

	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Parâmetro não válido! Falta o id do carro." << endl;
		return;
	}

	getline(ss, idCarro_s, ' ');
	idCarro = idCarro_s.at(0);

	Carro* carro = dados.getCarro(idCarro);
	if (carro == nullptr) {
		mensagemErro();
		cout << "Nao foi possivel encontrar carro com o id " << idCarro << "." << endl;
		esperaEnter();
		return;
	}

	if (carro->getPiloto() == nullptr) {
		mensagemErro();
		cout << "O carro com o id " << idCarro << " nao possui nenhum piloto dentro do mesmo." << endl;
		esperaEnter();
		return;
	}

	mensagemSucesso();
	cout << "O piloto " << carro->getPiloto()->getNome() << " saiu do carro " << idCarro << " com sucesso." << endl;
	carro->getPiloto()->saiCarro();
	carro->setPiloto(nullptr);
}

void Interface::comandoCampeonato(stringstream& ss)
{
	vector<Autodromo*> autodromos;

	while (ss.good() && !ss.eof()) {
		string nomeAutodromo;
		getline(ss, nomeAutodromo, ' ');
		Autodromo* a = dados.getAutodromo(nomeAutodromo);
		if (a == nullptr) {
			mensagemErro();
			cout << "Autodromo inválido - " << nomeAutodromo << endl;
			return;
		}
		autodromos.push_back(a);
	}

	dados.novoCampeonato(autodromos);

	modo = Modo::Modo2;
}

void Interface::comandoTermina(stringstream& ss)
{
	modo = Modo::Modo1;
	cout << "Modo 1 activo" << endl;
	esperaEnter();
}

void Interface::comandoPontuacao()
{
	limpaEcra();
	int x = 10;
	int y = 3;
	int n = 1;
	for(auto piloto : dados.getPontuacao()) {
		Consola::gotoxy(x, y);

		WORD cor = Consola::BRANCO_CLARO;
		if (n > 3) {
			cor = Consola::BRANCO; // Depois do 3 primeiros a cor, é menos clara.
		}

		Consola::setTextColor(cor);
		cout << n << ". ";

		cout << piloto->getNome() << " ";
		Consola::setTextColor(Consola::CINZENTO);
		cout << "(" << piloto->getTipo() << ") ";
		Consola::setTextColor(cor);
		cout << " - " << piloto->getPontos() << " pontos";
		n++;
		y++;
	}

}

void Interface::comandoPassatempo(stringstream& ss)
{
	int n = 1;
	if (ss.good()) {
		ss >> n;
	}

	auto a = dados.getAutodromo();

	if (a == nullptr || !a->getCorridaIniciada()) {
		cout << "A corrida ainda não começou" << endl;
		return;
	}

	if (a->getCorridaTerminada()) {
		cout << "A corrida já terminou." << endl;
		return;
	}

	if (!a->avancaTempo(n)) {
		cout << "A corrida terminou" << endl;
	}
}

void Interface::comandoCorrida()
{
	if (dados.corrida()) {
		mensagemSucesso();
		cout << "Corrida iniciada com sucesso" << endl;
	}
	else {
		mensagemErro();
		cout << "Não foi possível iniciar a corrida." << endl;
	}
}

void Interface::comandoListaCarros()
{
	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "\nDados dos Carros:" << endl;
	for (auto c : dados.getCarros()) {
		mostraCarro(c);
	}
}

void Interface::comandoCarregaBat(stringstream& ss)
{
	char letra;
	if (ss. fail() || ss.eof()) {
		mensagemErro();
		cout << "Faltam parâmetros ao comando. Consulte a ajuda." << endl;
		return;
	}
	ss >> letra;

	int quantidade;
	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Faltam parâmetros ao comando. Consulte a ajuda." << endl;
		return;
	}
	ss >> quantidade;

	Carro* c = dados.getCarro(letra);
	if (c == nullptr) {
		mensagemErro();
		cout << "Não foi encontrado um carro com a letra " << letra << "." << endl;
		return;
	}

	c->carrega(quantidade);
	mensagemSucesso();
	cout << "Carro carregado com " << quantidade << " mAh" << endl;
}

void Interface::comandoTudo()
{
	for (auto c : dados.getCarros()) {
		c->carrega();
	}
	cout << "Todos os carros foram carregados." << endl;
}

void Interface::comandoAcidente(stringstream& ss)
{
	char letra;
	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Faltam parâmetros ao comando. Consulte a ajuda." << endl;
		return;
	}
	ss >> letra;

	Carro* c = dados.getCarro(letra);
	c->acidente();
}

void Interface::comandoStop(stringstream& ss)
{
	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Falta o nome do piloto!" << endl;
		return;
	}

	string nomePiloto;
	getline(ss, nomePiloto);

	Piloto* p = dados.getPiloto(nomePiloto);
	if (p == nullptr) {
		mensagemErro();
		cout << "Não foi encontrado um piloto com o nome " << nomePiloto << "." << endl;
		return;
	}

	p->stop();
}

void Interface::comandoDestroi(stringstream& ss)
{
	char letra;
	if (ss.fail() || ss.eof()) {
		mensagemErro();
		cout << "Faltam parâmetros ao comando. Consulte a ajuda." << endl;
		return;
	}
	ss >> letra;

	if (!dados.apagaCarro(letra)) {
		mensagemErro();
		cout << "Não foi encontrado um carro com a letra " << letra << "." << endl;
		return;
	}
	mensagemSucesso();
	cout << "Carro com letra " << letra << " destruido." << endl;
}

void Interface::comandoLog()
{
	auto registos = Logs::getRegistos();
	int x = 10;
	int y = 3;

	Consola::clrscr();
	Consola::gotoxy(x, y);
	Consola::setTextColor(Consola::AZUL_CLARO);
	cout << "Logs";

	for (auto r : registos) {
		y++;
		Consola::gotoxy(x, y);
		if (r.getTipo() == Registo::Tipo::Piloto) {
			Consola::setTextColor(Consola::AMARELO);
			cout << "Piloto: ";
		}
		else if (r.getTipo() == Registo::Tipo::Carro) {
			Consola::setTextColor(Consola::COR_DE_ROSA);
			cout << "Carro: ";
		}
		else {
			// Outros
			Consola::setTextColor(Consola::BRANCO);
			cout << "Outros: ";
		}
		Consola::setTextColor(Consola::BRANCO_CLARO);
		cout << r.getTexto();
	}
	Consola::gotoxy(x, ++y);
}

void Interface::comandoLista()
{

	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "\nDados dos pilotos:" << endl;
	for(auto p: dados.getPilotos()) {
		mostraPiloto(p);
	}

	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "\nDados dos Carros:" << endl;
	for (auto c : dados.getCarros()) {
		mostraCarro(c);
	}

	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "\nDados dos Autodromos:\n";
	for (auto a : dados.getAutodromos()) {
		mostraAutodromo(a);
	}

}


void Interface::mostraPiloto(Piloto* p)
{
	// TODO
	Consola::setTextColor(Consola::BRANCO);
	cout << "\tTipo: " << p->getTipo() << "\tNome: " << p->getNome();
	if (p->getCarro() != nullptr) {
		cout << "\tCarro: " << p->getCarro()->getId();
	}
	cout << endl;
}

void Interface::mostraCarro(Carro* c)
{
	// TODO
	Consola::setTextColor(Consola::BRANCO);
	cout << "Id: " << c->getId() << "Marca: " << c->getMarca() << "\tModelo: " << c->getModelo() << "\tVelocidade Max:" << c->getMaxVelocidade() << "\tEnergia: " << c->getQtdEnergia() << "\tEnergia Max: " << c->getQtdMaxEnergia() << endl;
}


void Interface::mostraCarro(Carro* c, int x, int y)
{
	Consola::gotoxy(x, y);
	mostraCarro(c);
}

void Interface::mostraAutodromo(Autodromo* autodromo)
{
	// TODO
	Consola::setTextColor(Consola::BRANCO);
	cout << "\tNo. Carros: " << autodromo->getMaxCarros() << "\tNome: " << autodromo->getNome() << "\tComprimento: " << autodromo->getComprimento() << endl;
}



void Interface::mostraPista()
{
	if (modo != Modo::Modo2) {
		return;
	}

	auto a = dados.getAutodromo();
	if (a == nullptr) {
		return;
	}

	mostraDetalhesCarros();

	int x = 10;
	int y = 20;
	int comprimento = 80; // em chars
	int espaco = 3;

	Consola::gotoxy(x, y - 2);
	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "Autodromo: " << a->getNome();
	Consola::setTextColor(Consola::BRANCO);
	
	for (int i = 0; i < a->getMaxCarros(); i++) {
		
		Consola::setTextColor(Consola::BRANCO);
		Consola::gotoxy(x, y + i);
		if (i < 9) {
			cout << 0;
		}
		cout << i + 1;
		cout << "|"; // ver o Examplo da consola, para ficar mais bonito
		

		if (a->getNumCarrosPista() > i) {
			Carro* c = a->getCarro(i);
			int p = c->getDistanciaPercorrida() * comprimento / a->getComprimento();
			WORD corCarro = Consola::AZUL_CLARO;
			if (p > comprimento) {
				p = comprimento + 2;
				corCarro = Consola::VERDE_CLARO;  // terminou a corrida
			}
			if (c->getSinalEmergencia()) {
				corCarro = Consola::AMARELO_CLARO;
			}
			Consola::gotoxy(x + p + espaco, y + i);
			if (c->getDanificado()) {
				corCarro = Consola::VERMELHO_CLARO;
			}
			Consola::setTextColor(corCarro);
			cout << c->getId();
		}
	}

	Consola::setTextColor(Consola::BRANCO);
	for (int i = 0; i < a->getMaxCarros(); i++) {
		
		Consola::gotoxy(x + comprimento + espaco + 1, y + i);
		cout << "|";
	}
}

void Interface::mostraDetalhesCarros()
{
	auto a = dados.getAutodromo();
	int x = 10;
	int y = 2;

	auto classificacao = a->getClassificacaoAtual();
	Consola::gotoxy(x, y++);
	Consola::setTextColor(Consola::AZUL);
	cout << "Classificao";

	int n = 1;
	for (auto carro : classificacao) {
		Consola::gotoxy(x, y);
		Consola::setTextColor(Consola::AZUL_CLARO);
		cout << n << ". ";
		Consola::setTextColor(Consola::BRANCO);
		cout << carro->getId() << " " << carro->getMarca();
		Consola::setTextColor(Consola::AZUL_CLARO);
		cout << " / ";
		if (carro->getPiloto() != nullptr) {
			Consola::setTextColor(Consola::BRANCO);
			cout << carro->getPiloto()->getNome() << " ";
			Consola::setTextColor(Consola::CINZENTO);
			cout << "(" << carro->getPiloto()->getTipo() << ") ";
		}
		else {
			Consola::setTextColor(Consola::CINZENTO);
			cout << "(sem piloto) ";
		}
		Consola::setTextColor(Consola::BRANCO);
		cout << carro->getQtdEnergia() << "mAh, " << carro->getQtdMaxEnergia() << "mAh - ";
		cout << carro->getDistanciaPercorrida() << "m - " << carro->getVelocidade() << "m/s" << endl;
		y++;
		n++;
	}

	mostraGaragem(++y);

	if (a->getCorridaTerminada()) {
		mostraClassificacao(dados.getPontuacao(), y);
	}
}


void Interface::mostraGaragem(int &y)
{
	auto a = dados.getAutodromo();

	int x = 10;
	
	for (auto carro : a->getGaragem()) {
		mostraCarro(carro, x, y);
		y++;
	}
}

void Interface::mostraClassificacao(vector<Piloto*> pilotos, int &y)
{
	int x = 10;
	y++;

	int pos = 1;
	for (auto p : pilotos) {
		Consola::gotoxy(x, y++);
		Consola::setTextColor(Consola::AZUL_CLARO);
		cout << pos << ". ";
		if (pos <= 3 && p->getPontos() > 0) {
			Consola::setTextColor(Consola::VERDE_CLARO);
		}
		else if (pos > 3 && p->getPontos() > 0) {
			Consola::setTextColor(Consola::BRANCO_CLARO);
		}
		else {
			Consola::setTextColor(Consola::CINZENTO);
		}
		cout << p->getNome() << " - " << p->getPontos() << " pontos";
		pos++;
	}
}
		


void Interface::limpaEcra()
{
	Consola::clrscr();
}

void Interface::corFundo()
{
	Consola::setBackgroundColor(Consola::PRETO);
}

void Interface::mensagemSucesso() {
	Consola::setTextColor(Consola::VERDE);
	cout << "\t\n[SUCESSED] ";
	Consola::setTextColor(Consola::BRANCO);
}

void Interface::mensagemErro()
{
	Consola::setTextColor(Consola::VERMELHO_CLARO);
	cout << "\t\n[ERROR] ";
	Consola::setTextColor(Consola::BRANCO);
}


void Interface::enviaMensagem(string mensagem) {
	Consola::gotoxy(20, 26);
	Consola::setTextColor(Consola::VERMELHO);

	cout << mensagem;

	Consola::getch();
}


void Interface::esperaEnter()
{
	Consola::setTextColor(Consola::AMARELO_CLARO);
	cout << "\n\tCarregue numa tecla para continuar.";
	Consola::getch();
}