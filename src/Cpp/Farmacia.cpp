#include "Farmacia.h"

Farmacia::Farmacia(string nome, string morada) {
	this->nome = nome;
	this->morada = morada;
	this->gerente = "Nenhum";
}

string Farmacia::getNome() const {
	return this->nome;
}

void Farmacia::setNome(string nome) {
	this->nome = nome;
}

string Farmacia::getMorada() const {
	return this->morada;
}

void Farmacia::setMorada(string morada) {
	this->morada = morada;
}

string Farmacia::getGerente() const {
	return this->gerente;
}

void Farmacia::setGerente(string gerente) {
	this->gerente = gerente;
}

bool Farmacia::compare (Farmacia * farm1, Farmacia * farm2)
{
	if (farm1->getNome() < farm2->getNome())
		return true;
	else
		return false;
}

std::ostream& operator<< (ostream & out, Farmacia & farm){
	out << "Nome da Farmacia: " << farm.getNome() << endl;
	out << "Morada: " <<  farm.getMorada() << endl;
	out << "Gerente: " << farm.getGerente() << endl;

	return out;
}
